//
// Created by afons on 07/10/2025.
//

#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#include "..\\Data\\Simulation\\Simulation.h"
#include "..\\UI\\Render\\Render.h"
#include "..\\Utils\\Status.h"
#include <string>


class SimulationManager {

    Simulation* simulation;
    Render* render;
    bool simulation_running;

    static std::vector<std::string> handle_user_input();
    Status handleConfigCommand(const std::string &file);
    void handle_simulation_commands(const std::vector<std::string> &command);
    static bool string_to_positive_int(const std::string& s, int& out);

public:

    SimulationManager();
    ~SimulationManager();

    void start();

    void doDebug();
    void doRender() const;
};



#endif //SIMULATIONMANAGER_H
