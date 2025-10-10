//
// Created by afons on 09/10/2025.
//

#ifndef CARAVAN_H
#define CARAVAN_H



class Caravan {

    char id;
    int row;
    int col;
    static char next_caravan_id;
    int crew_members;
    bool autonomous_behavior;
    int water;
    int cargo;

public:

    Caravan();

};



#endif //CARAVAN_H
