//
// Created by afons on 13/10/2025.
//

#include "GoldenWhistle.h"
#include "..\\..\\..\\Utils\\GameContext\\GameContext.h"

GoldenWhistle::GoldenWhistle(int id, int turns_remaining, int row, int col):Item(id,turns_remaining, row, col){}

void GoldenWhistle::apply_effect(GameContext& ctx, char id) {
    ctx.add_velocity(id, 3);
}

std::string GoldenWhistle::get_description() const {
    return "You've found the Golden Whistle. With the help of the wind, you have extra speed this turn.";
}