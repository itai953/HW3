#include "Console.h"
#include "AsciiView.h"

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
            throw InvalidInputException("ERROR: vehiche name is too long");
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
            throw InvalidInputException("ERROR: create must have vehicle type Chopper or State_trooper");
        }
    }
    Model::TYPE type = Model::getInstance().getObjectType(token);
    if(type != Model::TROOPER && type != Model::CHOPPER){
       throw InvalidInputException("ERROR: expected name of vehicle of type State_trooper or chopper");
    }
    vehicle = token;
    vType = type;
    cin >> token;
    if(vehicleCMDs.find(token) == vehicleCMDs.end()){
       throw InvalidInputException("ERROR: unknown command");
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
                throw InvalidInputException("ERROR: expected double");
            }
            cin >> d2;
            if(cin.bad()){
                throw InvalidInputException("ERROR: expected double");
            }
            return;
        case ZOOM:
            cin >> d1;
            if(cin.bad()){
                throw InvalidInputException("ERROR: expected double");
            }
            return;
        case SIZE:
            cin >> n;
            if(cin.bad()){
               throw InvalidInputException("ERROR: expected int");
            }
            if(n < AsciiView::MINSIZE || n > AsciiView::MAXSIZE)
            {
                throw InvalidInputException("ERROR: view size must be int in range [6,30]");
            }
            return;
    }
}
void Console::getVehicleCMD(Console::CMD cm){
    switch(cm){
        case POSITION:
            cin >> d1;
            if(cin.bad()){
                throw InvalidInputException("ERROR: expected double");
            }
            cin >> d2;
            if(cin.bad()){
                throw InvalidInputException("ERROR: expected double");
            }
            
            if(vType == Model::CHOPPER){
                if(cin.peek() == '\n')
                    throw InvalidInputException("ERROR: expected another double");
                cin >> d3;
                if(cin.bad())
                {
                    throw InvalidInputException("ERROR: expected double");
                }
            }
            return;
        case COURSE:
            cin >> d1;
            if(vType == Model::CHOPPER)
            {
                if(cin.peek() == '\n')
                    throw InvalidInputException("ERROR: expected another double");
                cin >> d2;
                if(cin.bad())
                {
                    throw InvalidInputException("ERROR: expected double");
                };
            }
            return;
        case DEST:
            if(vType != Model::TROOPER){
                throw InvalidInputException("ERROR: you can set destanaiton only to an object of State_Trooper type ");
            }
            cin >> target;
            return;
        case ATK:
            cin >> target;
            return;
    }
}