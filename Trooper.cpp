#include "Trooper.h"
#include "factory.h"

registerInFactory<Vehicle, Trooper> rt("trooper");


string Trooper::heading(){
    stringstream ss;
    ss << " heading";
    if(Vehicle::TrackBase::heading_to){
        ss<<" to ";
        if (patrol.empty()){
            ss<<Vehicle::TrackBase::position<<",";
        }
        else{
             ss<<patrol.front()->getName();
        }
    }
    else{
        ss<< " on " << Vehicle::TrackBase::course<<" deg,";
    }
    return ss.str();
}

ostream& Trooper::broadcastState(ostream& out){
    out<<"State_trooper "<<Vehicle::SimObject::name<<" ";
    if(Vehicle::TrackBase::getStatus() == Vehicle::TrackBase::MOVING){
        out<<" at "<<Vehicle::TrackBase::curLocation;
        out<<heading()<<" speed " <<speed<<"km/h";

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
    return out<<"\n";
}

void Trooper::buildCourse(const string& startWH){
    vector<shared_ptr<Warehouse>>&& warehouses = Model::getInstance().getWarehouses();
    
    shared_ptr<Warehouse> curr = Model::getInstance().getWarehousePointer(startWH);
    //iterate over warehouses and find the closest warhouse to the last warehouse in patrol
    //which you didn't "visit" yet and add it to patrol and remove it from warehouses. 
    //If you visited all warehouses, then you are done.
    patrol.clear();
    while(!warehouses.empty()){
        sort(warehouses.begin(), warehouses.end(), 
        [&](shared_ptr<Warehouse> a, shared_ptr<Warehouse> b){
            double da,db;
            da = getDistance(a->getLocation(),curr->getLocation());
            db = getDistance(b->getLocation(),curr->getLocation());
            if(da == db){
                return a->getName() < b->getName();
            }else {
                return da < db;
            }
        });
        patrol.push_back(warehouses[0]);
        curr = warehouses[0];
        warehouses.erase(warehouses.begin());
    
    }
    patrol.push_back(patrol.front());
    if(curLocation==patrol.front()->getLocation()){
        patrol.pop_front();
    }
    TrackBase::setPosition(patrol.front()->getLocation());
}

void Trooper::updateHelper(float currTime, float nextTime){
    //means trooper won't arrive to a warehouse in this range of one hour
    if(getDistance(curLocation,patrol.front()->getLocation()) > 0.9){
        status = MOVING;
        move(nextTime-currTime);
    }

    //means trooper arrive and right a away leaving a warehouse 
    else{
        //calculate when the trooper will get to the next next warehouse
        double time = (getDistance(curLocation,patrol.front()->getLocation()) * 100) / speed;
        
        //move to the next warehouse   
        curLocation = patrol.front()->getLocation();

        //pop warehouse from the list
        patrol.pop_front();
        if(patrol.empty()){
            status = TrackBase::PARKED;
            speed = 0;
            return;
        }
        //set the target for the next warehouse
        TrackBase::setPosition(patrol.front()->getLocation());
        updateHelper(currTime+time,nextTime);
    }
}

void Trooper::update(){
    //happens in tow situations
    //1.Tropper is driving on course and not to a praticular warehouse
    //2.Trroper is in PARKED status then it's speed is zero and position is where it's parked
    if(patrol.empty()){
        move();
    }  
    else{
        float time = Model::getInstance().getTime();
        updateHelper(time-1,time);
    }
}

void Trooper::setCourse(double theta){
    heading_to = false;
    patrol.clear();
    TrackBase::setCourse(theta);
}


void Trooper::setPosition(double x, double y){
    heading_to = false;
    patrol.clear();
    TrackBase::setPosition(x,y);
}
