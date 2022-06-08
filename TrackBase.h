#ifndef TRACKBASE
#define TRACKBASE

#include "Geometry.h"
typedef unsigned int u_int;

class TrackBase{
protected:
    double speed;
    Point curLocation;
    u_int status;
    bool heading_to;
    double course;
    Point position; //target
public:
    enum STATUS{STOPPED,PARKED,OFFROAD,MOVING};
    TrackBase(){ };
    TrackBase(double speed, Point curLoc,double _course,Point target = Point(0,0),int status = STOPPED);
    const Point& getCurLocation() const{return curLocation;}
    double getCourse(){return course;}
    u_int getStatus(){return status;}
    void setStatus(u_int _status);
    void setCourse(double _course);
    void setposition(double x, double y);
    void setSpeed(double _speed){speed = _speed;}
};


#endif