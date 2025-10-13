//
// Created by afons on 13/10/2025.
//

#ifndef MINE_H
#define MINE_H

#include "..\\Item.h"

class Mine : public Item {

public:
    Mine(int turns_remaining, int row, int col);
    void apply_effect(GameContext& ctx, char id) override;
};



#endif //MINE_H
