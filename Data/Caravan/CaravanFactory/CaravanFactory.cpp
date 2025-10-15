//
// Created by afons on 09/10/2025.
//

#include "CaravanFactory.h"

#include "..\\CommercialCaravan\\CommercialCaravan.h"
#include "..\\BanditCaravan\\BanditCaravan.h"
#include "..\\MilitaryCaravan\\MilitaryCaravan.h"
#include "..\\BuilderCaravan\\BuilderCaravan.h"


std::unique_ptr<Caravan> CaravanFactory::createCaravan(CaravanType type, int row, int col, int bandits_duration) {
    static char id = '0';

    if(id > '9')
        return nullptr;

    switch (type) {
        case CaravanType::Commercial:
            return std::make_unique<CommercialCaravan>(id++,row, col);
        case CaravanType::Military:
            return std::make_unique<MilitaryCaravan>(id++,row, col);
        case CaravanType::Builder:
            return std::make_unique<BuilderCaravan>(id++,row, col);
        case CaravanType::Bandit:
            return std::make_unique<BanditCaravan>('!', row, col, bandits_duration);
        default:
            return nullptr;
    }
}


