//
// Created by afons on 09/10/2025.
//

#include "CommercialCaravan.h"


int CommercialCaravan::initial_crew = 20;
int CommercialCaravan::max_crew = 25;
int CommercialCaravan::max_cargo = 40;
int CommercialCaravan::max_water = 200;

CommercialCaravan::CommercialCaravan(char id, int row, int col)
: Caravan(id, row, col, initial_crew, false, max_water, 0, true) {}

void CommercialCaravan::move() {

}