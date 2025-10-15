//
// Created by afons on 09/10/2025.
//

#include "BanditCaravan.h"

int BanditCaravan::initial_crew = 40;
int BanditCaravan::max_crew = 50;
int BanditCaravan::speed = 1;

BanditCaravan::BanditCaravan(char id, int row, int col, int bandits_duration) : Caravan(id, row, col, speed,initial_crew, bandits_duration ,true, 0, 0,0, 0,max_crew,false){}


std::pair<int, int> BanditCaravan::move_autonomous(const std::vector<SimulationMap>&caravans, MoveContext& mc){
    return {-1, -1};
}

void BanditCaravan::reset_speed(){
    set_speed(speed);
}
std::string BanditCaravan::get_info() const {
    return "Bandits refuse to tell you what they have!";
}