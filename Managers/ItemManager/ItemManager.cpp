//
// Created by afons on 13/10/2025.
//

#include "ItemManager.h"

#include "..\\..\\Data\\Item\\ItemFactory\\ItemFactory.h"


ItemManager::ItemManager(int item_interval, int item_duration,int max_itens):
item_interval(item_interval), item_duration(item_duration), max_itens(max_itens){}

int ItemManager::get_item_interval() const {
    return item_interval;
}
int ItemManager::get_item_duration() const {
    return item_duration;
}
int ItemManager::get_max_itens() const {
    return max_itens;
}


void ItemManager::add_item(int row, int col) {
    items.push_back(ItemFactory::create_random(item_duration, row, col));
}

std::vector<SimulationMap> ItemManager::get_item_position() const {
    std::vector<SimulationMap> items_info;

    for(const auto& item : items) {
        items_info.emplace_back(Type::Item, item->get_row(), item->get_col());
    }
    return items_info;
}