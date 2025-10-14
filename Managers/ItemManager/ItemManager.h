//
// Created by afons on 13/10/2025.
//

#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <memory>
#include <vector>

#include "..\\..\\Data\\Item\\Item.h"
#include "..\\..\\Utils\\HelperType.h"

class ItemManager {

    std::vector<std::unique_ptr<Item>> items;
    int item_interval;
    int item_duration;
    int max_items;

    bool is_nearby(const std::pair<int, int>& pos, const std::pair<int, int>& next_pos,  int max_row, int max_col) const;

    Item* find(int id) const;
public:
    ItemManager(int item_interval, int item_duration,int max_items);

    void add_item(int row, int col);

    int get_item_interval() const;
    int get_item_duration() const;
    int get_max_items() const;
    std::string get_item_description(int id) const;

    std::vector<SimulationMap> get_item_position() const;

    std::vector<int> check_nearby_items(const std::pair<int, int>& next_pos,  int max_row, int max_col) const;

    void apply_item_effect(int id, char caravan_id,GameContext& ctx);
    void remove_item_by_id(int id);

};



#endif //ITEMMANAGER_H
