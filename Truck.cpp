#include "Truck.h"
#include <sstream>
#include "factory.h"
#include "Model.h"

auto MODEL = Model::getInstance;
registerInFactory<SimObject, Truck> rtruck("truck");
void Truck::init(const string& fPath){
    string line, token;
    ifstream file(fPath);
    char delim;
    if(!file){
        //todo throw something
    }
    char temp;

    //first line
    getline(file,line);
    stringstream firstLine(line);
    string originName, startTime_s;
    getline(firstLine,originName,',');
    getline(firstLine,startTime_s);
    if(firstLine>>temp){
        //todo throw something
    }
    if(!(MODEL().containsObj(Model::WAREHOUSE,originName))){
        //todo throw
    }

    //get a decimal hour out of string
    int startTime = MODEL().hourToDecimal(startTime_s);

    if (MODEL().getTime() > startTime)
    {
       MODEL().setTime(startTime); 
    }
    


    while(getline(file,line)){
        string arr_hour,dep_hour,name,amount;
        stringstream ss(line);
        getline(ss,name,',');
        getline(ss,arr_hour,',');
        getline(ss,amount,',');
        getline(ss,dep_hour);        

    }
    string whouseName;
    MODEL().containsObj(Model::WAREHOUSE, whouseName);
}
    