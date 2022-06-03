#ifndef TRUCK
#define TRUCK
#include "Vehicle.h"
#include <string>
#include<list>

using namespace std;

typedef struct stopNode{
    Warehouse* nextStop;
    u_int arrival;
    u_int departure;
    u_int qty;
}stopNode;

class Truck : public Vehicle
{
    u_int numCrates;
    list<stopNode> stops;

    u_int timeConverter(string time);
    void truckFileReader();

    public:
        Truck(){;}
        void init(string filePath);
        void attack();
        void update();

};

#endif