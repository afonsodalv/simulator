//
// Created by afons on 13/10/2025.
//

#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <utility>


class GameContext;

class Item {

    int id;
    int turns_remaining;
    int row;
    int col;
public:
    Item(int id, int turns_remaining, int row, int col);


    int get_turns_remaining() const;
    std::pair<int, int> get_position() const;
    int get_row() const;
    int get_col() const;
    int get_id() const;

    virtual std::string get_description() const = 0;
    virtual void apply_effect(GameContext& ctx, char id) = 0 ;

};



#endif //ITEM_H
