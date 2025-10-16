//
// Created by afons on 07/10/2025.
//

#include "Simulation.h"

#include <string>
#include <sstream>
#include <stdexcept>

#include "..\\..\\Utils\\GameContext\\GameContext.h"
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
      wallet(coins),
      item_manager(item_interval, item_duration, max_itens),
      city_manager(sell_price, buy_price, caravan_price),
      caravan_manager(bandits_interval, bandits_duration),
      turn(0)
{

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
                    case '!':
                        caravan_manager.add_caravan(CaravanType::Bandit, i, j);
                        break;
                    case '?':
                        item_manager.add_item(i, j);
                        desert.emplace_back(i, j);
                        break;
                    default:
                        desert.emplace_back(i, j);
                        break;
                }
            }
        }
    }
}

std::vector<SimulationMap> Simulation::get_map_state() const {

    vector<SimulationMap> map;

    for(const auto& [i, j] : mountain) {
        map.emplace_back(Type::Mountain, i, j);
    }
    for(const auto& [i, j] : desert) {
        map.emplace_back(Type::Desert, i, j);
    }

    for(const auto& cities_pos : city_manager.get_cities_info())
        map.emplace_back(cities_pos);

    for(const auto& caravans_pos : caravan_manager.get_caravans_position_map())
        map.emplace_back(caravans_pos);

    for(const auto& item_pos : item_manager.get_item_position_map())
        map.emplace_back(item_pos);

    return map;
}

CaravanType Simulation::char_to_caravan_type(char c) {

    switch (c) {
        case 'C': return CaravanType::Commercial;
        case 'M': return CaravanType::Military;
        case 'S': return CaravanType::Builder;
        case '!' : return CaravanType::Bandit;
        default:  throw std::invalid_argument("Unknown caravan type (use C, M or S)");
    }
}

char Simulation::string_to_char(const std::string& str) {
    if (str.size() != 1)
        throw std::invalid_argument("Expected a single-character string");
    return str[0];
}

string Simulation::get_simulation_info() const {
    std::ostringstream ss;

    ss << "=== Simulation Info ===\n";
    ss << "Turn: " << turn << '\n';
    ss << "Coins: " << wallet.get_coins() << '\n';
    ss << "Item interval: " << item_manager.get_item_interval() << '\n';
    ss << "Item duration: " << item_manager.get_item_duration() << '\n';
    ss << "Max items: " << item_manager.get_max_items() << '\n';
    ss << "Sell price: " << city_manager.get_sell_price() << '\n';
    ss << "Buy price: " << city_manager.get_buy_price() << '\n';
    ss << "Caravan price: " << city_manager.get_caravan_price() << '\n';
    ss << "Bandits interval: " << caravan_manager.get_bandits_interval() << '\n';
    ss << "Bandits duration: " << caravan_manager.get_bandits_duration() << '\n';

    for(const string& str : messages)
        ss<<str<<endl;
    ss << "========================\n";

    return ss.str();
}

Status Simulation::buy_caravan(const std::string& city, const std::string& caravan) {


    try {
        char city_id = string_to_char(city);
        char caravan_type = string_to_char(caravan);
        int coins = wallet.get_coins();
        CaravanType type = char_to_caravan_type(caravan_type);

        pair<int, int> coordinates = city_manager.get_city_coordinates(city_id);

        if(coordinates.first < 0)
            return {false, "City doesn't exist."};
        if(coins < city_manager.get_caravan_price())
            return {false,  "You don't have enough coins."};

        if(!city_manager.buy_caravan_in_city(city_id, type))
            return {false,  "No caravans of that type available in the city."};

        caravan_manager.add_caravan(type, coordinates.first, coordinates.second);
        wallet.add_coins(-city_manager.get_caravan_price());
        return  {true, "Caravan bought successfully."};
    }
    catch(const invalid_argument& e) {
        return {false, e.what()};
    }
}

std::string Simulation::get_goods_prices() const {
    std::string aux = "Buy goods price: " + std::to_string(city_manager.get_buy_price()) + '\n';
    aux += "Sell goods price: " + std::to_string(city_manager.get_sell_price()) + '\n';
    return aux;
}

std::string Simulation::get_city_info(const std::string& city) const{

    try {
        char city_id = string_to_char(city);

        std::ostringstream os;
        os << city_manager.get_city_info(city_id);

        const auto pos = city_manager.get_city_coordinates(city_id);
        const auto caravan_ids = caravan_manager.get_caravans_id_at_city(pos);

        if (caravan_ids.empty())
            os << "No caravans are currently inside this city.\n";
        else {
            for (const char& id : caravan_ids)
                os << "Caravan " << id << " is inside the city.\n";
        }
        return os.str();

    }
    catch(const invalid_argument& e) {
        return e.what();
    }
}

