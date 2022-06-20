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
    list<shared_ptr<SimObject>> patrol;
public:
    Trooper(const string& name):Vehicle(name),patrol(){ }
  //  void destination( string warehouseName);
    //void position(double x, double y);
   // void course(double _course);
    void buildCourse(const string& startWH);
    virtual void update(){};
    static Trooper* createInstance(const string& param){ return new Trooper(param);}
    virtual ostream& broadcastState(ostream&);
    string heading();
    // virtual const Point& getLocation() const{return Point(); }
};

#endif