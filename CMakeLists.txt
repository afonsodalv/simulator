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
        Data/Caravan/CaravanFactory/CaravanFactory.cpp
        Data/Caravan/CommercialCaravan/CommercialCaravan.cpp
        Data/Caravan/MilitaryCaravan/MilitaryCaravan.cpp
        Data/Caravan/BuilderCaravan/BuilderCaravan.cpp
        Data/Caravan/BanditCaravan/BanditCaravan.cpp
        Utils/Wallet/Wallet.h
        Utils/GameContext/GameContext.cpp
        Utils/IEconomy.h
        Managers/ItemManager/ItemManager.h
        Managers/ItemManager/ItemManager.cpp
        Data/Item/Item.h
        Data/Item/Item.cpp
        Data/Item/TreasureChest/TreasureChest.h
        Data/Item/PandoraBox/PandoraBox.h
        Data/Item/Cage/Cage.h
        Data/Item/GoldenWhistle/GoldenWhistle.h
        Data/Item/Mine/Mine.h
        Data/Item/PandoraBox/PandoraBox.cpp
        Data/Item/Mine/Mine.cpp
        Data/Item/GoldenWhistle/GoldenWhistle.cpp
        Data/Item/Cage/Cage.cpp
        Data/Item/TreasureChest/TreasureChest.cpp
        Data/Item/ItemFactory/ItemFactory.cpp)
