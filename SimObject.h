#ifndef SIMOBJECT_H
#define SIMOBJECT_H
#include <iostream>
#include "Geometry.h"
using namespace std;
/*
 * class SimObject is an abstract class defining general behaviour of an object in the simulation world
 * all objects in the simulation implement and extend this class
 */

class SimObject{
protected:
    string name;
public:
    //c'tor
    SimObject(const string& _name):name(_name){ }
    SimObject(SimObject&&) = default;
    SimObject(const SimObject&) = default;

    //assignment
    SimObject& operator=(const SimObject&) = default;
    SimObject& operator=(SimObject&&) = default;

    //getter
    const string& getName() const { return name;}
    
    //to be implemented in extending classes
    virtual void update() = 0;

    virtual ostream& broadcastState(ostream& out) = 0;
    virtual const Point& getLocation() const = 0;
    string& getName(){return name;}
    //d'tor
    virtual ~SimObject() = default;
};


#endif