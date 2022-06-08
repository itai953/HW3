#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Model.h"
#include "AsciiView.h"
#include <iterator>
class Controller{
    shared_ptr<AsciiView> view;
    void getCmd();
    bool parseExecCmd(const string& cmd);
    void go();
    void returnDefault();
    void status();
    void create(const string& name,const string& WHname);
    void create(const string& name, double x, double y);
    void execVehicleCmd(const string& cmd);
public:
    void run(int argc, char* argv[]);
    Controller():view(new AsciiView()){ }
};


#endif