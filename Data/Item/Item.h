//
// Created by afons on 13/10/2025.
//

#ifndef ITEM_H
#define ITEM_H

#include <utility>


class GameContext;

class Item {

    int turns_remaining;
    int row;
    int col;
public:
    Item(int turns_remaining, int row, int col);


    int get_turns_remaining() const;
    std::pair<int, int> get_position() const;

    virtual void apply_effect(GameContext& ctx, char id) = 0 ;

};



#endif //ITEM_H
