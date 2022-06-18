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
        //todo throw something
        cerr<<"file problem";
        exit(1);
    }
    getline(file, line);
    readFirstLine(line);

    u_int line_number = 1;
    while (getline(file, line)) {
        readTruckFileLine(line,++line_number);}
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
    shared_ptr<Warehouse> warehouse = Model::getInstance().getWarehousePointer(originName);
    stops.emplace_back(warehouse, 0, startTime, 0);
}

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
    if (!(Model::getInstance().containsObj(Model::WAREHOUSE, name))) {
        cerr<<"in file "<<Vehicle::getName()<<".txt in line"<<lineNumber<<" warehouse: \""<<name<<"\" does not exists\n";
        exit(1);
    }
    float arrival =  Model::hourToDecimal(arrival_s);
    float departure = Model::hourToDecimal(departure_s);
    u_int amount = stoi(amount_s);
    shared_ptr<Warehouse> warehouse = Model::getInstance().getWarehousePointer(name);
    stops.emplace_back(warehouse, arrival, departure, amount);
    numCrates+=amount;
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


void Truck::truckFileReader() {

}

void Truck::countArrDep(int& arr, int& dep,float time){
    for(auto& s : stops){
        if(s.arrival <= time) arr++;
        if(s.departure <= time) dep++;
        else break;
    }
}

void Truck::update(){
    float time = MODEL().getTime();
    updateHelper(time-1, time);

}
//todo very risky function check
void Truck::updateHelper(float currTime, float nextTime){
    if(stops.front().arrival > nextTime){
        move(nextTime - currTime);
    }  else if(currTime <= stops.front().arrival){
        curLocation = stops.front().nextStop->getLocation();
        *(stops.front().nextStop)+=stops.front().qty;        numCrates -= stops.front().qty;
        status = TrackBase::PARKED;
        updateHelper(stops.front().arrival+0.01,nextTime);
    }

    else if(stops.front().departure <= nextTime){
        float t = stops.front().departure;
        stops.pop_front();
        normalDeg = calculateAngle(curLocation,stops.front().nextStop->getLocation());
        course = calculateCourse(curLocation,stops.front().nextStop->getLocation());
        speed = calculateSpeed(curLocation,stops.front().nextStop->getLocation(),stops.front().arrival-t);
        status = TrackBase::MOVING;
        updateHelper(t,nextTime);
    }
}



