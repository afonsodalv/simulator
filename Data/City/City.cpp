//
// Created by afons on 08/10/2025.
//

#include "City.h"

#include <sstream>

City::City(char id, int row, int col) : id(id), row(row),col(col) {

    available_caravans ={
        { CaravanType::Commercial, 1 },
        { CaravanType::Military,   1 },
        { CaravanType::Builder,    1 },
    };
}

char City::get_id() const {
    return id;
}

int City::get_row() const {
    return row;
}
int City::get_col() const{
    return col;
}

std::string City::get_info() const {

    std::ostringstream os;
    for(const auto& aux : available_caravans ) {

        switch(aux.first) {
            case CaravanType::Commercial:
                os<<"Comercial Caravan: "<<aux.second<<" available"<<std::endl;
                break;
            case CaravanType::Military:
                os<<"Comercial Military: "<<aux.second<<" available"<<std::endl;
                break;
            case CaravanType::Builder:
                os<<"Comercial Builder: "<<aux.second<<" available"<<std::endl;
                break;
            default:
                os<<"No more Caravans"<<std::endl;
        }
    }

    return os.str();
}

bool City::buy_caravan(CaravanType type) {
    auto it = available_caravans.find(type);
    if (it != available_caravans.end() && it->second > 0) {
        --it->second;
        return true;
    }
    return false;
}