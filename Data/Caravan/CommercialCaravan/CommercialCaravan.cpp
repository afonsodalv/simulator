//
// Created by afons on 09/10/2025.
//

#include "CommercialCaravan.h"

#include <sstream>


int CommercialCaravan::initial_crew = 20;
int CommercialCaravan::max_crew = 25;
int CommercialCaravan::max_cargo = 40;
int CommercialCaravan::max_water = 200;
int CommercialCaravan::velocity = 2;

CommercialCaravan::CommercialCaravan(char id, int row, int col)
: Caravan(id, row, col, velocity, initial_crew, false, max_water, max_cargo,max_water, max_cargo, max_crew,true) {}

void CommercialCaravan::move() {

}

void CommercialCaravan::reset_velocity(){
    set_velocity(velocity);
}


std::string CommercialCaravan::get_info() const {
    std::ostringstream oss;
    oss << "Caravan " << get_id() << '\n'
        <<"Type: Commercial\n"
        << "Crew members: " << get_crew_members() << '\n'
        << "Autonomous behavior: " << (get_autonomous_behavior() ? "Yes" : "No") << '\n'
        << "Water: " << get_water() << '\n'
        << "Cargo: " << get_cargo();
    return oss.str();
}