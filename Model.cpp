#include "Model.h"
#include "factory.h"
#include "Truck.h"
Model& Model::getInstance(){
    static Model inst;
    return inst;
}

Model::Model(u_int curr_hour):curr_hour(curr_hour),time(0),simObjList(0),warehouses(0),vehicles(0){
    warehouses["Frankfurt"] = make_shared<Warehouse>("Frankfurt",100000,Point(40,10));
    simObjList["Frankfurt"] = dynamic_pointer_cast<SimObject>(warehouses["Frankfurt"]);
}


void Model::init(vector<string>&& argv){
    bool truckFileFound = false;
    for(u_int i=0; i < argv.size();i++){
        if(argv[i] == "-w"){
            i++;
            readDepotFile(argv[i]);
            continue;
        }
        if(argv[i] == "-t"){
            truckFileFound = true;
            i++;
            while(argv[i] != "-w"){
                auto truckfileName = argv[i];
                size_t lastdot = truckfileName.find_last_of(".");
                string truckName = truckfileName.substr(0,lastdot);
                vehicles[truckName] = genericFactory<Vehicle>::instance().create("truck",truckName);
                simObjList[truckName] = dynamic_pointer_cast<SimObject>(vehicles[truckName]);
                shared_ptr<Truck> tp = dynamic_pointer_cast<Truck>(vehicles[truckName]);
                try{   
                    tp->init(truckfileName);
                }catch(...){
                    //TODO catch correct exception and throw or terminate
                }
                if(argv.size() <= ++i) break;
            }
            i--;
        }

    }
}

bool Model::containsObj(TYPE t, const string& name){
    auto it = simObjList.find(name);
    switch(t){
        case WAREHOUSE:
            return it != simObjList.end() && typeid(*(it->second.get())).name() + 1 == string("Warehouse");
        case TROOPER:
            return it != simObjList.end() && typeid(*(it->second.get())).name() + 1 == "Trooper";
        case TRUCK:
            return it != simObjList.end() && typeid(*(it->second.get())).name() + 1 == "Truck";
        case CHOPPER:
            return it != simObjList.end() && typeid(*(it->second.get())).name() + 1 == "Chopper";
    }
    return false;
}

float Model:: hourToDecimal(string& hour){
    hour[2] = ' ';
    stringstream ss(hour);
    float decHour;
    float decMins;
    ss>>decHour;
    ss>>decMins;
    decHour+= decMins/60;
    return decHour;
}

void Model::readDepotFile(const string& filePath){
    ifstream f(filePath);
    if(!f){
        //TODO throw exception
    }
    int inventory;
    string name,point,inv;
    while(!f.eof()){
        getline(f,name,',');
        getline(f,point,')');
        f.ignore();
        getline(f,inv);
        stringstream(inv) >> inventory;
        stringstream sp(point);
        double x, y; char c;
        sp.ignore(2);
        sp >> x;
        sp >> c;
        sp >> y;
        warehouses[name] = shared_ptr<Warehouse>(new Warehouse(name,inventory,Point(x,y)));
        simObjList[name] = warehouses[name];
    }
}

void Model::updateAll(){
    time++;
    for(auto &o: simObjList){
        o.second->update();
    }
    for(auto c:choppers){
        string target_s = c->getAttackTarget();
        if(target_s=="") continue;
        shared_ptr<Truck> target = dynamic_pointer_cast<Truck>(vehicles[target_s]);
        int range = c->getRange();
        if(getDistance(c->getCurLocation(),target->getCurLocation())*100 > range
          || trooperInRadius(target->getLocation()))
        {
            if(range>2) c->setRange(range-1);
            cout << c->getName() << " attack failed\n";
        }
        else{
            target->attack();
            if(range < 20) c->setRange(range+1);
            cout << c->getName() << " attack success\n";
        }
        c->attack("");
        c->setCurLocation(target->getLocation());
        c->setStatus(TrackBase::STOPPED);
    }
}


