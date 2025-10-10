#include <iostream>
#include "SimulationManager\\SimulationManager.h"

int main() {

    SimulationManager sm;

    sm.handleConfigCommand("..\\test.txt");

    sm.doRender();

    return 0;
}
