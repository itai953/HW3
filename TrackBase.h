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
    double normalDeg;
    Point position; //target
public:
    enum STATUS{STOPPED,PARKED,OFFROAD,MOVING};
    TrackBase():speed(0),status(PARKED){ }
    const Point& getCurLocation() const{return curLocation;}
    double getCourse(){return course;}
    u_int getStatus(){return status;}
    void setStatus(u_int _status){status = _status;} //TODO write real imp
    void setCourse(double _course);
    void setNormalDeg(double theta);
    void setPosition(double x, double y);
    void setPosition(Point p){setPosition(p.x,p.y);}
    void setSpeed(double _speed){speed = _speed;}
    void setCurLocation(const Point& p){curLocation = p;}
    void move(float time =1);
};


#endif