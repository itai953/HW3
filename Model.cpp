#include "Model.h"

Model& Model::getInstance(){
    static Model inst;
    return inst;
}