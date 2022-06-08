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

    while (getline(file, line)) {
        readTruckFileLine(line);}
}

void Truck::readFirstLine(string &line){
    if (line[line.size()-1] =='\r'){line.pop_back();}
    stringstream firstLine(line);
    string originName, startTime_s;
    char temp;

    getline(firstLine, originName, ',');
    getline(firstLine, startTime_s);

    //todo
    if (firstLine >> temp) {
        //todo throw something
    }
    if (!(Model::getInstance().containsObj(Model::WAREHOUSE, originName))) {
        //todo throw
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

void Truck::readTruckFileLine( string &line){
    if (line[line.size()-1] =='\r'){line.pop_back();}

    string arrival_s, departure_s, name, amount_s;
    char temp;

    stringstream ss(line);
    getline(ss, name, ',');
    getline(ss, arrival_s, ',');
    getline(ss, amount_s, ',');
    getline(ss, departure_s);

    if (ss >> temp) {
        //todo maybe get more info
        cerr<<"too many arguments\n";
        exit(1);
    }
    if (!(Model::getInstance().containsObj(Model::WAREHOUSE, name))) {
        //todo maybe get more info
        cerr<<"warehouse :\""<<name<<"\" does not exists\n";
        exit(1);
    }
    u_int arrival =  Model::hourToDecimal(arrival_s);
    u_int departure = Model::hourToDecimal(departure_s);
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






