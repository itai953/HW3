#ifndef VEHICLE
#define VEHICLE
#include "TrackBase.h"
#include "Warehouse.h"

class Vehicle :public SimObject, public TrackBase
{

    public:
        Vehicle(const string& name):SimObject(name),TrackBase(){ }
        virtual const Point& getLocation() const {return TrackBase::getCurLocation();}
        // string& getName{return name;}
        // void update() = 0;
};

#endif