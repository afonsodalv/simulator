//
// Created by afons on 09/10/2025.
//

#include "MilitaryCaravan.h"
#include <sstream>

int MilitaryCaravan::initial_crew = 30;
int MilitaryCaravan::max_crew = 40;
int MilitaryCaravan::max_cargo = 5;
int MilitaryCaravan::max_water = 400;


MilitaryCaravan::MilitaryCaravan(char id, int row, int col)
: Caravan(id, row, col, initial_crew, false,max_water, max_cargo ,max_water, max_cargo, true) {}

void MilitaryCaravan::move() {

}

std::string MilitaryCaravan::get_info() const {
    std::ostringstream oss;
    oss << "Caravan " << get_id() << '\n'
        <<"Type: Military\n"
        << "Crew members: " << get_crew_members() << '\n'
        << "Autonomous behavior: " << (get_autonomous_behavior() ? "Yes" : "No") << '\n'
        << "Water: " << get_water() << '\n'
        << "Cargo: " << get_cargo();
    return oss.str();
}

