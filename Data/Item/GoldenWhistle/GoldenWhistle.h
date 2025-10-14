//
// Created by afons on 13/10/2025.
//

#ifndef GOLDENWHISTLE_H
#define GOLDENWHISTLE_H

#include "..\\Item.h"

class GoldenWhistle : public Item {

public:
    GoldenWhistle(int id, int turns_remaining, int row, int col);
    void apply_effect(GameContext& ctx, char id) override;
    std::string get_description() const override;
};



#endif //GOLDENWHISTLE_H
