
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
    catch (std::exception &e) //for unexpected exceptions
    {
        cerr << e.what() << endl;
    }
    catch(...) //for unexpected exceptions not derived from std::exception
    {
        cerr << "an unknown error occured, terminating program\n";
        exit(1);
    }
    return 0;
}
