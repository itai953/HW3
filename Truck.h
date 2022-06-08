#ifndef TRUCK_H
#define TRUCK_H
#include "Vehicle.h"
#include <string>
#include <list>
#include <fstream>
#include "Model.h"

using namespace std;
struct StopNode{
    shared_ptr<Warehouse> nextStop;
    float arrival;
    float departure;
    u_int qty;
    StopNode(const shared_ptr<Warehouse> &nextStop, float arrival, float departure, u_int qty) : nextStop(nextStop),arrival(arrival),departure(departure),qty(qty) {}
};

class Truck : public Vehicle
{
    u_int numCrates;
    list<StopNode> stops;
    void readTruckFileLine(string &line);
    void readFirstLine(string &line);
    void truckFileReader();
    public:
        Truck(const string& name):Vehicle(name),numCrates(0){}
        void init(const string& fPath);
        static Truck* createInstance(const string& name){return new Truck(name);}
        void attack(){};
        void update(){};
        virtual ostream& broadcastState(ostream& out);
        // virtual const Point& getLocation() const{return Point(); }
};

#endif