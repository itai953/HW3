#include "Trooper.h"
#include "Chopper.h"
#include "Truck.h"
#include <memory>
#include "factory.h"
#include "Model.h"
#include "AsciiView.h"


int main(int argc, char** argv){
    // if(argc < 5){
    //     cerr << "ERROR usage: <program name> -w <warehouse_file> -t <truck_file1> [truckfile2,truckfile3,...]\n";
    //     exit(1);
    // }
    auto m = Model::getInstance();
    Model::getInstance().readDepotFile("depot.dat");
    auto objects = Model::getInstance().getSimObjList();
    auto whouses = Model::getInstance().getWarehouses();
    return 0;
}