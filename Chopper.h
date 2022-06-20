#ifndef CHOPPER_H
#define CHOPPER_H
#include "Vehicle.h"
class Chopper: public Vehicle{
    string heading();
    string attackTarget;
    int range;
public:
    Chopper(const string& name):Vehicle(name),range(2){ }
    void attack(const string& target){attackTarget=target;};
    virtual void update(){move();}
    string getAttackTarget() const{return attackTarget;}
    void setRange(int r){range = r;}
    int getRange() const {return range;}
    static Chopper* createInstance(const string& param){ return new Chopper(param);}
    virtual ostream& broadcastState(ostream& out);
};

#endif