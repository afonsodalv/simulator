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

public:

    CityManager();

    CityManager(int sell_price, int buy_price, int caravan_price);

    bool create_city(char id, int i, int j);
    bool check_caravan_in_city(char id, CaravanType type);

    int get_caravan_price() const;
    std::vector<SimulationMap> get_cities_info() const;
};



#endif //CITYMANAGER_H
