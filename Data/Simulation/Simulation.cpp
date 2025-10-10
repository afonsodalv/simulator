//
// Created by afons on 07/10/2025.
//

#include "Simulation.h"

#include <string>
#include <sstream>

using namespace std;

Simulation::Simulation(int row,
    int col,
    int coins,
    int item_interval,
    int item_duration,
    int max_itens,
    int sell_price,
    int buy_price,
    int caravan_price,
    int bandits_interval,
    int bandits_duration, const std::string& map):

      row(row),
      col(col),
      coins(coins),
      item_interval(item_interval),
      item_duration(item_duration),
      max_itens(max_itens),
      sell_price(sell_price),
      buy_price(buy_price),
      caravan_price(caravan_price),
      bandits_interval(bandits_interval),
      bandits_duration(bandits_duration) {
    city_manager = CityManager(sell_price, buy_price, caravan_price);

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            const char c = map[i * col + j];

            if (c >= 'a' && c <= 'z') {
                city_manager.create_city(c, i, j);
            } else {
                switch (c) {
                    case '.':
                        desert.emplace_back(i, j);
                    break;
                    case '+':
                        mountain.emplace_back(i, j);
                    break;
                    default:
                        // maybe handle invalid characters here
                            break;
                }
            }
        }
    }
}

bool Simulation::handle_command(){
    return true;
}

std::vector<SimulationMap> Simulation::get_map_state() const {

    vector<SimulationMap> map;
    for(const auto& [i, j] : mountain) {
        map.emplace_back(Type::Mountain, i, j);
    }
    for(const auto& [i, j] : desert) {
        map.emplace_back(Type::Desert, i, j);
    }

    for(const auto& cities_info : city_manager.get_cities_info())
        map.emplace_back(cities_info);

    return map;
}



bool Simulation::buy_caravan(char city_id, CaravanType type) {

    if(coins < city_manager.get_caravan_price())
        return false;

    if(!city_manager.check_caravan_in_city(city_id, type))
        return false;

}

string Simulation::get_simulation_info() const {
    std::ostringstream ss;

    ss << "=== Simulation Info ===\n";
    ss << "Map size: " << row << " x " << col << '\n';
    ss << "Coins: " << coins << '\n';
    ss << "Item interval: " << item_interval << '\n';
    ss << "Item duration: " << item_duration << '\n';
    ss << "Max items: " << max_itens << '\n';
    ss << "Sell price: " << sell_price << '\n';
    ss << "Buy price: " << buy_price << '\n';
    ss << "Caravan price: " << caravan_price << '\n';
    ss << "Bandits interval: " << bandits_interval << '\n';
    ss << "Bandits duration: " << bandits_duration << '\n';

    for(const string& str : messages)
        ss<<str<<endl;
    ss << "========================\n";

    return ss.str();
}
