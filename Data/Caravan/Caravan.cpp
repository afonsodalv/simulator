//
// Created by afons on 09/10/2025.
//

#include "Caravan.h"

Caravan::Caravan(char id, int row, int col, int speed, int crew_members, int turns_left, bool autonomous_behavior, int max_water, int max_cargo, int water, int cargo,int max_crew , bool is_in_city) :
id(id), row(row), col(col),speed(speed) ,crew_members(crew_members),turns_left(turns_left) ,autonomous_behavior(autonomous_behavior),
max_water(max_water), max_cargo(max_cargo), current_water(water), current_cargo(cargo), max_crew(max_crew), is_in_city(is_in_city){}


int Caravan::get_row() const {
    return row;
}

int Caravan::get_col() const {
    return col;
}

std::pair<int, int> Caravan::get_position() const {
    return {row, col};
}


char Caravan::get_id() const {
    return id;
}

bool Caravan::get_autonomous_behavior() const {
    return autonomous_behavior;
}

int  Caravan::get_crew_members() const {
    return crew_members;
}
int Caravan::get_turns_left() const {
    return turns_left;
}

int  Caravan::get_cargo() const {
    return current_cargo;
}

int Caravan::get_current_water() const {
    return current_water;
}

int Caravan::get_speed() const {
    return speed;
}

bool Caravan::get_is_in_city() const {
    return is_in_city;
}

int Caravan::add_cargo(int qtd) {

    int space_left = max_cargo - current_cargo;

    int added = std::min(qtd, space_left);

    current_cargo += added;

    return added;
}

void Caravan::add_crew_members(int qtd) {
    if (qtd > 0) {
        int space_left = max_crew - crew_members;
        int added = std::min(qtd, space_left);
        crew_members += added;
    } else if (qtd < 0) {
        int removed = std::min(-qtd, crew_members);
        crew_members -= removed;
        autonomous_behavior = (crew_members == 0);
    }
}

void Caravan::add_speed(int v) {
    speed += v;
    if (speed < 0)
        speed = 0;
}

void Caravan::add_turns_left(int t) {
    turns_left += t;
    if (turns_left < 0)
        turns_left = 0;
}

void Caravan::decrement_water(int qtd) {
    int removed = std::min(qtd, current_water);
    current_water -= removed;
}
void Caravan::set_speed(int v) {
    if(v>0)
        speed = v;
}

int Caravan::sell_all_cargo() {
    int aux = current_cargo;
    current_cargo = 0;
    return aux;
}

void Caravan::set_position(std::pair<int, int> pos) {

    if(pos.first > 0 && pos.second > 0) {
        row = pos.first;
        col = pos.second;
    }

}

void Caravan::set_is_in_city(bool b) {

    if(b) {
        current_water = max_water;
    }
    is_in_city = b;
}

int Caravan::distance_between(std::pair<int,int> a, std::pair<int,int> b, int rows, int cols) {
    int dr = std::abs(a.first  - b.first);
    int dc = std::abs(a.second - b.second);
    dr = std::min(dr, rows - dr);
    dc = std::min(dc, cols - dc);
    return std::max(dr, dc);
}

std::pair<int, int> Caravan::get_closest_target_position(int row, int col, int max_dist, char target_id,const std::vector<SimulationMap>&targets) const{
    auto my_pos = get_position();

    std::pair pos = {-1, -1};
    int min_dist = 999;

    for(const auto& target : targets) {

        if(target.id != target_id)
            continue;

        std::pair target_pos = {target.row, target.col};

        int dist = distance_between(my_pos, target_pos, row, col);

        if(dist <= max_dist && dist < min_dist) {
            min_dist = dist;
            pos = target_pos;
        }
    }

    return pos;
}

std::pair<int, int> Caravan::get_closest_player_caravan_position(int row, int col, int max_dist,const std::vector<SimulationMap>&targets) const{
    auto my_pos = get_position();

    std::pair pos = {-1, -1};
    int min_dist = 999;

    for(const auto& target : targets) {

        if(target.id == '!')
            continue;

        if (target.row == my_pos.first && target.col == my_pos.second) continue;

        std::pair target_pos = {target.row, target.col};

        int dist = distance_between(my_pos, target_pos, row, col);

        if(dist <= max_dist && dist < min_dist) {
            min_dist = dist;
            pos = target_pos;
        }
    }

    return pos;
}

void Caravan::set_autonomous_behavior(bool ab) {
    autonomous_behavior = ab;
}

std::pair<int, int> Caravan::move_random(int max_row, int max_col) const {

    std::pair<int , int> next_pos;

    next_pos.first = row + (rand() % 3 - 1);
    next_pos.second = col + (rand() % 3 - 1);

    next_pos.first  = (next_pos.first  + max_row) % max_row;
    next_pos.second = (next_pos.second +  max_col) %  max_col;

    return next_pos;
}