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

    auto my_pos = get_position();



    if (get_crew_members() == 0) {

        add_turns_left(-1);
        std::pair<int , int> next_pos = move_random(mc.row, mc.col);

        if (std::ranges::find(mc.desert, next_pos) != mc.desert.end())
            return next_pos;

        return my_pos;
    }

    std::pair target = get_closest_target_position(mc.row, mc.col, 2, '?',mc.items);

    if(target.first == -1) {
        target = get_closest_player_caravan_position(mc.row, mc.col, 4, caravans);

        if (target.first == -1) {
            std::pair<int , int> next_pos = move_random(mc.row, mc.col);

            if (std::ranges::find(mc.desert, next_pos) != mc.desert.end())
                return next_pos;

            return my_pos;
        }
    }

    std::pair direction = {0, 0};

    if (target.first > my_pos.first) direction.first = 1;
    else if (target.first < my_pos.first) direction.first = -1;

    if (target.second > my_pos.second) direction.second = 1;
    else if (target.second < my_pos.second) direction.second = -1;

    auto new_pos = std::pair<int,int>{
        my_pos.first + direction.first,
        my_pos.second + direction.second
    };

    new_pos.first  = (new_pos.first  + mc.row) % mc.row;
    new_pos.second = (new_pos.second + mc.col) % mc.col;

    if (std::ranges::find(mc.desert, new_pos) == mc.desert.end())
        return my_pos;

    return new_pos;

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
        << "Water: " << get_current_water() << '\n'
        << "Cargo: " << get_cargo() << '\n'
        << "Speed: " << get_speed() << '\n'
        << "Visitng a City: " << (get_is_in_city() ? "Yes" : "No") << '\n';
    return oss.str();
}

void CommercialCaravan::consume_water(){

    if(get_current_water() == 0) {
        add_crew_members(-1);
        return;
    }

    if(get_crew_members() < max_crew/2) {
        decrement_water(1);
    }
    else
        decrement_water(2);
}