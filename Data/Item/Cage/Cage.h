//
// Created by afons on 13/10/2025.
//

#ifndef CAGE_H
#define CAGE_H

#include "..\\Item.h"

class Cage : public Item{

public:
    Cage(int turns_remaining, int row, int col);
    void apply_effect(GameContext& ctx, char id) override;
};



#endif //CAGE_H
