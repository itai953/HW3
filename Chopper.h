#ifndef CHOPPER_H
#define CHOPPER_H
#include "Vehicle.h"
class Chopper: public Vehicle{
public:
    // Chopper(const string& name, )
    void attack(const string& target);
    virtual void update();

};

#endif