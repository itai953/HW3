#include "Truck.h"
#include <sstream>
#include "factory.h"
#include "Model.h"

auto MODEL = Model::getInstance;
registerInFactory<Vehicle, Truck> rtruck("truck");



void Truck::init(const string &fPath) {
    
    string line, token;
    ifstream file(fPath);
    if (!file) {
        cerr<<"file problem";
        exit(1);
    }
    getline(file, line);
    readFirstLine(line);

    u_int line_number = 1;
    while (getline(file, line)) {
        readTruckFileLine(line,++line_number);}
    curLocation = stops.front().nextStop->getLocation();
    *(stops.front().nextStop)-=numCrates;
    status = PARKED;
    
}


void Truck::readFirstLine(string &line){
    if (line[line.size()-1] =='\r'){line.pop_back();}
    stringstream firstLine(line);
    string originName, startTime_s;
    char temp;

    getline(firstLine, originName, ',');
    getline(firstLine, startTime_s);

    if (firstLine >> temp) {
        cerr<<"too many arguments at file"<<Vehicle::getName()<<".txt at line 1\n";
        exit(1);
    }

    //check if warehouse name is in the model
    if (!(Model::getInstance().containsObj(Model::WAREHOUSE, originName))) {
        cerr<<"in file "<<Vehicle::getName()<<".txt in line 1"<<" warehouse: \""<<originName<<"\" does not exists\n";
        exit(1);
    }

    //get a decimal hour out of string
    float startTime = Model::hourToDecimal(startTime_s);

    //if this truck starting time is earlier than current earliest change Model starting time
    if (Model::getInstance().getTime() > startTime) {
        Model::getInstance().setTime(startTime);
    }
    //after checking if waehouse is exists in the model we can ask for it's pointer
    shared_ptr<Warehouse> warehouse = Model::getInstance().getWarehousePointer(originName);

    //add data about this warehouse stop to stops list
    stops.emplace_back(warehouse, 0, startTime, 0);
}


//this function parse all the other lines in truck input file
void Truck::readTruckFileLine( string &line, u_int lineNumber){
    if (line[line.size()-1] =='\r'){line.pop_back();}

    string arrival_s, departure_s, name, amount_s;
    char temp;

    stringstream ss(line);
    getline(ss, name, ',');
    getline(ss, arrival_s, ',');
    getline(ss, amount_s, ',');
    getline(ss, departure_s);

    if (ss >> temp) {
        cerr<<"too many arguments at file"<<Vehicle::getName()<<".txt at line "<<lineNumber<<endl;
        exit(1);
    }

    //check if warehouse name is in the model
    if (!(Model::getInstance().containsObj(Model::WAREHOUSE, name))) {
        cerr<<"in file "<<Vehicle::getName()<<".txt in line"<<lineNumber<<" warehouse: \""<<name<<"\" does not exists\n";
        exit(1);
    }
    //get a decimal hour out of string
    float arrival =  Model::hourToDecimal(arrival_s);
    float departure = Model::hourToDecimal(departure_s);

    u_int amount = stoi(amount_s);
    numCrates+=amount;

    //after checking if waehouse is exists in the model we can ask for it's pointer
    shared_ptr<Warehouse> warehouse = Model::getInstance().getWarehousePointer(name);

    //add data about this warehouse stop to stops list
    stops.emplace_back(warehouse, arrival, departure, amount);
    
}


ostream& Truck::broadcastState(ostream& out){
    out<<"Truck "<<Vehicle::SimObject::name;
    if(Vehicle::TrackBase::getStatus() == Vehicle::TrackBase::MOVING){
        out<<" at "<<Vehicle::TrackBase::curLocation;
        out<<" Heading to "<<stops.front().nextStop->getName();
        out<<" Crates: "<<numCrates;
    }
    if (Vehicle::TrackBase::getStatus() == Vehicle::TrackBase::STOPPED)
    {
        out<<" stopped at: "<<Vehicle::TrackBase::curLocation;
    }
     if (Vehicle::TrackBase::getStatus() == Vehicle::TrackBase::PARKED)
    {
        out<<" parked at: "<<Vehicle::TrackBase::curLocation;
    }
     if (Vehicle::TrackBase::getStatus() == Vehicle::TrackBase::OFFROAD)
    {
        out<<" off road at: "<<Vehicle::TrackBase::curLocation;
    }  
    out<<endl;
    return out;
}



//update truck status after one hour
void Truck::update(){
    if(status == STOPPED)
        return;
    float time = MODEL().getTime();
    updateHelper(time-1, time);
}

//a recursive function helper to update
//simulate the truck course in time range of one hour
//input: currTime - thime within the last round hour to the next one
//nextTime : next rounded hour
void Truck::updateHelper(float currTime, float nextTime){

    //stopping condition: if next stop arrival time isn't before
    //the next round hour we can just move the truck on the current direction
    if(stops.front().arrival > nextTime){
        move(nextTime - currTime);

    //means we can "forward" currTime to the ariival time of the nextStop
    //and marked the truck as it arrived to the stop
    }else if(currTime < stops.front().arrival ){
        curLocation = stops.front().nextStop->getLocation();
        *(stops.front().nextStop)+=stops.front().qty;       
        numCrates -= stops.front().qty;
        status = TrackBase::PARKED;
        updateHelper(stops.front().arrival,nextTime);
    }

    //means the truck should leave the current warehouse
    else if(stops.front().departure < nextTime){
        float t = stops.front().departure;
        stops.pop_front();

        //if this was the last stop in the truck course
        if(stops.empty())
        {
            status = STOPPED;
            return;
        }

        //set the course for the next ride
        setPosition(stops.front().nextStop->getLocation());
        speed = calculateSpeed(curLocation,stops.front().nextStop->getLocation(),stops.front().arrival-t);
        status = TrackBase::MOVING;
        updateHelper(t,nextTime);
    }
}

//truck attacked only if all the ataack conditons passed
void Truck::attack(){
    status = TrackBase::OFFROAD;
    numCrates = 0;
}


