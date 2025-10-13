//
// Created by afons on 13/10/2025.
//

#include "Mine.h"

#include "..\\..\\..\\Utils\\GameContext\\GameContext.h"
Mine::Mine(int turns_remaining, int row, int col): Item(turns_remaining, row, col){}

void Mine::apply_effect(GameContext& ctx, char id){
    ctx.destroy(id);
}