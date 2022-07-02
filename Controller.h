#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Model.h"
#include "AsciiView.h"
#include <iterator>
#include "Console.h"

/* 
 * class Controller interacts with user, Model and View, getting commands from
 * user and applying to Model or view as necessary
 */
class Controller{
    //the game view
    shared_ptr<AsciiView> view;
    Console console; //a console to interact with user
    void execute(Console::CMD cm); //execute the command if input was valid
public:
    void run(int argc, char* argv[]); //initalize program
    Controller():view(new AsciiView()){ } //c'tor

    //Controller should not be copied, should interact with a single View
    Controller(const Controller&) = delete;
    Controller(Controller&&) = delete;
    Controller& operator=(const Controller&) = delete;
    Controller& operator=(Controller&&) = delete;


    ~Controller() = default;
};


#endif