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
    int max_itens;

public:
    ItemManager(int item_interval, int item_duration,int max_itens);

    int get_item_interval() const;
    int get_item_duration() const;
    int get_max_itens() const;
    std::vector<SimulationMap> get_item_position() const;
    void add_item(int row, int col);
};



#endif //ITEMMANAGER_H
