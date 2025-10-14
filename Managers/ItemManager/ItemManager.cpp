//
// Created by afons on 13/10/2025.
//

#include "ItemManager.h"

#include "..\\..\\Data\\Item\\ItemFactory\\ItemFactory.h"
#include <algorithm>

ItemManager::ItemManager(int item_interval, int item_duration,int max_items):
item_interval(item_interval), item_duration(item_duration), max_items(max_items){}


Item* ItemManager::find(int id) const {

    for (const auto & item : items) {
        if (item->get_id() == id) {
            return item.get();
        }
    }

    return nullptr;
}

int ItemManager::get_item_interval() const {
    return item_interval;
}

int ItemManager::get_item_duration() const {
    return item_duration;
}

int ItemManager::get_max_items() const {
    return max_items;
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

bool ItemManager::is_nearby(const std::pair<int, int>& pos, const std::pair<int, int>& next_pos, int max_row, int max_col) const {

    int dr = (next_pos.first  - pos.first  + max_row) % max_row;
    int dc = (next_pos.second - pos.second + max_col) % max_col;

    int drow = std::min(dr, max_row - dr);
    int dcol = std::min(dc, max_col - dc);

    return (drow + dcol) <= 1;
}

std::vector<int> ItemManager::check_nearby_items(const std::pair<int, int>& next_pos, int max_row, int max_col) const {

    std::vector<int> id_items_nearby;
    for(const auto& item : items) {
        auto pos = item->get_position();

        if(is_nearby(pos, next_pos, max_row, max_col)) {
            id_items_nearby.push_back(item->get_id());
        }
    }

    return id_items_nearby;
}

void  ItemManager::apply_item_effect(int id, char caravan_id,GameContext& ctx) {
    if(auto item = find(id)) item->apply_effect(ctx, caravan_id);
}

void  ItemManager::remove_item_by_id(int id) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if ((*it)->get_id() == id) {
            items.erase(it);
            break;
        }
    }
}

std::string ItemManager::get_item_description(int id) const {
    if(auto item = find(id)) return item->get_description();
    return "Item not found.";
}
