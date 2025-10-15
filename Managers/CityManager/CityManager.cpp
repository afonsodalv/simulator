//
// Created by afons on 08/10/2025.
//

#include "CityManager.h"


#include "..\\..\\Data\\City\\City.h"
using namespace std;


CityManager::CityManager() : CityManager(2, 1, 100) {}

CityManager::CityManager(int sell_price, int buy_price,int caravan_price) : sell_price(sell_price)
,buy_price(buy_price),caravan_price(caravan_price) {}


City* CityManager::find(char id) const {

    for (const auto & city : cities) {
        if (city->get_id() == id) {
            return city.get();
        }
    }
    return nullptr;
}

bool CityManager::find(pair<int, int> pos) const {

    for (const auto & city : cities) {
        if (city->get_row() == pos.first && city->get_col() == pos.second) {
            return true;
        }
    }
    return false;
}

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

int CityManager::get_sell_price() const {
    return sell_price;
}

int CityManager::get_buy_price() const {
    return buy_price;
}

std::string CityManager::get_city_info(char id) const {

    if(auto city = find(id)) return city->get_info();
    return "City doesn't exit";
}

std::vector<SimulationMap> CityManager::get_cities_info() const {
    vector<SimulationMap> cities_info;

    for(const auto& city : cities) {
         cities_info.emplace_back(Type::City, city->get_row(), city->get_col(), city->get_id());
    }
    return cities_info;
}

std::pair<int, int> CityManager::get_city_coordinates(char id) const {

    if(auto city = find(id)) return {city->get_row(), city->get_col()};
    return {-1, -1};
}

bool CityManager::buy_caravan_in_city(char id, CaravanType type) {

    if(auto city = find(id)) return city->buy_caravan(type);
    return false;
}

bool CityManager::is_a_city(std::pair<int,int> pos) {
    return find(pos);
}

std::vector<std::pair<int, int>> CityManager::get_cities_position() const {

    std::vector<std::pair<int, int>> pos;

    for(const auto& city : cities) {
        pos.emplace_back(city->get_row(), city->get_col());
    }
    return pos;
}