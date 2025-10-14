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
public:
    CommercialCaravan(char id, int row, int col);

    void move() override;
    void reset_velocity() override;
    std::string get_info() const override;
};



#endif //COMMERCIALCARAVAN_H
