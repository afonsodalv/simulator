//
// Created by afons on 09/10/2025.
//

#include "BuilderCaravan.h"

#include <sstream>

int BuilderCaravan::initial_crew = 15;
int BuilderCaravan::max_crew = 20;
int BuilderCaravan::max_cargo = 5;
int BuilderCaravan::max_water = 200;
int BuilderCaravan::speed = 1;

BuilderCaravan::BuilderCaravan(char id, int row, int col)
: Caravan(id, row, col, speed,initial_crew, false, max_water, max_cargo ,max_water, max_cargo, max_crew,true) {}

void BuilderCaravan::move() {

}

void BuilderCaravan::reset_velocity(){
    set_velocity(speed);
}

std::string BuilderCaravan::get_info() const {
    std::ostringstream oss;
    oss << "Caravan " << get_id() << '\n'
        <<"Type: Builder Caravan\n"
        << "Crew members: " << get_crew_members() << '\n'
        << "Autonomous behavior: " << (get_autonomous_behavior() ? "Yes" : "No") << '\n'
        << "Water: " << get_water() << '\n'
        << "Cargo: " << get_cargo() << '\n'
        << "Speed: " << get_speed() << '\n'
        << "Visitng a City: " << (get_is_in_city() ? "Yes" : "No") << '\n';
    return oss.str();
}