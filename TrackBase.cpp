#include "TrackBase.h"

void TrackBase::move(float time){
    Polar_vector pv;
    pv.r = (speed*time)/100;
    pv.theta = normalDeg;
    Cartesian_vector cv(pv);
    curLocation.x += cv.delta_x;
    curLocation.y += cv.delta_y;
}