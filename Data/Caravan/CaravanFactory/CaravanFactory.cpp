//
// Created by afons on 09/10/2025.
//

#include "CaravanFactory.h"

#include "..\\CommercialCaravan\\CommercialCaravan.h"
#include "..\\BanditCaravan\\BanditCaravan.h"
#include "..\\MilitaryCaravan\\MilitaryCaravan.h"
#include "..\\BuilderCaravan\\BuilderCaravan.h"

using namespace factory;

std::unique_ptr<Caravan> createCaravan(CaravanType type, int row, int col) {
    static char id = '0';
    switch (type) {
        case CaravanType::Commercial:
            return std::make_unique<CommercialCaravan>(id,row, col);
        case CaravanType::Military:
            return std::make_unique<MilitaryCaravan>(id,row, col);
        case CaravanType::Builder:
            return std::make_unique<BuilderCaravan>(id,row, col);
        default:
            return nullptr;
    }
}

std::unique_ptr<BanditCaravan> createBandit(int row, int col) {
    return std::make_unique<BanditCaravan>(row, col);
}

