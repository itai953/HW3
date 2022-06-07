#ifndef CHOPPER_H
#define CHOPPER_H
#include "Vehicle.h"
class Chopper: public Vehicle{
public:
    Chopper(const string& name):Vehicle(name){ }
    void attack(const string& target);
    virtual void update();
    static Chopper* createInstance(const string& param){ return new Chopper(param);}
    virtual void broadcastState(){ }
    virtual const Point& getLocation() const { }
};

#endif