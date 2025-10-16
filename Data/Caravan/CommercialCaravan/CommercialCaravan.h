//
// Created by afons on 09/10/2025.
//

#ifndef COMMERCIALCARAVAN_H
#define COMMERCIALCARAVAN_H

#include "..\\Caravan.h"


class CommercialCaravan : public Caravan {

    static int max_crew;
    static int max_cargo;
    static int max_water;
    static int initial_crew;
    static int speed;
    static int turns_left_after_no_crew;
public:
    CommercialCaravan(char id, int row, int col);

    std::pair<int, int> move_autonomous(const std::vector<SimulationMap>&caravans, MoveContext& mc) override;
    void reset_speed() override;
    void consume_water() override;
    std::string get_info() const override;
};



#endif //COMMERCIALCARAVAN_H
