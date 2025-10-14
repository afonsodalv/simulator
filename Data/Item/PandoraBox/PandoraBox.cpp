//
// Created by afons on 13/10/2025.
//

#include "PandoraBox.h"

#include "..\\..\\..\\Utils\\GameContext\\GameContext.h"
PandoraBox::PandoraBox(int id, int turns_remaining, int row, int col):
Item(id,turns_remaining, row, col){}

void PandoraBox::apply_effect(GameContext& ctx, char id){
    ctx.lose_crew_percentage(id, 0.2);
}

std::string PandoraBox::get_description() const {
    return "You've found Pandora’s Box. Some of your crew got sick and perished.";
}