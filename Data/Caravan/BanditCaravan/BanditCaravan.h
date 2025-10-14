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
    BanditCaravan(char id, int row, int col);
    void move() override;
    void reset_velocity() override;
    std::string get_info() const override;
};



#endif //BANDITCARAVAN_H
