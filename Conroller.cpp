#include "Controller.h"

void Controller::run(int argc, char* argv[]){
    if(argc < 5){
        //TODO throw something
    }
    Model::getInstance().init(vector<string>(argv+1,argv+argc));
    bool go = true;
    string cmd;
    while(go){
        cin >> cmd;
        go = parseExecCmd(cmd);
    }
}
bool Controller::parseExecCmd(const string& cmd){
    if(cmd == "EXIT") return false;
    stringstream ss(cmd);
    string first;
    ss >> first;
    if(first == "default"){
        returnDefault();
    }else if(first == "size"){
        int s;
        ss >> s;
        if(s < AsciiView::MINSIZE || s > AsciiView::MAXSIZE){
            //TODO throw exception
        }
        view->setSize(s);
    }else if(first == "zoom"){
        double z;
        ss >> z;
        view->setScale(z);
    }else if(first == "pan"){
        double x,y;
        ss >> x;
        ss >> y;
        view->setOrigin(x,y);
    }else if(first == "show"){
        view->draw(cout);
    }else if(first == "status"){
        auto list = Model::getInstance().getSimObjList();
        for(auto & o: list){
            o.second->broadcastState(cout);
        }
    }else if(first == "go"){
        Model::getInstance().updateAll();
    }else if(first == "create"){
        string name,type,pos;
        ss >> name;
        ss >> type;
        ss >> pos;
        if(type == "State_trooper"){
            create(name,pos);
        }else{
            double x,y;
            stringstream pt(pos);
            pt.ignore();
            pt >> x;
            pt.ignore();
            pt >> y;
            create(name,x,y);
        }
    }else{
        execVehicleCmd(cmd);
    }
    return true;
}

void Controller::execVehicleCmd(const string& cmd){
    string name,action;
    stringstream ss(cmd);
    ss >> name;
    ss >> action;
    if(action == "course"){
        double heading,speed;
        ss >> heading >> speed;
        if(speed == 0){
            Model::getInstance().setVehicleCourse(name, heading);
        }else{
            Model::getInstance().setVehicleCourse(name,heading,speed);
        }
    }else if(action == "position"){

    }
}