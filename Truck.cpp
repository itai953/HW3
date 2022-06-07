#include "Truck.h"
#include "Model.h"
#include <sstream>
#include "factory.h"

registerInFactory<SimObject, Truck> rtruck("truck");
void Truck::init(const string& fPath){
    string line, token;
    ifstream file(fPath);
    char delim;
    if(!file){
        //todo throw something
    }
     while(getline(file,line)){
        string arr_hour,dep_hour,name,amount;
        stringstream ss(line);
        getline(ss,name,',');
        getline(ss,arr_hour,',');
        getline(ss,dep_hour);



    while(getline(file,line)){
        string arr_hour,dep_hour,name,amount;
        stringstream ss(line);
        getline(ss,name,',');
        getline(ss,arr_hour,',');
        getline(ss,amount,',');
        getline(ss,dep_hour);

        

    }
     }
    
    string whouseName;
    Model::getInstance().containsObj(Model::WAREHOUSE, whouseName);
}