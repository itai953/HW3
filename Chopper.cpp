#include "Chopper.h"
#include "factory.h"
#include <sstream>

registerInFactory<SimObject, Chopper> rc("chopper");

string Chopper::heading(){
    string st = "Heading";
    stringstream ss(st);
    if(Vehicle::TrackBase::heading_to){
        ss<<" to "<<Vehicle::TrackBase::position<<",";
    }
    else{
        ss<< " on " << Vehicle::TrackBase::course<<" deg,";
    }
    return ss.str();
}

ostream& Chopper::broadcastState(ostream& out){
    out<<"Chopper "<<Vehicle::SimObject::name;
    if(Vehicle::TrackBase::getStatus() == Vehicle::TrackBase::MOVING){
        out<<" at "<<Vehicle::TrackBase::curLocation;
        out<<heading()<<" speed " <<speed<<"km/h\n";

    }
    if (Vehicle::TrackBase::getStatus() == Vehicle::TrackBase::STOPPED)
    {
        out<<"stopped at: "<<Vehicle::TrackBase::curLocation;
    }
     if (Vehicle::TrackBase::getStatus() == Vehicle::TrackBase::PARKED)
    {
        out<<"parked at: "<<Vehicle::TrackBase::curLocation;
    }
     if (Vehicle::TrackBase::getStatus() == Vehicle::TrackBase::OFFROAD)
    {
        out<<"off road at: "<<Vehicle::TrackBase::curLocation;
    }  
    return out;
}