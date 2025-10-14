//
// Created by afons on 13/10/2025.
//

#include "ItemFactory.h"
#include <random>

#include "..\\Cage\\Cage.h"
#include "..\\PandoraBox\\PandoraBox.h"
#include "..\\TreasureChest\\TreasureChest.h"
#include "..\\Mine\\Mine.h"
#include "..\\GoldenWhistle\\GoldenWhistle.h"

int ItemFactory::rng_int(int low, int high) {
    if (low > high) std::swap(low, high);

    static thread_local std::mt19937 rng{ std::random_device{}() };
    std::uniform_int_distribution<int> dist(low, high);
    return dist(rng);
}

std::unique_ptr<Item> ItemFactory::create_random(int turns_remaining, int row, int col) {

    static int id = 0;

    switch (rng_int(0, 4)) {
        case 0: return std::make_unique<PandoraBox>(id++, turns_remaining, row, col);
        case 1: return std::make_unique<TreasureChest>(id++,turns_remaining, row, col);
        case 2: return std::make_unique<Cage>(id++,turns_remaining, row, col);
        case 3: return std::make_unique<Mine>(id++,turns_remaining, row, col);
        default: return std::make_unique<GoldenWhistle>(id++,turns_remaining, row, col);
    }
}