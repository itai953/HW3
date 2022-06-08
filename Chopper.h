#ifndef CHOPPER_H
#define CHOPPER_H
#include "Vehicle.h"
class Chopper: public Vehicle{
    string heading();
public:
    Chopper(const string& name):Vehicle(name){ }
    void attack(const string& target);
    virtual void update(){}
    static Chopper* createInstance(const string& param){ return new Chopper(param);}
    virtual ostream& broadcastState(ostream& out);
    // virtual const Point& getLocation() const {return Point(); }
};

#endif