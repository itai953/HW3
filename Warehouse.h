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
    Warehouse(const string& name,u_int _inventory,const Point& loc):SimObject(name),inventory(_inventory),location(loc){ }
    Warehouse(const Warehouse& wh):SimObject(wh.getName()),inventory(wh.inventory),location(wh.location){ }
    Warehouse(Warehouse&& wh):SimObject(dynamic_cast<SimObject&&>(wh)),inventory(wh.inventory),location(wh.location){ }
    
    //assignment
    Warehouse& operator=(const Warehouse& rhs)
    {
        SimObject::operator=(rhs);
        inventory = rhs.inventory;
        location = rhs.location;
        return *this;
    }
    Warehouse& operator=(Warehouse&& rhs)
    {
        SimObject::operator=(rhs);
        inventory = rhs.inventory;
        location = rhs.location;
        return *this;
    }

    //update does nothing, inventory will be updated by trucks
    virtual void update(){ }
    //operator +=, -= overloads to update inventory
    void operator+=(int add_crates){ inventory += add_crates;}
    void operator-=(int take_crates){inventory -= take_crates;}
    //imp of SimObject getLocation
    virtual const Point& getLocation() const {return location;}
    virtual ostream& broadcastState(ostream& out){return out<<"warehouse " << name <<" at position " << 
                                                  location << ", Inventory: " << inventory << endl;}
    
    //d'tor
    virtual ~Warehouse(){ }
};

#endif