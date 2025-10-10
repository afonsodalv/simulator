cmake_minimum_required(VERSION 3.29)
project(simulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(simulator main.cpp
        UI/Buffer/Buffer.cpp
        SimulationManager/SimulationManager.h
        Data/Simulation/Simulation.h
        Data/Simulation/Simulation.cpp
        Data/Simulation/Simulation.cpp
        SimulationManager/SimulationManager.cpp
        UI/Render/Render.h
        UI/Render/Render.cpp
        Data/City/City.h
        Data/City/City.cpp
        Managers/CityManager/CityManager.cpp
        Utils/HelperType.h
        Utils/HelperView.h
        Data/Caravan/Caravan.h
        Data/Caravan/Caravan.cpp
        Managers/CaravanManager/CaravanManager.h
        Managers/CaravanManager/CaravanManager.cpp
        Data/Caravan/CaravanFactory/CaravanFactory.h
        Data/Caravan/CaravanFactory/CaravanFactory.cpp)
