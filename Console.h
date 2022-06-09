#ifndef CONSOLE_H
#define CONSOLE_H
#include <iostream>
#include <algorithm>
#include "Model.h"
class Console{
    string vehicle,target,startPos;
    double d1,d2,d3;
    int n,vType;
public:
    enum CMD{DEFAULT,SIZE,PAN,ZOOM,SHOW,GO,STATUS,CREATE,COURSE,
    POSITION,DEST,ATK,STOP,EXIT};
    CMD getCMD();
    string getVehicle() const {return vehicle;}
    string getTarget() const { return target;}
    double getD1() const {return d1;}
    double getD2() const {return d2;}
    double getD3() const {return d3;}
    int getInt() const {return n;}
    int getVtype() const {return vType;}
private:
    void getViewCMD(CMD cm);
    void getVehicleCMD(CMD cm);
    static unordered_map<string,CMD> viewCMDs;
    static unordered_map<string,CMD> vehicleCMDs;
};


#endif