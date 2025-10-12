//
// Created by afons on 09/10/2025.
//

#ifndef BANDITCARAVAN_H
#define BANDITCARAVAN_H


#include "..\\Caravan.h"

class BanditCaravan : public Caravan {

    static int initial_crew;
public:
    BanditCaravan(char id, int row, int col);
    void move() override;
};



#endif //BANDITCARAVAN_H
