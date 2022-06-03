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
    string name;
public:
    //c'tor
    SimObject(const string& _name):name(_name){ }
    
    //getter
    const string& getName() const { return name;}
    
    //to be implemented in extending classes
    virtual void update() = 0;
    virtual void broadcastState() = 0;
    virtual const Point& getLocation() const = 0;
    
    //d'tor
    virtual ~SimObject() { }
};


#endif