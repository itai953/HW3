#ifndef MODEL_H
#define MODEL_H
#include <memory>
#include <vector>
#include "Truck.h"
#include "Trooper.h"
// #include "Chopper.h"
#include "Warehouse.h"
using u_int = unsigned int;
using obj_ptr = shared_ptr<SimObject>;
using wobj_ptr = weak_ptr<SimObject>;
class Model{
    u_int curr_hour;
    u_int time;
    vector<obj_ptr> SimObjList;
    vector<wobj_ptr> warehouses;
    vector<wobj_ptr> vehicles;
    Model(u_int curr_hour = 0):curr_hour(0),time(0),SimObjList(1),warehouses(1),vehicles(0){ }
public:
    static Model& getInstance();
};


#endif