#ifndef TROOPER_H
#define TROOPER_H
#include "Vehicle.h"
#include "Model.h"
#include <string>
#include <list>
#include <memory>

using namespace std;


class Trooper : public Vehicle
{
    list<weak_ptr<SimObject>> patrol;
public:
    Trooper(const string& name):Vehicle(name),patrol(){ }
  //  void destination( string warehouseName);
    //void position(double x, double y);
   // void course(double _course);
    void buildCourse(const string& startWH){} //TODO implement
    virtual void update(){};
    static Trooper* createInstance(const string& param){ return new Trooper(param);}
    virtual ostream& broadcastState(ostream&);
    string heading();
    // virtual const Point& getLocation() const{return Point(); }
};

#endif