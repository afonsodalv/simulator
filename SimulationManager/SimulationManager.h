//
// Created by afons on 07/10/2025.
//

#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#include "..\\Data\\Simulation\\Simulation.h"
#include "..\\UI\\Buffer\\Buffer.h"
#include "..\\UI\\Render\\Render.h"

#include <memory>
#include <string>

class SimulationManager {

    Simulation* simulation;
    Buffer* buffer;
    Render render;

public:

    SimulationManager();
    ~SimulationManager();
    void handleConfigCommand(const std::string &file);

    void doRender();
};



#endif //SIMULATIONMANAGER_H
