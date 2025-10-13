//
// Created by afons on 13/10/2025.
//

#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H


class CaravanManager;
class IEconomy;

class GameContext {
    CaravanManager& caravan_manager;
    IEconomy&        economy;

public:
    GameContext(CaravanManager& caravans, IEconomy& economy);

    void destroy(char id);
    void lose_crew_percentage(char id, double p);
    void add_crew_members(char id, int qtd);
    void add_coin_percentage(double p);
    void add_velocity(char id, int v);
};



#endif //GAMECONTEXT_H
