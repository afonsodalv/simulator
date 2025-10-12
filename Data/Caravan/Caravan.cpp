//
// Created by afons on 09/10/2025.
//

#include "Caravan.h"

Caravan::Caravan(char id, int row, int col, int crew_members,bool autonomous_behavior, int max_water, int max_cargo, int water, int cargo, bool is_in_city) :
id(id), row(row), col(col), crew_members(crew_members), autonomous_behavior(autonomous_behavior),
max_water(max_water), max_cargo(max_cargo), current_water(water), current_cargo(cargo), is_in_city(is_in_city){}


int Caravan::get_row() const {
    return row;
}
int Caravan::get_col() const {
    return col;
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

int Caravan::add_cargo(int qtd) {

    int space_left = max_cargo - current_cargo;

    int added = std::min(qtd, space_left);

    current_cargo += added;

    return added;
}

int Caravan::sell_all_cargo() {
    int aux = current_cargo;
    current_cargo = 0;
    return aux;
}