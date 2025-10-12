//
// Created by afons on 09/10/2025.
//

#include "Caravan.h"

#include <sstream>

Caravan::Caravan(char id, int row, int col, int crew_members,bool autonomous_behavior, int water, int cargo, bool is_in_city) :
id(id), row(row), col(col), crew_members(crew_members), autonomous_behavior(autonomous_behavior), water(water), cargo(cargo), is_in_city(is_in_city){}


int Caravan::get_row() const {
    return row;
}
int Caravan::get_col() const {
    return col;
}
char Caravan::get_id() const {
    return id;
}

std::string Caravan::get_info() const {
    std::ostringstream oss;
    oss << "Caravan " << id << '\n'
        << "Crew members: " << crew_members << '\n'
        << "Autonomous behavior: " << (autonomous_behavior ? "Yes" : "No") << '\n'
        << "Water: " << water << '\n'
        << "Cargo: " << cargo;
    return oss.str();
}