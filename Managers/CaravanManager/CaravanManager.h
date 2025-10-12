//
// Created by afons on 09/10/2025.
//

#ifndef CARAVANMANAGER_H
#define CARAVANMANAGER_H


#include <memory>
#include <vector>

#include "..\\..\\Data\\Caravan\\Caravan.h"
#include "..\\..\\Utils\\HelperType.h"

class CaravanManager {

    std::vector<std::unique_ptr<Caravan>> caravans;
    int bandits_interval;
    int bandits_duration;
public:

    CaravanManager(int bandits_interval,int bandits_duration);

    int get_bandits_interval() const;
    int get_bandits_duration() const;
    void add_caravan(CaravanType type, int row, int col);


    std::string get_caravan_info(char id) const;
    std::vector<SimulationMap> get_caravans_position() const;
};



#endif //CARAVANMANAGER_H
