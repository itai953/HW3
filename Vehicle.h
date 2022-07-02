#ifndef VEHICLE
#define VEHICLE
#include "TrackBase.h"
#include "Warehouse.h"

/* class Vehicle is a base class for the SimObjects that represent vehicles in the game
 * inherits from TrackBase
 */
class Vehicle :public SimObject, public TrackBase
{
    public:
        //c'tors
        Vehicle(const string& name):SimObject(name),TrackBase(){ }

        //the usage of this class in the program does not use copy or move c'tor
        Vehicle(const Vehicle& v) = delete;
        Vehicle(Vehicle&& v) = delete;

        //assignment operators also not needed
        Vehicle& operator=(const Vehicle& rhs) = delete;
        Vehicle& operator=(Vehicle&& rhs) = delete;

        //d'tor
        virtual ~Vehicle(){ }

        //implementation of getLocation function
        virtual const Point& getLocation() const {return TrackBase::getCurLocation();}
};


#endif