//
// Created by afons on 09/10/2025.
//

#include "BanditCaravan.h"

int BanditCaravan::initial_crew = 40;
int BanditCaravan::max_crew = 50;
int BanditCaravan::speed = 1;

BanditCaravan::BanditCaravan(char id, int row, int col, int bandits_duration) : Caravan(id, row, col, speed,initial_crew, bandits_duration ,true, 0, 0,0, 0,max_crew,false){}

std::pair<int, int> BanditCaravan::move_autonomous(const std::vector<SimulationMap>&caravans, MoveContext& mc){


    auto my_pos = get_position();

    std::pair target = get_closest_player_caravan_position(mc.row, mc.col, 8, caravans);

    if (target.first == -1) {

        std::pair<int , int> next_pos = move_random(mc.row, mc.col);

        if (std::ranges::find(mc.desert, next_pos) != mc.desert.end())
            return next_pos;

        return my_pos;
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

void BanditCaravan::reset_speed(){
    set_speed(speed);
}
std::string BanditCaravan::get_info() const {
    return "Bandits refuse to tell you what they have!";
}