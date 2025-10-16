//
// Created by afons on 09/10/2025.
//

#include "MilitaryCaravan.h"
#include <sstream>

int MilitaryCaravan::initial_crew = 30;
int MilitaryCaravan::max_crew = 40;
int MilitaryCaravan::max_cargo = 5;
int MilitaryCaravan::max_water = 400;
int MilitaryCaravan::speed = 3;
int MilitaryCaravan::turns_left_after_no_crew = 7;


MilitaryCaravan::MilitaryCaravan(char id, int row, int col)
: Caravan(id, row, col,speed ,initial_crew,turns_left_after_no_crew ,false,max_water, max_cargo ,max_water, max_cargo, max_crew,true) {}

std::pair<int, int> MilitaryCaravan::move_autonomous(const std::vector<SimulationMap>&caravans, MoveContext& mc) {

    auto my_pos = get_position();

    if(get_crew_members() == 0) {

        my_pos.first += last_direction.first;
        my_pos.second += last_direction.second;
        auto it_desert = std::ranges::find(mc.desert, my_pos);
        add_turns_left(-1);

        if(it_desert == mc.desert.end()) {
            return  get_position();
        }
        return my_pos;
    }


    std::pair target = get_closest_target_position(mc.row, mc.col, 6,'!' ,caravans);

    if (target.first == -1)
        return my_pos;

    std::pair direction = {0, 0};

    if (target.first > my_pos.first) direction.first = 1;
    else if (target.first < my_pos.first) direction.first = -1;

    if (target.second > my_pos.second) direction.second = 1;
    else if (target.second < my_pos.second) direction.second = -1;

    last_direction = direction;

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

void MilitaryCaravan::reset_speed(){
    set_speed(speed);
}

void MilitaryCaravan::set_last_direction(std::pair<int, int> ld) {
    last_direction = ld;
}

std::string MilitaryCaravan::get_info() const {
    std::ostringstream oss;
    oss << "Caravan " << get_id() << '\n'
        <<"Type: Military\n"
        << "Crew members: " << get_crew_members() << '\n'
        << "Autonomous behavior: " << (get_autonomous_behavior() ? "Yes" : "No") << '\n'
        << "Water: " << get_current_water() << '\n'
        << "Cargo: " << get_cargo() << '\n'
        << "Speed: " << get_speed() << '\n'
        << "Visitng a City: " << (get_is_in_city() ? "Yes" : "No") << '\n';
    return oss.str();
}

void MilitaryCaravan::consume_water(){

    if(get_current_water() == 0) {
        //Should add -1 water as in the assignment description but since this project
        //is not for grading, I won't put because doesn't make sense.
        add_crew_members(-1);
        return;
    }

    if(get_crew_members() < max_crew/2) {
        decrement_water(1);
    }
    else
        decrement_water(3);
}

