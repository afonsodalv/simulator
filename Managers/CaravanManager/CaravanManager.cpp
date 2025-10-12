//
// Created by afons on 09/10/2025.
//

#include "CaravanManager.h"

#include "..\\..\\Data\\Caravan\\CaravanFactory\\CaravanFactory.h"

CaravanManager::CaravanManager(int bandits_interval,int bandits_duration) :bandits_interval(bandits_interval), bandits_duration(bandits_duration){}


int CaravanManager::get_bandits_interval() const {
    return bandits_interval;
}
int CaravanManager::get_bandits_duration() const {
    return bandits_duration;
}
void CaravanManager::add_caravan(CaravanType type, int row, int col) {

    caravans.push_back(CaravanFactory::createCaravan(type, row, col));
}


std::vector<SimulationMap> CaravanManager::get_caravans_position() const {
    std::vector<SimulationMap> caravans_info;

    for(const auto& caravan : caravans) {
        caravans_info.emplace_back(Type::Caravan, caravan->get_row(), caravan->get_col(), caravan->get_id());
    }
    return caravans_info;
}

std::string CaravanManager::get_caravan_info(char id) const {
    for(const auto& caravan : caravans) {
        if(caravan->get_id() == id)
            return caravan->get_info();
    }
    return "Caravan doesn't exit";
}