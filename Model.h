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

//forward declarations
class AsciiView;
class Truck;
class Trooper;

//typedefs
using u_int = unsigned int;
using obj_ptr = shared_ptr<SimObject>;

/* 
 * class Model is a singleton, holds all the information about the objects in the game world
 */
class Model{
    //current time
    float time;
    unordered_map<string,obj_ptr> simObjList; // all objects in the game
    unordered_map<string,shared_ptr<Warehouse>> warehouses; //only the Warehouse objects
    unordered_map<string,shared_ptr<Vehicle>> vehicles; //only the Vehicle objects
    vector<shared_ptr<Chopper>> choppers; //only the Chopper objects
    vector<shared_ptr<Trooper>> troopers; //only the Trooper objects
    vector<shared_ptr<Truck>> trucks;//only the Truck objects
    //private c'tor
    Model();

    //rule out copy or move operations
    Model(const Model&) = delete;
    Model(Model&&) = delete;
    Model& operator=(const Model&) = delete;
    Model& operator=(Model&&) = delete;
    
    //view - in this program only AsciiView
    shared_ptr<AsciiView> view;
public:
    
    /* 
     * initialize the Model
     * @param argv the arguments supplied to program at execution 
     */
    void init(vector<string>&& argv);


    //an invalid command exception nested class
    class invalidCommandException
    {
        string msg;
    public:
        invalidCommandException(const string& m):msg(m){ }
        string getMsg() const {return msg;}
    };
    //object types enum
    enum TYPE{WAREHOUSE,TRUCK,TROOPER,CHOPPER,NONE};
    static Model& getInstance(); //the singleton instance getter

    //functino to read the depot file in initialization
    void readDepotFile(const string& filePath);

    //get the type of the object with name equal to param name
    Model::TYPE getObjectType(const string& name);

    //check if the Model contains a SimObject with name = name and type = t
    bool containsObj(TYPE t, const string& name);

    //check if a Trooper is located in radius r from location p for the attack process
    bool trooperInRadius(const Point& p, double r=10);

    //get the SimObjects map
    const unordered_map<string, shared_ptr<SimObject>>& getSimObjList() const {return simObjList;}
    
    //get the SimObject with name = name
    shared_ptr<SimObject>& getSimObject(const string& name){return simObjList[name];}
    
    //get a vector of all the Warehouses in the game
    vector<shared_ptr<Warehouse>> getWarehouses() const;

    //get the map of all vehicles in the game currently
    const unordered_map<string,shared_ptr<Vehicle>>& getVehicles() const { return vehicles;}
    
    //convert a string in format HH:MM to float
    static float hourToDecimal(string& hour);

    //attach a view object to Model
    void attach(shared_ptr<AsciiView> v){ view = v;}
    
    //getter for time member
    float getTime(){return time;}

    //setter for time member
    void setTime(float _time){time = _time;}

    //update all objects in the game (move ahead 1 hour)
    void updateAll();

    //create a vehicle - Trooper
    void createVehicle(const string& name, const string& target);
    //create a vehicle - Chopper overload
    void createVehicle(const string& name, double x, double y);
    
    //set vehicle's course
    //param name = vehicle's name
    //param course = new course
    void setVehicleCourse(const string& name, double course);
    //overload for Chopper - also takes speed argument for new speed to assign
    void setVehicleCourse(const string& name, double course, double speed);

    //set vehicle's position
    //param name = vehicle's name
    //params x,y = new position coordinates
    void setVehiclePosition(const string& name, double x, double y);
    //overload for Chopper also takes param speed for new soeed to assign
    void setVehiclePosition(const string& name, double x, double y, double speed);
    
    //set a Trooper's destination to a new warehouse - WHname
    void setVehicleDestination(const string& name,const string& WHname);
    
    //set an attack target for chopper
    //param name = Chopper's name
    //param target = target truck's name
    void attack(const string& name, const string& target);

    //stop a vehicle
    void stopVehicle(const string& name);

    //print the status for all objects
    void status() const;

    //get a shared_ptr<Warehouse> to warehouse
    //param name = warehouse's name
    shared_ptr<Warehouse> getWarehousePointer(const string& name){return static_pointer_cast<Warehouse>(warehouses[name]);}
};

#endif