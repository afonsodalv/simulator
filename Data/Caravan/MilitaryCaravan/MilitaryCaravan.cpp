//
// Created by afons on 09/10/2025.
//

#include "MilitaryCaravan.h"


int MilitaryCaravan::initial_crew = 30;
int MilitaryCaravan::max_crew = 40;
int MilitaryCaravan::max_cargo = 5;
int MilitaryCaravan::max_water = 400;


MilitaryCaravan::MilitaryCaravan(char id, int row, int col)
: Caravan(id, row, col, initial_crew, false, max_water, 0, true) {}

void MilitaryCaravan::move() {

}