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
    unordered_map<string,shared_ptr<Warehouse>> warehouses;
    unordered_map<string,shared_ptr<Vehicle>> vehicles;
    Model(u_int curr_hour = 0);

public:
    enum TYPE{WAREHOUSE,TRUCK,TROOPER,CHOPPER};
    static Model& getInstance();
    void readDepotFile(const string& filePath);
    bool containsObj(TYPE t, const string& name);
    static u_int hourToDecimal(string& hour); 
    const unordered_map<string, shared_ptr<SimObject>>& getSimObjList() const {return simObjList;}
    const unordered_map<string,shared_ptr<Warehouse>>& getWarehouses() const {return warehouses;}
    const unordered_map<string,shared_ptr<Vehicle>>& getVehicles() const { return vehicles;}
    u_int getTime() const {return time;}
    void setTime(u_int _time) {time = _time;}
    void init(vector<string>&& argv);
    

};

#endif