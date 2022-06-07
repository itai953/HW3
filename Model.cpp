#include "Model.h"

Model& Model::getInstance(){
    static Model inst;
    return inst;
}


bool Model::containsObj(TYPE t, const string& name){
    auto it = simObjList.find(name);
    switch(t){
        case WAREHOUSE:
            return it != simObjList.end() && typeid(*it).name() == "Warehouse";
        case TROOPER:
            return it != simObjList.end() && typeid(*it).name() == "Trooper";
        case TRUCK:
            return it != simObjList.end() && typeid(*it).name() == "Truck";
        case CHOPPER:
            return it != simObjList.end() && typeid(*it).name() == "Chopper";
    }
    return false;
}

u_int Model:: hourToDecimal(string& hour){
    hour[2] = ' ';
    stringstream ss(hour);
    int decHour;
    int decMins;
    ss>>decHour;
    ss>>decMins;
    decHour+= decMins/60;
    return decHour;
}

    

