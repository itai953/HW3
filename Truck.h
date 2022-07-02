#ifndef TRUCK_H
#define TRUCK_H
#include "Vehicle.h"
#include <string>
#include <list>
#include <fstream>
#include "Model.h"

using namespace std;

//using by stops list which contains data about a warehouse on the truck course
struct StopNode{
    shared_ptr<Warehouse> nextStop; //pointer to the next warehouse the Truck going to visit
    float arrival; //when the truck going to get to the warehouse
    float departure; //when the truck going to leave the warehouse
    u_int qty;
    StopNode(const shared_ptr<Warehouse> &nextStop, float arrival, float departure, u_int qty) : nextStop(nextStop),arrival(arrival),departure(departure),qty(qty) {}
};

class Truck : public Vehicle
{
        u_int numCrates; //how many crates on the truck at the moment
        list<StopNode> stops; //list which contains data on the Truck course
        void readTruckFileLine(string &line,u_int lineNumber); //this function parse the first line in Truck file input
        void readFirstLine(string &line);
        void updateHelper(float currTime, float nextTime);
    public:
        //the only c'tor for Truck
        Truck(const string& name):Vehicle(name),numCrates(0){}// the only c'tor for Truck

        void init(const string& fPath); // a builder helper for Truck
        
        void attack();
        void update();

        virtual ostream& broadcastState(ostream& out); //prints data about truck current status

        static Truck* createInstance(const string& name){return new Truck(name);} 

        //Truck is create only from a input file
        //and since then we are working only with pointers
        //so no need for big five except from d'tor 
        Truck(const Truck&) = delete;
        Truck(Truck&&) = delete;
        Truck& operator=(const Truck&) =delete;
        Truck& operator=(Truck&&) =delete;
        ~Truck(){}


};

#endif