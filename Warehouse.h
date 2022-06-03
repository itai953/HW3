#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include "SimObject.h"

/* 
 * class Warehouse is a simulation object, it is static (does not change location)
 * data members: 
 * inevntory: unsigned int, current number of crates in warehouse
 * location: Point, warehouse location
 */
using u_int = unsigned int;
class Warehouse: public SimObject {
    u_int inventory;
    Point location;
public:
    //c'tor
    Warehouse(const string& name,u_int _inventory):SimObject(name),inventory(_inventory){ }
    //update does nothing, inventory will be updated by trucks
    virtual void update(){ }
    //operator +=, -= overloads to update inventory
    void operator+=(int add_crates){ inventory += add_crates;}
    void operator-=(int take_crates){inventory -= take_crates;}
    //imp of SimObject getLocation
    virtual const Point& getLocation() const {return location;}
};

#endif