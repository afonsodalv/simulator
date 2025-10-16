//
// Created by afons on 09/10/2025.
//

#ifndef CARAVANMANAGER_H
#define CARAVANMANAGER_H


#include <memory>
#include <set>
#include <vector>

#include "..\\..\\Data\\Caravan\\Caravan.h"
#include "..\\..\\Utils\\HelperType.h"
#include "..\\..\\Utils\\Status.h"

class CaravanManager {

    std::vector<std::unique_ptr<Caravan>> caravans;
    int bandits_interval;
    int bandits_duration;

    Caravan* find(char id) const;

    static void update_map_positions(Caravan* caravan,const std::pair<int,int>& next_pos,MoveContext& mc);
    std::vector<Caravan*> get_bandits_caravans() const;
public:

    CaravanManager(int bandits_interval,int bandits_duration);

    int get_bandits_interval() const;
    int get_bandits_duration() const;
    std::string get_caravan_info(char id) const;
    std::vector<SimulationMap> get_caravans_position_map() const;
    std::pair<int, int>get_caravan_position(char id) const;
    std::vector<char> get_caravans_id_at_city(std::pair<int, int>) const;
    std::vector<char> get_autonomous_caravans_id() const;

    void add_caravan(CaravanType type, int row, int col);
    void remove_caravan(char id);
    void remove_caravan(const std::pair<int, int> pos);

    void add_speed(char id, int p);
    void add_crew_members(char id, int qtd);
    void lose_crew_percentage(char id, double p);

    void enter_city(char id);
    void leave_city(char id);

    void set_caravan_position(char id, std::pair<int, int> pos);

    int buy_cargo(char id, int qtd);
    int sell_cargo(char id);

    bool exist(char id) const;

    std::vector<char> move_autonomous(MoveContext& mc);

    Status move_caravan(char id, std::pair<int, int> pos, MoveContext& mc);
    Status put_caravan_on_auto(char id);

    std::vector<std::string> combat_phase(int row, int col);
    std::vector<std::string>handle_caravans_life_time();

    void handle_speed_and_water_consumption();
    void handle_bandits_spawn(int turns, std::vector<std::pair<int,int>>& desert);
};



#endif //CARAVANMANAGER_H
