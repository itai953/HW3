#include "Console.h"

unordered_map<string,Console::CMD> Console::viewCMDs{
                                                {"size",SIZE},
                                                {"pan",PAN},
                                                {"show",SHOW},
                                                {"zoom",ZOOM},
                                                {"default",DEFAULT}
                                            };
unordered_map<string,Console::CMD> Console::vehicleCMDs{
                                                    {"position",POSITION},
                                                    {"stop",STOP},
                                                    {"course",COURSE},
                                                    {"attack",ATK},
                                                    {"destination",DEST}
                                                };
                                    
Console::CMD Console::getCMD(){
    //this function will get the command from the user
    //and return the command enum
    string token;
    CMD cm;
    cout << setprecision(0) <<"Time " << Model::getInstance().getTime() << ": Enter command: ";
    cout << setprecision(2);
    cin >> token;
    if(token == "EXIT") return EXIT;
    if(viewCMDs.find(token) != viewCMDs.end()){
        cm = viewCMDs[token];
        getViewCMD(cm);
        return cm;
    }
    else if(token == "go") return GO;
    else if(token == "status") return STATUS;
    else if(token == "create"){
        cm = CREATE;
        string name,type,pos;
        cin >> name >> type >> pos;
        if(name.size() > 12){
            //TODO throw something
        }
        vehicle = name;
        if(type == "State_trooper"){
            vType = Model::TROOPER;
            startPos = pos;
            return cm;
        }else if(type == "Chopper"){
            vType = Model::CHOPPER;
            stringstream ss(pos);
            ss.ignore();
            ss >> d1;
            ss.ignore();
            ss >> d2;
            return cm;
        }else{
            //TODO throw something
        }
    }
    Model::TYPE type = Model::getInstance().getObjectType(token);
    if(type == Model::WAREHOUSE || type == Model::NONE){
        //TODO throw something
    }
    vehicle = token;
    vType = type;
    cin >> token;
    if(vehicleCMDs.find(token) == vehicleCMDs.end()){
        //TODO throw somwthing
    }
    cm = vehicleCMDs[token];
    getVehicleCMD(cm);
    return cm;
}
void Console::getViewCMD(Console::CMD cm){
    switch(cm){
        case PAN:
            cin >> d1;
            if(cin.bad()){
                //TODO throw something
            }
            cin >> d2;
            if(cin.bad()){
                //TODO throw something
            }
            return;
        case ZOOM:
            cin >> d1;
            if(cin.bad()){
                //TODO throw something
            }
            return;
        case SIZE:
            cin >> n;
            if(cin.bad()){
                //TODO throw something
            }
            return;
    }
}
void Console::getVehicleCMD(Console::CMD cm){
    switch(cm){
        case POSITION:
            cin >> d1;  //TODO check cin.bad
            cin >> d2;
            if(vType == Model::CHOPPER) cin >> d3;
            return;
        case COURSE:
            cin >> d1;
            if(vType == Model::CHOPPER) cin >> d2;
            return;
        case DEST:
            if(vType != Model::TROOPER){
                //TODO throw something
            }
            cin >> target;
            return;
        case ATK:
            cin >> target;
            return;
    }
}