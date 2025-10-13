//
// Created by afons on 09/10/2025.
//

#include "BanditCaravan.h"

int BanditCaravan::initial_crew = 40;
int BanditCaravan::max_crew = 50;
int BanditCaravan::velocity = 1;

BanditCaravan::BanditCaravan(char id, int row, int col) : Caravan(id, row, col, velocity,initial_crew, true, 0, 0,0, 0,max_crew,false){}


void BanditCaravan::move(){

}

void BanditCaravan::reset_velocity(){
    set_velocity(velocity);
}
std::string BanditCaravan::get_info() const {
    return "Bandits refuse to tell you what they have!";
}