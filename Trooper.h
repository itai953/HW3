#ifndef TROOPER
#define TROOPER
#include "Vehicle.h"
#include <string>
#include <list>

using namespace std;


class Trooper : public Vehicle
{
    
   public:
        Trooper(string _name, string warehouseName);
        void destination( string warehouseName);
        void position(u_int x, u_int y);
        void course(double _course);
        virtual void update();

};

#endif