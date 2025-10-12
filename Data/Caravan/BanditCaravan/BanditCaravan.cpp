//
// Created by afons on 09/10/2025.
//

#include "BanditCaravan.h"

int BanditCaravan::initial_crew = 40;

BanditCaravan::BanditCaravan(char id, int row, int col) : Caravan(id, row, col, initial_crew, true, 0, 0,0, 0,false){}


void BanditCaravan::move(){

}


std::string BanditCaravan::get_info() const {
    return "Bandits refuse to tell you what they have!";
}