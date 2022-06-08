#include "Chopper.h"
#include "factory.h"


registerInFactory<SimObject, Chopper> rc("chopper");

string Chopper::heading(){
    if(Vehicle::TrackBase::heading_to){
        return "Heading to : "<< Vehicle::TrackBase::position;
    }
    return "Heading on course "<< Vehicle::TrackBase::course<<" deg,";
}

ostream& Chopper::broadcastState(ostream& out){
    out<<"Chopper "<<Vehicle::SimObject::name;
    if(Vehicle::TrackBase::getStatus() == Vehicle::TrackBase::MOVING){
        out<<" at "<<Vehicle::TrackBase::curLocation;
        out<<" Heading to "<<stops.front().nextStop->getName();
        out<<" Crates: "<<numCrates;
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