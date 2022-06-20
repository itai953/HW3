#ifndef MODEL_H
#define MODEL_H
#include <memory>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include "Trooper.h"
#include "Chopper.h"
#include "Warehouse.h"

class Truck;
class Trooper;
using u_int = unsigned int;
using obj_ptr = shared_ptr<SimObject>;
class Model{
    float curr_hour;
    float time;
    unordered_map<string,obj_ptr> simObjList;
    unordered_map<string,shared_ptr<Warehouse>> warehouses;
    unordered_map<string,shared_ptr<Vehicle>> vehicles;
    vector<shared_ptr<Chopper>> choppers;
    vector<shared_ptr<Trooper>> troopers;
    Model(u_int curr_hour = 0);

public:
    enum TYPE{WAREHOUSE,TRUCK,TROOPER,CHOPPER,NONE};
    static Model& getInstance();
    void readDepotFile(const string& filePath);
    Model::TYPE getObjectType(const string& name);
    bool containsObj(TYPE t, const string& name);
    bool trooperInRadius(const Point& p, double r=10);
    const unordered_map<string, shared_ptr<SimObject>>& getSimObjList() const {return simObjList;}
    shared_ptr<SimObject>& getSimObject(const string& name){return simObjList[name];}
    vector<shared_ptr<Warehouse>> getWarehouses() const;
    const unordered_map<string,shared_ptr<Vehicle>>& getVehicles() const { return vehicles;}
    void init(vector<string>&& argv);
    static float hourToDecimal(string& hour);
    
    float getTime(){return time;}
    void setTime(float _time){time = _time;}
    void updateAll();
    void createVehicle(const string& name, const string& target);
    void createVehicle(const string& name, double x, double y);
    void setVehicleCourse(const string& name, double course);
    void setVehicleCourse(const string& name, double course, double speed);
    void setVehiclePosition(const string& name, double x, double y);
    void setVehiclePosition(const string& name, double x, double y, double speed);
    void setVehicleDestination(const string& name,const string& WHname);
    void attack(const string& name, const string& target);
    void stopVehicle(const string& name);
    void status() const;
    shared_ptr<Warehouse> getWarehousePointer(const string& name){return static_pointer_cast<Warehouse>(warehouses[name]);}
};

#endif