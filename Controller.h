#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Model.h"
#include "AsciiView.h"
#include <iterator>
#include "Console.h"
class Controller{
    shared_ptr<AsciiView> view;
    Console console;
    void execute(Console::CMD cm);
public:
    void run(int argc, char* argv[]);
    Controller():view(new AsciiView()){ }
};


#endif