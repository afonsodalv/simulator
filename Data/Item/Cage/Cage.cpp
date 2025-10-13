//
// Created by afons on 13/10/2025.
//

#include "Cage.h"

#include "..\\..\\..\\Utils\\GameContext\\GameContext.h"

Cage::Cage(int turns_remaining, int row, int col) : Item(turns_remaining, row, col){}

void Cage::apply_effect(GameContext& ctx, char id){
    ctx.add_crew_members(id, 10);
}