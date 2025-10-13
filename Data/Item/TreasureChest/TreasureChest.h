//
// Created by afons on 13/10/2025.
//

#ifndef TRESURECHEST_H
#define TRESURECHEST_H


#include "..\\Item.h"

class TreasureChest : public Item {

public:
    TreasureChest(int turns_remaining, int row, int col);
    void apply_effect(GameContext& ctx, char id) override;
};



#endif //TRESURECHEST_H
