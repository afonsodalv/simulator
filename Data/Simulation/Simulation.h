//
// Created by afons on 07/10/2025.
//

#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <utility>
#include <string>

#include "..\\..\\Managers\\CityManager\\CityManager.h"
#include "..\\..\\Utils\\HelperType.h"
class Simulation {

    int row;
    int col;
    int coins;
    int item_interval;
    int item_duration;
    int max_itens;
    int sell_price;
    int buy_price;
    int caravan_price;
    int bandits_interval;
    int bandits_duration;

    std::vector<std::pair<int, int>> mountain;
    std::vector<std::pair<int, int>> desert;
    std::vector<std::string> messages;
    // CaravanManager caravans;
    CityManager city_manager;
    // ItemManager itens;


public:
    Simulation(int row,
    int col,
    int coins,
    int item_interval,
    int item_duration,
    int max_itens,
    int sell_price,
    int buy_price,
    int caravan_price,
    int bandits_interval,
    int bandits_duration, const std::string& map);

    bool handle_command();

    bool buy_caravan(char city_id, CaravanType type);
    std::vector<SimulationMap> get_map_state() const;

    std::string get_simulation_info() const;

};



#endif //SIMULATION_H
