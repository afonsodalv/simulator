//
// Created by afons on 09/10/2025.
//

#ifndef MILITARYCARAVAN_H
#define MILITARYCARAVAN_H

#include "..\\Caravan.h"

class MilitaryCaravan : public Caravan {

    static int max_crew;
    static int max_cargo;
    static int max_water;
    static int initial_crew;
    static int speed;
    static int turns_left_after_no_crew;
    std::pair<int, int> last_direction;


public:
    MilitaryCaravan(char id, int row, int col);

    std::string get_info() const override;
    void reset_speed() override;
    std::pair<int, int> move_autonomous(const std::vector<SimulationMap>&caravans, MoveContext& mc) override;
    void set_last_direction(std::pair<int, int> ld) override;
};



#endif //MILITARYCARAVAN_H
