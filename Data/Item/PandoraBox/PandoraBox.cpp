//
// Created by afons on 13/10/2025.
//

#include "PandoraBox.h"

#include "..\\..\\..\\Utils\\GameContext\\GameContext.h"
PandoraBox::PandoraBox(int turns_remaining, int row, int col):
Item(turns_remaining, row, col){}

void PandoraBox::apply_effect(GameContext& ctx, char id){
    ctx.lose_crew_percentage(id, 0.2);
}