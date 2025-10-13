//
// Created by afons on 13/10/2025.
//

#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <vector>

#include "..\\..\\Data\\Item\\Item.h"

class ItemManager {

    std::vector<Item> items;
    int item_interval;
    int item_duration;
    int max_itens;

public:
    ItemManager(int item_interval, int item_duration,int max_itens);

    int get_item_interval() const;
    int get_item_duration() const;
    int get_max_itens() const;

    void add_item(int item_duration, int row, int col);
};



#endif //ITEMMANAGER_H
