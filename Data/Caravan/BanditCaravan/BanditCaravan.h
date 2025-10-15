//
// Created by afons on 09/10/2025.
//

#ifndef BANDITCARAVAN_H
#define BANDITCARAVAN_H


#include "..\\Caravan.h"

class BanditCaravan : public Caravan {

    static int initial_crew;
    static int max_crew;
    static int speed;
public:
    BanditCaravan(char id, int row, int col, int bandits_duration);
    std::pair<int, int> move_autonomous(const std::vector<SimulationMap>&caravans, MoveContext& mc) override;
    void reset_speed() override;
    std::string get_info() const override;
};



#endif //BANDITCARAVAN_H
