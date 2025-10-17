//
// Created by afons on 09/10/2025.
//

#include "CaravanManager.h"

#include <sstream>

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

void CaravanManager::remove_caravan(const std::pair<int, int> pos) {
    for (auto it = caravans.begin(); it != caravans.end(); ++it) {
        if ((*it)->get_position() == pos) {
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

            if((*it)->get_speed() == 0)
                continue;

            auto next_pos = (*it)->move_autonomous(caravans_pos, mc);

            if(next_pos.first == -1 || next_pos == (*it)->get_position())
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

std::vector<Caravan*> CaravanManager::get_bandits_caravans() const {
    std::vector<Caravan*> barbarians;
    for (auto& c : caravans) {
        if (c->get_id() == '!')
            barbarians.push_back(c.get());
    }
    return barbarians;
}

std::vector<std::string> CaravanManager::combat_phase(int row, int col) {

    std::vector<std::string> results;
    auto bandits = get_bandits_caravans();

    for (auto it = caravans.begin(); it != caravans.end(); ++it) {

        if((*it)->get_id() == '!' || (*it)->get_is_in_city())
           continue;

        auto caravan_pos = (*it)->get_position();

        for (int row_chek = -1; row_chek <= 1; ++row_chek) {
            for (int col_check = -1; col_check <= 1; ++col_check) {
                if (row_chek == 0 && col_check == 0) continue;

                int pos_row = (caravan_pos.first  + row_chek + row) % row;
                int pos_col = (caravan_pos.second + col_check + col) % col;

                for (const auto& enemy : bandits) {
                    if (enemy->get_position() == std::pair(pos_row, pos_col)) {

                        int bandit_crew = enemy->get_crew_members();
                        int player_crew = (*it)->get_crew_members();


                        if (bandit_crew == 0 || player_crew == 0)
                            continue;

                        int rand_bandit = rand() % bandit_crew;
                        int rand_player = rand() % player_crew;

                        Caravan* winner = nullptr;
                        Caravan* loser  = nullptr;

                        if (rand_bandit > rand_player) {
                            winner = enemy;
                            loser  = it->get();
                        } else {
                            winner = it->get();
                            loser  = enemy;
                        }

                        int winner_crew = winner->get_crew_members();
                        int loss_winner = static_cast<int>(winner_crew * 0.2);
                        int loss_loser  = loss_winner * 2;

                        winner->add_crew_members(-loss_winner);
                        loser->add_crew_members(-loss_loser);

                        std::ostringstream msg;
                        msg << winner->get_id() << " won the match vs "
                            << loser->get_id() << " dealing "
                            << loss_loser << " damage to the opponent, but lost "
                            << loss_winner << " crew members.";

                        if(enemy->get_crew_members() == 0)
                            enemy->set_turns_left(0);
                        if((*it)->get_crew_members() == 0)
                            (*it)->set_turns_left(0);

                        results.emplace_back(msg.str());
                    }
                }
            }
        }
    }

    return results;
}

void CaravanManager::handle_speed_and_water_consumption() {
    for (auto it = caravans.begin(); it != caravans.end(); ++it) {

        if(!(*it)->get_is_in_city())
            (*it)->consume_water();

        (*it)->reset_speed();
    }
}

void CaravanManager::handle_bandits_spawn(int turns, std::vector<std::pair<int,int>>& desert) {

    if(turns % bandits_interval != 0) return;
    if (desert.empty()) return;

    int idx = rand() % desert.size();
    add_caravan(CaravanType::Bandit, desert[idx].first, desert[idx].second);
    desert.erase(desert.begin() + idx);
}

std::vector<std::string> CaravanManager::handle_caravans_life_time(std::vector<std::pair<int,int>>& desert) {

    std::vector<std::string> msg;

    for (auto it = caravans.begin(); it != caravans.end();) {
        if((*it)->get_turns_left() == 0) {
            msg.emplace_back( "Caravan " + std::string(1, (*it)->get_id()) + " was destroyed.");
            desert.emplace_back((*it)->get_position());
            it = caravans.erase(it);
        }
        else {
            ++it;
        }
    }

    return msg;
}