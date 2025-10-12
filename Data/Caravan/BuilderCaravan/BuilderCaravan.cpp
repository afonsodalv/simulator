//
// Created by afons on 09/10/2025.
//

#include "BuilderCaravan.h"

int BuilderCaravan::initial_crew = 15;
int BuilderCaravan::max_crew = 20;
int BuilderCaravan::max_cargo = 5;
int BuilderCaravan::max_water = 200;


BuilderCaravan::BuilderCaravan(char id, int row, int col)
: Caravan(id, row, col, initial_crew, false, max_water, 0, true) {}

void BuilderCaravan::move() {

}