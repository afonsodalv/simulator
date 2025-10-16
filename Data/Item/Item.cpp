//
// Created by afons on 13/10/2025.
//

#include "Item.h"

Item::Item(int id,int turns_remaining, int row, int col) : id(id), turns_remaining(turns_remaining), row(row), col(col){}


int Item::get_turns_remaining() const {
    return turns_remaining;
}

std::pair<int, int> Item::get_position() const {
    return {row, col};
}

int Item::get_row() const {
    return row;
}
int Item::get_col() const{
    return col;
}

int Item::get_id() const {
    return id;
}

void Item::decrement_turns_remaining() {

    if(--turns_remaining < 0)
        turns_remaining = 0;
}