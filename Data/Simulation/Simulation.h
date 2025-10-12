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
#include "..\\..\\Utils\\Status.h"
#include "..\\..\\Managers\\CaravanManager\\CaravanManager.h"

class Simulation {

    int row;
    int col;
    int coins;
    int item_interval;
    int item_duration;
    int max_itens;
    int turn;

    std::vector<std::pair<int, int>> mountain;
    std::vector<std::pair<int, int>> desert;
    std::vector<std::string> messages;
    CaravanManager caravan_manager;
    CityManager city_manager;
    // ItemManager itens;

    static CaravanType char_to_caravan_type(char c);
    static char string_to_char(const std::string& str);

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

    void next_turn();

    std::string get_goods_prices() const;
    std::vector<SimulationMap> get_map_state() const;
    std::string get_simulation_info() const;
    std::string get_city_info(const std::string& city);
    std::string get_caravan_info(const std::string& caravan);



    Status buy_caravan(const std::string& city, const std::string& caravan);

};



#endif //SIMULATION_H
