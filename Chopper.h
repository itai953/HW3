#ifndef CHOPPER_H
#define CHOPPER_H
#include "Vehicle.h"
/*
 * class Chopper is a robber Motorcycle in the game 
 * data members:
 * attackTarget: a truck to attack in next time step, if empty string then no attack assigned to chopper
 * range: the radius of the chopper's attack range
 */

class Chopper: public Vehicle{
    string heading(); //a function for internal use in broadcastState function
    string attackTarget;
    int range;
public:
    //c'tpr
    Chopper(const string& name):Vehicle(name),range(2){ }
    
    //set attack target
    void attack(const string& target){attackTarget=target;};
    
    virtual void update(){move();}
    
    //getters
    string getAttackTarget() const{return attackTarget;}
    int getRange() const {return range;}
    
    //setter
    void setRange(int r){range = r;}
    
    //for the abstract factory
    static Chopper* createInstance(const string& param){ return new Chopper(param);}
    
    //implementation of the base class broadcastState
    virtual ostream& broadcastState(ostream& out);

    //Chopper is create only by user command 
    //and since then we work only with pointers so no need for 
    //big five except from d'tor
    Chopper(const Chopper&) = delete;
    Chopper(Chopper&&) = delete;
    Chopper& operator=(const Chopper&) =delete;
    Chopper& operator=(Chopper&&) =delete;
    ~Chopper(){ }



};

#endif