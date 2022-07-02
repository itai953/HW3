#ifndef TRACKBASE
#define TRACKBASE

#include "Geometry.h"
typedef unsigned int u_int;

/* 
 * class TrackBase is a class that tracks the vehicles in the game including their status,
 * speed, location, course, and target location
 */
class TrackBase{
protected:
    double speed; //vehicle speed - relevent only if status is MOVING
    Point curLocation; //the current location
    u_int status;
    bool heading_to; //for status print usage
    double course; //course of movement
    double normalDeg; //course in normal cartesian angle measurement
    Point position; //the target location
public:
    enum STATUS{STOPPED,PARKED,OFFROAD,MOVING};

    //c'tor
    TrackBase():speed(0),status(PARKED){ }
    
    //getters
    const Point& getCurLocation() const{return curLocation;}
    double getCourse(){return course;}
    u_int getStatus(){return status;}

    //setters
    void setStatus(u_int _status){status = _status;}
    void setCourse(double _course);
    void setNormalDeg(double theta);
    void setPosition(double x, double y);
    void setPosition(Point p){setPosition(p.x,p.y);}
    void setSpeed(double _speed){speed = _speed;}
    void setCurLocation(const Point& p){curLocation = p;}
    
    /*move the vehicle according to status speed and course
    * @param time the time the vehicle is moved in hours (default 1 hour)
    */
    void move(float time =1);
};


#endif