#ifndef TROOPER_H
#define TROOPER_H
#include "Vehicle.h"
#include "Model.h"
#include <string>
#include <list>
#include <memory>
#include <algorithm>

using namespace std;


class Trooper : public Vehicle
{

    //list of warehouses the Trooper is going to visit 
    //create buildCourse function 
    list<shared_ptr<SimObject>> patrol; 
    void updateHelper(float currTime,float nextTime);
    string heading(); //a function for internal use in broadcastState function
public:

    Trooper(const string& name):Vehicle(name),patrol(){ }//c'tor
    void buildCourse(const string& startWH);//function which build the patrol list
    virtual void update();// update Tropper status
    static Trooper* createInstance(const string& param){ return new Trooper(param);}
    virtual ostream& broadcastState(ostream&);//prints data about tropper's current status

    //setters
    virtual void setCourse(double theta);
    virtual void setPosition(double x, double y);
  
    //Trooper is create only by user command 
    //and since then we work only with pointers so no need for 
    //big five except from d'tor
    Trooper(const Trooper&) = delete;
    Trooper(Trooper&&) = delete;
    Trooper& operator=(const Trooper&) =delete;
    Trooper& operator=(Trooper&&) =delete;
    ~Trooper(){ }



};

#endif