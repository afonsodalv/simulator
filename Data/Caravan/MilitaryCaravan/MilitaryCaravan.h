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
    static int velocity;
public:
    MilitaryCaravan(char id, int row, int col);

    std::string get_info() const override;
    void reset_velocity() override;
    void move() override;
};



#endif //MILITARYCARAVAN_H
