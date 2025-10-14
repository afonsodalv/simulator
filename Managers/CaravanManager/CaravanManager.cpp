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

    caravans.push_back(CaravanFactory::createCaravan(type, row, col));
}

void CaravanManager::remove_caravan(char id) {
    for (auto it = caravans.begin(); it != caravans.end(); ++it) {
        if ((*it)->get_id() == id) {
            caravans.erase(it);
            break;
        }
    }
}

std::vector<SimulationMap> CaravanManager::get_caravans_position() const {
    std::vector<SimulationMap> caravans_info;

    for(const auto& caravan : caravans) {
        if(!caravan->get_is_in_city())
            caravans_info.emplace_back(Type::Caravan, caravan->get_row(), caravan->get_col(), caravan->get_id());
    }
    return caravans_info;
}

std::vector<char> CaravanManager::get_caravans_id_at(std::pair<int, int> pos) const {

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

void CaravanManager::add_velocity(char id, int p) {

    if(auto caravan = find(id))
        caravan->add_velocity(p);
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

    if(auto caravan = find(id)) return caravan->set_position(pos);

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