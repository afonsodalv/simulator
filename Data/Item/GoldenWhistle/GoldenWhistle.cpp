//
// Created by afons on 13/10/2025.
//

#include "GoldenWhistle.h"
#include "..\\..\\..\\Utils\\GameContext\\GameContext.h"

GoldenWhistle::GoldenWhistle(int turns_remaining, int row, int col):Item(turns_remaining, row, col){}

void GoldenWhistle::apply_effect(GameContext& ctx, char id) {
    ctx.add_velocity(id, 3);
}