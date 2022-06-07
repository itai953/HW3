#include "Trooper.h"
#include "Chopper.h"
#include "Truck.h"
#include <memory>
#include "factory.h"


int main(){
    shared_ptr<SimObject> o1 = genericFactory<SimObject>::instance().create("truck","Godzilla");
    return 0;
}