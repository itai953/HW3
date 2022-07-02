#include "Controller.h"

void Controller::run(int argc, char* argv[]){
    if(argc < 5){
        cerr << "ERROR: not enough arguments for program";
        exit(1);
    }
    Model::getInstance().init(vector<string>(argv+1,argv+argc));
    Console::CMD go = Console::DEFAULT;
    cout << "Game starting, at any point input EXIT to quit\n";
    while(go != Console::EXIT){
        try
        {
            go = console.getCMD();
            execute(go);
        }
        catch (Console::InvalidInputException& e)
        {
            cerr << e.getMessege() << endl;
        }
        catch (Model::invalidCommandException& e)
        {
            cerr << e.getMsg() << endl;
        }
    }
}

void Controller::execute(Console::CMD cmd){
    switch(cmd){
        case Console::DEFAULT:
            view->returnDefault();
            return;
        case Console::SIZE:
            view->setSize(console.getInt());
            return;
        case Console::ZOOM:
            view->setScale(console.getD1());
            return;
        case Console::PAN:
            view->setOrigin(console.getD1(), console.getD2());
            return;
        case Console::SHOW:
            view->draw(cout);
            return;
        case Console::CREATE:
            if(console.getVtype() == Model::TROOPER){
                Model::getInstance().createVehicle(console.getVehicle(),console.getStartPos());
            }else{
                Model::getInstance().createVehicle(console.getVehicle(),console.getD1(),console.getD2());
            }
            return;
        case Console::COURSE:
            if(console.getVtype() == Model::TROOPER){
                Model::getInstance().setVehicleCourse(console.getVehicle(),console.getD1());
            }else{
                Model::getInstance().setVehicleCourse(console.getVehicle(),console.getD1(),console.getD2());
            }
            return;
        case Console::POSITION:
            if(console.getVtype() == Model::TROOPER){
                Model::getInstance().setVehiclePosition(console.getVehicle(),console.getD1(),console.getD2());
            }else{
                Model::getInstance().setVehiclePosition(console.getVehicle(),console.getD1(),console.getD2(),console.getD3());
            }
            return;
        case Console::DEST:
            Model::getInstance().setVehicleDestination(console.getVehicle(),console.getTarget());
            return;
        case::Console::ATK:
            Model::getInstance().attack(console.getVehicle(),console.getTarget());
            return;
        case::Console::STOP:
            Model::getInstance().stopVehicle(console.getVehicle());
            return;
        case Console::GO:
            Model::getInstance().updateAll();
            return;
        case Console::STATUS:
            Model::getInstance().status();
            return;
    }
}