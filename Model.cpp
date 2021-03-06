#include "Model.h"
#include "factory.h"
#include "Truck.h"
Model& Model::getInstance(){
    static Model inst;
    return inst;
}

Model::Model():time(0),simObjList(0),warehouses(0),vehicles(0){
    //create the defualt warehouse
    warehouses["Frankfurt"] = make_shared<Warehouse>("Frankfurt",100000,Point(40,10));
    simObjList["Frankfurt"] = dynamic_pointer_cast<SimObject>(warehouses["Frankfurt"]);
}


void Model::init(vector<string>&& argv){
    bool truckFileFound = false;
    bool depotFileFound = false;

    for(u_int i=0; i < argv.size();i++){
        if(argv[i] == "-w"){
            i++;
            readDepotFile(argv[i]);
            depotFileFound = true;
            continue;
        }
        if(argv[i] == "-t"){
            //get input from a Truck's file
            truckFileFound = true;
            i++;
            while(argv[i] != "-w"){
                 //get trucks files and create trucks by thier data
                auto truckfileName = argv[i];
                size_t lastdot = truckfileName.find_last_of(".");
                string truckName = truckfileName.substr(0,lastdot);
                //using factory c'tors map to get a new truck pointer 
                vehicles[truckName] = genericFactory<Vehicle>::instance().create("truck",truckName);
                //add the new truck to the simObjects map
                simObjList[truckName] = dynamic_pointer_cast<SimObject>(vehicles[truckName]);
                shared_ptr<Truck> tp = dynamic_pointer_cast<Truck>(vehicles[truckName]);   
                //init the truck and create it's course
                tp->init(truckfileName);
                trucks.push_back(tp);
                if(argv.size() <= ++i) break;
            }
            i--;
        }
    }
    if(!truckFileFound)
    {
        cerr << "ERROR: at least one truckfile required as input";
        exit(1);
    }
    if(!depotFileFound)
    {
        cerr << "ERROR: path to depot file required as input";
        exit(1);
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
        cerr << "ERROR: problem with depot file";
        exit(1);
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
        if(sp.bad())
        {
            cerr << "ERROR in depot file expected double for x coordinate";
            exit(1);
        }
        sp >> c;
        sp >> y;
        if(sp.bad())
        {
            cerr << "ERROR in depot file expected double for x coordinate";
            exit(1);
        }
        warehouses[name] = shared_ptr<Warehouse>(new Warehouse(name,inventory,Point(x,y)));
        simObjList[name] = warehouses[name];
    }
}

void Model::updateAll(){
    time++;
    for(auto &o: simObjList){
        o.second->update();
    }
    //after update all the objects in the Model check about attack happend in the last hour
    for(auto c:choppers){
        string target_s = c->getAttackTarget();
        //means attack didn't activated on this chopper
        if(target_s=="") continue;
        //else
        //extract the target truck from the map
        shared_ptr<Truck> target = dynamic_pointer_cast<Truck>(vehicles[target_s]);
        int range = c->getRange();
       
        //if the truck in this chopper range and there are no troppers in the area
        //the attack will succeed
        if(getDistance(c->getCurLocation(),target->getCurLocation())*100 > range
          || trooperInRadius(target->getLocation()))
        {
            //reduce chopper's range if the attack failed
            if(range>2) c->setRange(range-1);
            cout << c->getName() << " attack failed\n";
        }
        else{

            target->attack();
            //anhance the chopper's rang if the attack succeed
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
    //means the object isn't in the map
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

//overloaded for Trooper
void Model::createVehicle(const string& name, const string& target){
    //there is a object with this name in the model
    if(simObjList.find(name) != simObjList.end()){
        throw invalidCommandException("Erorr: vehicle name wasn't found.");
    }
    if(!containsObj(WAREHOUSE,target)){
        throw invalidCommandException("ERROR: warehouse name does not exist");
    }
    vehicles[name] = genericFactory<Vehicle>::instance().create("trooper",name);
    simObjList[name] = dynamic_pointer_cast<SimObject>(vehicles[name]);
    vehicles[name]->setCurLocation(warehouses[target]->getLocation());
    vehicles[name]->setSpeed(90);
    dynamic_pointer_cast<Trooper>(vehicles[name])->buildCourse(target);
    troopers.push_back(dynamic_pointer_cast<Trooper>(vehicles[name]));
}

//overloaded for Chopper
void Model::createVehicle(const string& name, double x, double y){
    if(simObjList.find(name) != simObjList.end()){
       throw invalidCommandException("Erorr: vehicle name wasn't found.");
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
        throw invalidCommandException("Erorr: vehicle name wasn't found or wrong type.");
    }
    vehicles[name]->setCourse(course);
}
void Model::setVehicleCourse(const string& name, double course, double speed){
    if(getObjectType(name) != CHOPPER){
            throw invalidCommandException("Erorr: vehicle name wasn't found or wrong type.");
    }
    vehicles[name]->setCourse(course);
    vehicles[name]->setSpeed(speed);
}

void Model::setVehiclePosition(const string& name, double x, double y){
    if(getObjectType(name) != TROOPER){
        throw invalidCommandException("Erorr: vehicle name wasn't found or wrong type.");
    }
    vehicles[name]->setPosition(x,y);
}
void Model::setVehiclePosition(const string& name, double x, double y, double speed){
    if(getObjectType(name) != CHOPPER){
        throw invalidCommandException("Erorr: vehicle name wasn't found or wrong type.");
    }
    vehicles[name]->setPosition(x,y);
    vehicles[name]->setSpeed(speed);
}

void Model::setVehicleDestination(const string& name,const string& WHname){
    if(getObjectType(name) != TROOPER){
        throw invalidCommandException("Erorr: vehicle name wasn't found or wrong type.");
    }
    if(!containsObj(WAREHOUSE,WHname)){
        throw invalidCommandException("ERROR: warehouse name does not exist");
    }
    dynamic_pointer_cast<Trooper>(vehicles[name])->buildCourse(WHname);
}

void Model::attack(const string& name, const string& target){
    if(getObjectType(name) != CHOPPER){
        throw invalidCommandException("Erorr: Attacker name wasn't found or wrong type.");
    }if(getObjectType(target) != TRUCK){
        throw invalidCommandException("Erorr: target name wasn't found or wrong type.");
    }
    dynamic_pointer_cast<Chopper>(vehicles[name])->attack(target);
}

void Model::stopVehicle(const string& name){
    if(getObjectType(name) == WAREHOUSE || getObjectType(name) == NONE){
        throw invalidCommandException("ERROR: name supplied does not exist or is not a vehicle");
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
    for(const auto& w: warehouses)
    {
        w.second->broadcastState(cout);
    }
    for(const auto& t: trucks)
    {
        t->broadcastState(cout);
    }
    for(const auto& c: choppers)
    {
        c->broadcastState(cout);
    }
    for(const auto& t: troopers)
    {
        t->broadcastState(cout);
    }
}