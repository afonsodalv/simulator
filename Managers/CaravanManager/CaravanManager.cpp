//
// Created by afons on 09/10/2025.
//

#include "CaravanManager.h"

#include "..\\..\\Data\\Caravan\\CaravanFactory\\CaravanFactory.h"

CaravanManager::CaravanManager(int bandits_interval,int bandits_duration) :bandits_interval(bandits_interval), bandits_duration(bandits_duration){}

Caravan* CaravanManager::find(char id) const {

    for (const auto & caravan : caravans) {
        if (caravan->get_id() == id) {
            return caravan.get();
        }
    }

    return nullptr;
}

int CaravanManager::get_bandits_interval() const {
    return bandits_interval;
}

int CaravanManager::get_bandits_duration() const {
    return bandits_duration;
}

void CaravanManager::add_caravan(CaravanType type, int row, int col) {

    caravans.push_back(CaravanFactory::createCaravan(type, row, col, bandits_duration));
}

void CaravanManager::remove_caravan(char id) {
    for (auto it = caravans.begin(); it != caravans.end(); ++it) {
        if ((*it)->get_id() == id) {
            caravans.erase(it);
            break;
        }
    }
}

std::vector<SimulationMap> CaravanManager::get_caravans_position_map() const {
    std::vector<SimulationMap> caravans_info;

    for(const auto& caravan : caravans) {
        if(!caravan->get_is_in_city())
            caravans_info.emplace_back(Type::Caravan, caravan->get_row(), caravan->get_col(), caravan->get_id());
    }
    return caravans_info;
}

std::vector<char> CaravanManager::get_caravans_id_at_city(std::pair<int, int> pos) const {

    std::vector<char> caravans_id;
    for(const auto& caravan : caravans) {
        if(caravan->get_is_in_city() && caravan->get_row() == pos.first && caravan->get_col() == pos.second)
            caravans_id.push_back(caravan->get_id());
    }

    return caravans_id;
}

std::string CaravanManager::get_caravan_info(char id) const {

    if(auto caravan = find(id)) return caravan->get_info();
    return "Caravan doesn't exit";
}

std::vector<char> CaravanManager::get_autonomous_caravans_id() const {
    std::vector<char> caravans_id;
    for(const auto& caravan : caravans) {
        if(caravan->get_autonomous_behavior())
            caravans_id.push_back(caravan->get_id());
    }

    return caravans_id;
}

int CaravanManager::buy_cargo(char id, int qtd) {

    if(auto caravan = find(id)) return caravan->add_cargo( qtd);
    return -1;
}

int CaravanManager::sell_cargo(char id) {

    if(auto caravan = find(id)) return caravan->sell_all_cargo();
    return -1;
}

std::pair<int, int> CaravanManager::get_caravan_position(char id) const {

    if(auto caravan = find(id)) return {caravan->get_row(), caravan->get_col()};
    return {-1, -1};
}

void CaravanManager::add_speed(char id, int p) {

    if(auto caravan = find(id))
        caravan->add_speed(p);
}

void CaravanManager::add_crew_members(char id, int qtd) {

    if(auto caravan = find(id))
        caravan->add_crew_members(qtd);
}

void CaravanManager::lose_crew_percentage(char id, double p) {

    if(auto caravan = find(id)) {

        int qtd = static_cast<int>(caravan->get_crew_members() * p);
        caravan->add_crew_members(-qtd);
    }
}

void CaravanManager::set_caravan_position(char id, std::pair<int, int> pos) {

    if(auto caravan = find(id))
        caravan->set_position(pos);

}

void CaravanManager::enter_city(char id) {
    if(auto caravan = find(id)) {
        caravan->set_is_in_city(true);
    }
}

void CaravanManager::leave_city(char id) {
    if(auto caravan = find(id)) {
        caravan->set_is_in_city(false);
    }
}

bool CaravanManager::exist(char id) const {
    if(find(id) != nullptr) return true;

    return false;
}

std::vector<char> CaravanManager::move_autonomous(MoveContext& mc) {

    std::vector<char> caravans_ids;

    auto caravans_pos = get_caravans_position_map();

    for (auto it = caravans.begin(); it != caravans.end(); ++it) {
        if ((*it)->get_autonomous_behavior()) {
            auto next_pos = (*it)->move_autonomous(caravans_pos, mc);

            if(next_pos.first == -1)
                continue;

            update_map_positions(it->get(), next_pos,mc);

            caravans_ids.push_back((*it)->get_id());
        }
    }

    return caravans_ids;
}

Status CaravanManager::move_caravan(char id,std::pair<int, int> direction, MoveContext& mc) {

    auto caravan = find(id);

    if(!caravan)
        return {false, "Caravan doesn't exist."};

    if(caravan->get_autonomous_behavior())
        return {false, "Caravan is on autonomous behavior."};

    if(caravan->get_speed() == 0)
        return {false, "Caravan can't move. The camels are tired."};

    auto current_pos = caravan->get_position();

    auto next_pos = direction;

    next_pos.first += current_pos.first;
    next_pos.second += current_pos.second;

    next_pos.first  = (next_pos.first  + mc.row) % mc.row;
    next_pos.second = (next_pos.second + mc.col) % mc.col;

    auto it_desert = std::ranges::find(mc.desert, next_pos);

    if(it_desert == mc.desert.end()) {
        return {false, "You can't move there."};
    }

    update_map_positions(caravan, next_pos,mc);
    caravan->set_last_direction(direction);
    return {true, "Caravan moved successfully."};
}

void CaravanManager::update_map_positions(Caravan* caravan, const std::pair<int,int>& next_pos,MoveContext& mc)
{
    auto current_pos = caravan->get_position();

    if (next_pos == current_pos) return;

    auto it_city = std::ranges::find(mc.cities_pos, next_pos);

    if (it_city != mc.cities_pos.end()) {
        mc.desert.push_back(current_pos);
        caravan->set_position(next_pos);
        caravan->add_speed(-1);
        caravan->set_is_in_city(true);
        return;
    }

    it_city = std::ranges::find(mc.cities_pos, current_pos);
    if (it_city != mc.cities_pos.end())
        caravan->set_is_in_city(false);

    auto it_desert = std::ranges::find(mc.desert, next_pos);
    if (it_desert != mc.desert.end())
        mc.desert.erase(it_desert);

    mc.desert.push_back(current_pos);
    caravan->set_position(next_pos);
    caravan->add_speed(-1);

}

Status CaravanManager::put_caravan_on_auto(char id) {
    auto caravan = find(id);

    if(!caravan)
        return {false, "Caravan doesn't exist."};

    if(caravan->get_autonomous_behavior())
        return {false, "Caravan is already in autonomous behavior."};

    caravan->set_autonomous_behavior(true);
    return {true, "Caravan is on autonomous behavior."};
}