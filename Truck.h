#ifndef TRUCK_H
#define TRUCK_H
#include "Vehicle.h"
#include <string>
#include<list>
#include <fstream>

using namespace std;

typedef struct stopNode{
    Warehouse* nextStop;
    u_int arrival;
    u_int departure;
    u_int qty;
} StopNode;

class Truck : public Vehicle
{
    u_int numCrates;
    list<stopNode> stops;

    u_int timeConverter(string time);
    void truckFileReader();
    public:
        Truck(const string& name):Vehicle(name),numCrates(0){}
        void init(const string& fPath);
        static Truck* createInstance(const string& name){return new Truck(name);}
        void attack();
        void update(){};
        virtual void broadcastState(){ }
        virtual const Point& getLocation() const{return Point(); }

};

#endif