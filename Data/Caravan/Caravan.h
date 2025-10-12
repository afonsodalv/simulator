//
// Created by afons on 09/10/2025.
//

#ifndef CARAVAN_H
#define CARAVAN_H
#include <string>


class Caravan {

    char id;
    int row;
    int col;
    int crew_members;
    bool autonomous_behavior;
    int water;
    int cargo;
    bool is_in_city;

public:


    Caravan(char id, int row, int col, int crew_members,bool autonomous_behavior, int water, int cargo, bool is_in_city);

    int get_row() const;
    int get_col() const;
    char get_id() const;

    void add_goods();
    void sell_goods();
    virtual std::string get_info() const;
    virtual void move() = 0;


};



#endif //CARAVAN_H
