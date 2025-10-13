//
// Created by afons on 13/10/2025.
//

#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <memory>

class Item;

class ItemFactory {

   static int rng_int(int lo, int hi);
public:
    static std::unique_ptr<Item> create_random(int turns_remaining, int row, int col);
};



#endif //ITEMFACTORY_H
