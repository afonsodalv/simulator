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

int  Caravan::get_cargo() const {
    return current_cargo;
}

int Caravan::get_water() const {
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

int Caravan::distance_between(std::pair<int,int> a, std::pair<int,int> b, int rows, int cols) const {
    int dr = std::abs(a.first  - b.first);
    int dc = std::abs(a.second - b.second);
    dr = std::min(dr, rows - dr);
    dc = std::min(dc, cols - dc);
    return std::max(dr, dc);
}

void Caravan::set_autonomous_behavior(bool ab) {
    autonomous_behavior = ab;
}