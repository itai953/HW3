
#include <memory>
#include "AsciiView.h"
#include "Controller.h"


int main(int argc, char** argv){
    cout.setf(ios::fixed,ios::floatfield);
    cout.precision(2);
    Controller controller;
    controller.run(argc,argv);
    auto objects = Model::getInstance().getSimObjList();
    auto whouses = Model::getInstance().getWarehouses();
    auto vehicles = Model::getInstance().getVehicles();
    return 0;
}
