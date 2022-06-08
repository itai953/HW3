#include "Model.h"
#include "factory.h"
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
            return it != simObjList.end() && typeid(*(it->second.get())).name() == "Warehouse";
        case TROOPER:
            return it != simObjList.end() && typeid(*(it->second.get())).name() == "Trooper";
        case TRUCK:
            return it != simObjList.end() && typeid(*(it->second.get())).name() == "Truck";
        case CHOPPER:
            return it != simObjList.end() && typeid(*(it->second.get())).name() == "Chopper";
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
        simObjList[name] = dynamic_pointer_cast<SimObject>(warehouses[name]);
    }
}

