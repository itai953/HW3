#ifndef MODEL_H
#define MODEL_H
#include <memory>
#include <vector>
#include <unordered_map>
#include <sstream>
#include "Truck.h"
#include "Trooper.h"
// #include "Chopper.h"
#include "Warehouse.h"
using u_int = unsigned int;
using obj_ptr = shared_ptr<SimObject>;
class Model{
    u_int curr_hour;
    u_int time;
    unordered_map<string,obj_ptr> simObjList;
    unordered_map<string,obj_ptr> warehouses;
    unordered_map<string,obj_ptr> vehicles;
    Model(u_int curr_hour = 0):curr_hour(0),time(0),simObjList(1),warehouses(1),vehicles(0){ }

public:
    enum TYPE{WAREHOUSE,TRUCK,TROOPER,CHOPPER};
    static Model& getInstance();
    void readDepotFile(const string& filePath);
    bool containsObj(TYPE t, const string& name);
    static u_int hourToDecimal(string& hour); 

    u_int getTime(){return time;}
    u_int setTime(u_int _time){time = _time;}

};


#endif