std::string Simulation::get_caravan_info(const std::string& caravan) const{

    try {
        char caravan_id = string_to_char(caravan);

        return caravan_manager.get_caravan_info(caravan_id);
    }
    catch(const invalid_argument& e) {
        return e.what();
    }
}

Status Simulation::buy_goods(const std::string& caravan, int qtd) {

    try {

        char caravan_id = string_to_char(caravan);

        if(caravan_id == '!')
            return {false, "Bandits didn't trust you... they  didn't accept your goods."};

        int expense = city_manager.get_buy_price() * caravan_manager.buy_cargo(caravan_id, qtd);
        int coins = wallet.get_coins();
        if(expense < 0) {
            return {false, "Caravan doesn't exit."};
        }
        if(coins < expense)
            return {false, "You don't have enough coins."};

        wallet.add_coins(-expense);
        return {true, "Goods bought successfully."};
    }
    catch (const invalid_argument& e) {
        return {false, e.what()};
    }

}

Status Simulation::sell_all_goods(const std::string& caravan) {


    try {
        char id = string_to_char(caravan);

        if(id == '!')
            return {false, "Bandits didn't took your orders!"};

        int qtd = caravan_manager.sell_cargo(id);

        if(qtd == -1)
            return {false,"Caravan doesn't exist"};

        wallet.add_coins(qtd * city_manager.get_sell_price());
        return {true, "Cargo sold successfully"};
    }
    catch(const invalid_argument& e) {
        return {false, e.what()};
    }

}

std::pair<int, int> Simulation::direction_to_pair_int(const std::string& direction) {

    if(direction == "D") {
        return {0, 1};
    }
    if(direction == "E") {
        return {0, -1};
    }
     if(direction == "C") {
        return {-1, 0};
    }
    if(direction == "B") {
        return {1, 0};
    }
    if(direction == "CE") {
        return {-1, -1};
    }
    if(direction == "CD") {
        return {-1, 1};
    }
    if(direction == "BE") {
        return {1, -1};
    }
    if(direction == "BD") {
        return {1, 1};
    }

    throw std::invalid_argument("Invalid direction: " + direction);
}

Status Simulation::move_caravan(const std::string& caravan, const std::string& direction) {


    try {
        char caravan_id = string_to_char(caravan);

        if(caravan_id == '!')
            return {false, "Bandits refused to take orders from you!"};

        auto current_pos = caravan_manager.get_caravan_position(caravan_id);

        if(current_pos.first < 0) {
            return {false, "Caravan doesn't exist."};
        }

        auto next_pos = direction_to_pair_int(direction);
        MoveContext mc {desert, city_manager.get_cities_position(), item_manager.get_item_position_map(), row, col};
        auto result = caravan_manager.move_caravan(caravan_id, next_pos, mc);

        if(result.ok)
            check_for_items(caravan_id, next_pos);
        return result;

    }
    catch (const invalid_argument& e) {
        return {false, e.what()};
    }

}

void Simulation::check_for_items(char caravan_id, pair<int, int> pos) {
    auto items_id = item_manager.check_nearby_items(pos, row, col);

    GameContext ctx{caravan_manager, wallet, pos};

    for(const auto& id : items_id) {

        item_manager.apply_item_effect(id, caravan_id,ctx);
        messages.emplace_back("Caravan "s + caravan_id + " found an item!\n" + item_manager.get_item_description(id));
        item_manager.remove_item_by_id(id);

        if(!caravan_manager.exist(caravan_id)) {
            desert.push_back(pos);
        }
    }
}

void Simulation::next_turn() {

    ++turn;

    MoveContext mc {desert, city_manager.get_cities_position(), item_manager.get_item_position_map(), row, col};

    auto caravans_ids = caravan_manager.move_autonomous(mc);

    for(const auto& id : caravans_ids) {
        check_for_items(id, caravan_manager.get_caravan_position(id));
    }


    for(auto result : caravan_manager.combat_phase(row, col)) {
        messages.push_back(result);
    }

    for(auto result : caravan_manager.handle_caravans_life_time()) {
        messages.push_back(result);
    }
    caravan_manager.handle_speed_and_water_consumption();
    caravan_manager.handle_bandits_spawn(turn, desert);
    item_manager.handle_items_life_time();
    item_manager.handle_items_spawn(turn, desert);

}

Status Simulation::put_caravan_on_auto(const std::string& caravan) {

    try {
        char id = string_to_char(caravan);

        if(id == '!')
            return {false, "Bandits didn't took your orders!"};

        return caravan_manager.put_caravan_on_auto(id);
    }
    catch(const invalid_argument& e) {
        return {false, e.what()};
    }
}
