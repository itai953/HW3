#include "TrackBase.h"
#include <cmath>
void TrackBase::move(float time){
    double delta = (speed*time)/100;
    curLocation.x += cos(to_radians(normalDeg))*delta;
    curLocation.y += sin(to_radians(normalDeg))*delta;
}



void TrackBase::setCourse(double _course){
    course = _course;
    normalDeg = normalizeAngle(course);
}

void TrackBase::setNormalDeg(double theta){
    normalDeg = theta;
    course = normalizeAngle(theta);
}

void TrackBase::setPosition(double x, double y){
    position.x = x; position.y = y;
    double theta = calculateAngle(curLocation,position);
    setNormalDeg(theta);
}