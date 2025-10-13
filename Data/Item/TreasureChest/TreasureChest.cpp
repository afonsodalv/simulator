//
// Created by afons on 13/10/2025.
//

#include "TreasureChest.h"
#include "..\\..\\..\\Utils\\GameContext\\GameContext.h"

TreasureChest::TreasureChest(int turns_remaining, int row, int col) :
Item(turns_remaining, row, col){}

void TreasureChest::apply_effect(GameContext& ctx, char id) {
    ctx.add_coin_percentage(0.1);
}