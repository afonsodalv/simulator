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
    int current_water;
    int current_cargo;
    int max_cargo;
    int max_water;
    bool is_in_city;

public:


    Caravan(char id, int row, int col, int crew_members,bool autonomous_behavior,int max_water, int max_cargo ,int water, int cargo, bool is_in_city);

    int get_row() const;
    int get_col() const;
    char get_id() const;
    int get_crew_members() const;
    bool get_autonomous_behavior() const;
    int get_cargo() const;
    int get_water() const;

    virtual int add_cargo(int qtd);
    int sell_all_cargo();

    virtual std::string get_info() const = 0;
    virtual void move() = 0;


};



#endif //CARAVAN_H
