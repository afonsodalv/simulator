//
// Created by afons on 13/10/2025.
//

#include "Item.h"

Item::Item(int turns_remaining, int row, int col) : turns_remaining(turns_remaining), row(row), col(col){}


int Item::get_turns_remaining() const {
    return turns_remaining;
}
std::pair<int, int> Item::get_position() const {
    return {row, col};
}