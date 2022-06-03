#ifndef VEHICLE
#define VEHICLE
#include "TrackBase.h"
#include "WareHouse.h"

class Vehicle :public SimObject, public TrackBase
{
    string name;
    public:
        Vehicle(const string& name):SimObject(name),TrackBase(){ }
        // string& getName{return name;}
        // void update() = 0;
};

#endif