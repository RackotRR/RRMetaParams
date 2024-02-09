#include "ParamClass.h"
#include <iostream>
#include <fstream>

int main() {
    auto constraints = Constraints::FromFile("Constraints.json");
    constraints.GenerateModuleFile("Constraints.h");

    auto params = ParamClass::FromFile("ModelParams.json");
    params.GenerateModuleFile("ModelParams.h");
    return 0;
}