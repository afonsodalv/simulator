//
// Created by afons on 13/10/2025.
//

#include "Cage.h"

#include "..\\..\\..\\Utils\\GameContext\\GameContext.h"

Cage::Cage(int id, int turns_remaining, int row, int col) : Item(id, turns_remaining, row, col){}

void Cage::apply_effect(GameContext& ctx, char id){
    ctx.add_crew_members(id, 10);
}

std::string Cage::get_description() const {
    return "You freed prisoners from a cage! they joined your crew.";
}