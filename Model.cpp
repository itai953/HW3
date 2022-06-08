#include "Model.h"

Model& Model::getInstance(){
    static Model inst;
    return inst;
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
        // sp.ignore();
        sp >> c;
        sp >> y;
        warehouses[name] = shared_ptr<Warehouse>(new Warehouse(name,inventory,Point(x,y)));
        simObjList[name] = dynamic_pointer_cast<SimObject>(warehouses[name]);
    }
}

