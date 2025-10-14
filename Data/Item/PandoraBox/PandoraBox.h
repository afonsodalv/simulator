//
// Created by afons on 13/10/2025.
//

#ifndef PANDORABOX_H
#define PANDORABOX_H

#include "..\\Item.h"

class PandoraBox : public Item {

public:
    PandoraBox(int id,int turns_remaining, int row, int col);
    void apply_effect(GameContext& ctx, char id) override;
    std::string get_description() const override;
};



#endif //PANDORABOX_H
