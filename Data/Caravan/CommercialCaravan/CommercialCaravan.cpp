//
// Created by afons on 09/10/2025.
//

#include "CommercialCaravan.h"

#include <sstream>


int CommercialCaravan::initial_crew = 20;
int CommercialCaravan::max_crew = 25;
int CommercialCaravan::max_cargo = 40;
int CommercialCaravan::max_water = 200;
int CommercialCaravan::speed = 2;
int CommercialCaravan::turns_left_after_no_crew = 5;

CommercialCaravan::CommercialCaravan(char id, int row, int col)
: Caravan(id, row, col, speed, initial_crew, turns_left_after_no_crew,false, max_water, max_cargo,max_water, max_cargo, max_crew,true) {}

std::pair<int, int> CommercialCaravan::move_autonomous(const std::vector<SimulationMap>&caravans, MoveContext& mc) {

    return {-1, -1};
}

void CommercialCaravan::reset_speed(){
    set_speed(speed);
}


std::string CommercialCaravan::get_info() const {
    std::ostringstream oss;
    oss << "Caravan " << get_id() << '\n'
        <<"Type: Commercial\n"
        << "Crew members: " << get_crew_members() << '\n'
        << "Autonomous behavior: " << (get_autonomous_behavior() ? "Yes" : "No") << '\n'
        << "Water: " << get_water() << '\n'
        << "Cargo: " << get_cargo() << '\n'
        << "Speed: " << get_speed() << '\n'
        << "Visitng a City: " << (get_is_in_city() ? "Yes" : "No") << '\n';
    return oss.str();
}