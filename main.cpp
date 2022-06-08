#include "Trooper.h"
#include "Chopper.h"
#include "Truck.h"
#include <memory>
#include "factory.h"
#include "Model.h"
#include "AsciiView.h"


int main(int argc, char** argv){
    Model::getInstance().init(vector<string>(argv+1,argv+argc));
    auto objects = Model::getInstance().getSimObjList();
    auto whouses = Model::getInstance().getWarehouses();
    auto vehicles = Model::getInstance().getVehicles();
    return 0;
}