//
// Created by afons on 13/10/2025.
//

#include "GameContext.h"
#include "..\\..\\Managers\\CaravanManager\\CaravanManager.h"
#include "..\\IEconomy.h"
GameContext::GameContext(CaravanManager& caravans, IEconomy& economy, std::pair<int, int> pos) : caravan_manager(caravans), economy(economy), pos(pos){}

void GameContext::destroy(char id) {

    if(id == '!')
        caravan_manager.remove_caravan(pos);
    else
        caravan_manager.remove_caravan(id);
}

void GameContext::lose_crew_percentage(char id, double p) {

    caravan_manager.lose_crew_percentage(id, p);
}

void GameContext::add_crew_members(char id, int qtd) {
    caravan_manager.add_crew_members(id, qtd);
}

void GameContext::add_coin_percentage(double p) {

    if (p <= 0.0)
        return;

    int coins = static_cast<int>(economy.get_coins() * p);

    economy.add_coins(coins);
}

void GameContext::add_velocity(char id, int v) {
    caravan_manager.add_speed(id, v);
}