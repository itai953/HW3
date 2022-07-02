#ifndef CONSOLE_H
#define CONSOLE_H
#include <iostream>
#include <algorithm>
#include "Model.h"
/*
 * class Console handles interaction with user in regards to command input
 * data members are all the possible input types the user can supply
 * vehicle: is the vehicle to which the command is applied (including create)
 * target: Warehouse in case of Trooper, truck in case of Chopper
 * startPos: Warehouse in case of Trooper
 * d1, d2, d3 are doubles, usage:
 * if the command requires 2 double arguments use d1 and d2, if only one requires use only d1, etc.
 * n is the int input type
 */

class Console{
    string vehicle,target,startPos;
    double d1,d2,d3;
    int n,vType; //vType captures the type of vehicle the command refers to will have a value from the Model class TYPE enum
public:
    //an invlaid input exception nested class
    class InvalidInputException
    {
        string msg;
    public:
        InvalidInputException(const string& e):msg(e){ }
        string getMessege() const {return msg;}
    };

    //enum for CMDs
    enum CMD{DEFAULT,SIZE,PAN,ZOOM,SHOW,GO,STATUS,CREATE,COURSE,
            POSITION,DEST,ATK,STOP,EXIT};
    CMD getCMD(); //get next command from user

    //getters
    string getVehicle() const {return vehicle;}
    string getTarget() const { return target;}
    string getStartPos() const {return startPos;}
    double getD1() const {return d1;}
    double getD2() const {return d2;}
    double getD3() const {return d3;}
    int getInt() const {return n;}
    int getVtype() const {return vType;}
private:

    //get a command that pertains to view
    void getViewCMD(CMD cm);
    //get a command that pertains to vehicle
    void getVehicleCMD(CMD cm);

    //static maps that associate the string input to the correct CMD enum
    static unordered_map<string,CMD> viewCMDs;
    static unordered_map<string,CMD> vehicleCMDs;
};


#endif