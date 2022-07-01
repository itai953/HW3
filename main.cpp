
#include <memory>
#include "AsciiView.h"
#include "Controller.h"


int main(int argc, char** argv){
    cout.setf(ios::fixed,ios::floatfield);
    cout.precision(2);
    Controller controller;
    try
    {
        controller.run(argc,argv);
    }
    catch (std::exception &e)
    {
        
    }
    return 0;
}
