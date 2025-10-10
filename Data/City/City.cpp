//
// Created by afons on 08/10/2025.
//

#include "City.h"

City::City(char id, int row, int col) : id(id), row(row),col(col) {}

char City::get_id() const {
    return id;
}

int City::get_row() const {
    return row;
}
int City::get_col() const{
    return col;
}

bool City::is_caravan_available(CaravanType type) {
    auto it = available_caravans.find(type);
    if (it != available_caravans.end() && it->second > 0) {
        --it->second;
        return true;
    }
    return false;
}