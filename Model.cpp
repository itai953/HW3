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
    int inventory; Point p;
    string name,point,inv;
    while(!f.eof()){
        getline(f,name,',');
        getline(f,point,')');
        f.ignore();
        getline(f,inv);
        stringstream(inv) >> inventory;
        stringstream sp(point);
        sp.ignore();
        sp >> p.x;
        sp.ignore();
        sp >> p.y;
    }
}

