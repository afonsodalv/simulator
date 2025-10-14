//
// Created by afons on 09/10/2025.
//

#ifndef CARAVANMANAGER_H
#define CARAVANMANAGER_H


#include <memory>
#include <vector>

#include "..\\..\\Data\\Caravan\\Caravan.h"
#include "..\\..\\Utils\\HelperType.h"
#include "..\\..\\Utils\\Status.h"

class CaravanManager {

    std::vector<std::unique_ptr<Caravan>> caravans;
    int bandits_interval;
    int bandits_duration;

    Caravan* find(char id) const;

public:

    CaravanManager(int bandits_interval,int bandits_duration);

    int get_bandits_interval() const;
    int get_bandits_duration() const;
    std::string get_caravan_info(char id) const;
    std::vector<SimulationMap> get_caravans_position() const;
    std::pair<int, int>get_caravan_position(char id) const;
    std::vector<char> get_caravans_id_at(std::pair<int, int>) const;

    void add_caravan(CaravanType type, int row, int col);
    void remove_caravan(char id);

    void add_velocity(char id, int p);
    void add_crew_members(char id, int qtd);
    void lose_crew_percentage(char id, double p);

    void enter_city(char id);
    void leave_city(char id);

    void set_caravan_position(char id, std::pair<int, int> pos);

    int buy_cargo(char id, int qtd);
    int sell_cargo(char id);

    bool exist(char id) const;
};



#endif //CARAVANMANAGER_H
