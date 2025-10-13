//
// Created by afons on 13/10/2025.
//

#ifndef WALLET_H
#define WALLET_H

#include <algorithm>

#include "..\\IEconomy.h"

class Wallet : public IEconomy {
    int coins;

public:
    explicit Wallet(int startingCoins = 0)
        : coins(startingCoins) {}

    void add_coins(int qtd) override {
        coins = std::max(0, qtd + coins);
    }

    int get_coins() const override {
        return coins;
    }

};



#endif //WALLET_H
