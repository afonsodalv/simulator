//
// Created by afons on 09/10/2025.
//

#ifndef BUILDERCARAVAN_H
#define BUILDERCARAVAN_H

#include "..\\Caravan.h"

class BuilderCaravan : public Caravan {

    static int max_crew;
    static int max_cargo;
    static int max_water;
    static int initial_crew;
    static int speed;


public:
    BuilderCaravan(char id, int row, int col);
    void move() override;
    void reset_velocity() override;
    std::string get_info() const override;
};



#endif //BUILDERCARAVAN_H
