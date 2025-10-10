//
// Created by afons on 08/10/2025.
//

#include "CityManager.h"


#include "..\\..\\Data\\City\\City.h"
using namespace std;


CityManager::CityManager() : CityManager(2, 1, 100) {}

CityManager::CityManager(int sell_price, int buy_price,int caravan_price) : sell_price(sell_price)
,buy_price(buy_price),caravan_price(caravan_price) {}

bool CityManager::create_city(char id, int i, int j) {

    if(id < 'a' || id > 'z')
        return false;

    for(auto & citie : cities) {
        if(citie->get_id() == id)
            return false;
    }

    cities.emplace_back(make_unique<City>(id, i, j));
    return true;
}

int CityManager::get_caravan_price() const {
    return caravan_price;
}

std::vector<SimulationMap> CityManager::get_cities_info() const {
    vector<SimulationMap> cities_info;

    for(const auto& city : cities) {
         cities_info.emplace_back(Type::City, city->get_row(), city->get_col(), city->get_id());
    }
    return cities_info;
}

bool CityManager::check_caravan_in_city(char id, CaravanType type) {

    for(auto it = cities.begin(); it != cities.end();++it) {
        if((*it)->get_id() == id) {
            return (*it)->is_caravan_available(type);
        }
    }

    return false;
}