Model::TYPE Model::getObjectType(const string& name){
    auto it = simObjList.find(name);
    if(it == simObjList.end()){
        return NONE;
    }
    string type = typeid(*(it->second.get())).name() + 1;
    if(type == "Warehouse") return WAREHOUSE;
    if(type == "Truck") return TRUCK;
    if(type == "Trooper") return TROOPER;
    if(type == "Chopper") return CHOPPER;
    return NONE;
}

void Model::createVehicle(const string& name, const string& target){
    if(simObjList.find(name) != simObjList.end()){
        //TODO throw
    }
    if(!containsObj(WAREHOUSE,target)){
        //TODO throw
    }
    vehicles[name] = genericFactory<Vehicle>::instance().create("trooper",name);
    simObjList[name] = dynamic_pointer_cast<SimObject>(vehicles[name]);
    vehicles[name]->setCurLocation(warehouses[target]->getLocation());
    vehicles[name]->setSpeed(90);
    dynamic_pointer_cast<Trooper>(vehicles[name])->buildCourse(target);
    troopers.push_back(dynamic_pointer_cast<Trooper>(vehicles[name]));
}
void Model::createVehicle(const string& name, double x, double y){
    if(simObjList.find(name) != simObjList.end()){
        //TODO throw
    }
    vehicles[name] = genericFactory<Vehicle>::instance().create("chopper",name);
    simObjList[name] = dynamic_pointer_cast<SimObject>(vehicles[name]);
    vehicles[name]->setCurLocation(Point(x,y));
    vehicles[name]->setSpeed(0);
    vehicles[name]->setStatus(TrackBase::PARKED);
    choppers.push_back(dynamic_pointer_cast<Chopper>(vehicles[name]));
}

void Model::setVehicleCourse(const string& name, double course){
    if(getObjectType(name) != TROOPER){
        //TODO throw
    }
    vehicles[name]->setCourse(course);
}
void Model::setVehicleCourse(const string& name, double course, double speed){
    if(getObjectType(name) != CHOPPER){
        //TODO throw
    }
    vehicles[name]->setCourse(course);
    vehicles[name]->setSpeed(speed);
}

void Model::setVehiclePosition(const string& name, double x, double y){
    if(getObjectType(name) != TROOPER){
        //TODO throw
    }
    vehicles[name]->setPosition(x,y);
}
void Model::setVehiclePosition(const string& name, double x, double y, double speed){
    if(getObjectType(name) != CHOPPER){
        //TODO throw
    }
    vehicles[name]->setPosition(x,y);
    vehicles[name]->setSpeed(speed);
}

void Model::setVehicleDestination(const string& name,const string& WHname){
    if(getObjectType(name) != TROOPER){
        //TODO throw
    }
    dynamic_pointer_cast<Trooper>(vehicles[name])->buildCourse(WHname);
}

void Model::attack(const string& name, const string& target){
    if(getObjectType(name) != CHOPPER){
        //TODO throw
    }if(getObjectType(target) != TRUCK){
        //TODO throw
    }
    dynamic_pointer_cast<Chopper>(vehicles[name])->attack(target);
}

void Model::stopVehicle(const string& name){
    if(getObjectType(name) == WAREHOUSE || getObjectType(name) == NONE){
        //TODO throw
    }
    vehicles[name]->setStatus(0);
}

vector<shared_ptr<Warehouse>> Model::getWarehouses() const{
    vector<shared_ptr<Warehouse>> vec;
    for (auto it=warehouses.begin(); it!=warehouses.end(); ++it) {
      vec.push_back( it->second );
    }
    return vec;
}


bool Model::trooperInRadius(const Point& p,double r){
    for(auto t:troopers){
        if(getDistance(t->getCurLocation(),p)*100<=r){
            return true;
        }
    }
    return false;
}


void Model::status() const{
    for(auto o:simObjList){
        o.second->broadcastState(cout);
    }
}