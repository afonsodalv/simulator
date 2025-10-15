//
// Created by afons on 08/10/2025.
//

#ifndef CITYMANAGER_H
#define CITYMANAGER_H
#include <memory>
#include <vector>

#include "..\\..\\Utils\\HelperType.h"
#include "..\\..\\Data\\City\\City.h"


class CityManager {
    std::vector<std::unique_ptr<City>> cities;
    int sell_price;
    int buy_price;
    int caravan_price;

    City* find(char id) const;
    bool find(std::pair<int, int>) const;

public:

    CityManager();

    CityManager(int sell_price, int buy_price, int caravan_price);

    bool create_city(char id, int i, int j);

    bool buy_caravan_in_city(char id, CaravanType type);
    bool is_a_city(std::pair<int,int> pos);

    int get_caravan_price() const;
    int get_sell_price() const;
    int get_buy_price() const;


    std::pair<int, int> get_city_coordinates(char id) const;
    std::string get_city_info(char id) const;
    std::vector<SimulationMap> get_cities_info() const;
    std::vector<std::pair<int, int>> get_cities_position() const;
};



#endif //CITYMANAGER_H
