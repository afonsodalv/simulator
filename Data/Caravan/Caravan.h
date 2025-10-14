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
    int speed;
    int crew_members;
    bool autonomous_behavior;
    int current_water;
    int current_cargo;
    int max_cargo;
    int max_water;
    int max_crew;
    bool is_in_city;

public:
    virtual ~Caravan() = default;


    Caravan(char id, int row, int col, int speed,int crew_members,bool autonomous_behavior,int max_water, int max_cargo ,int water, int cargo,int max_crew ,bool is_in_city);

    int get_row() const;
    int get_col() const;
    int get_speed() const;
    char get_id() const;
    int get_crew_members() const;
    bool get_autonomous_behavior() const;
    int get_cargo() const;
    int get_water() const;
    bool get_is_in_city() const;
    virtual std::string get_info() const = 0;

    virtual int add_cargo(int qtd);
    void add_crew_members(int qtd);
    void add_velocity(int v);

    void set_velocity(int v);
    void set_position(std::pair<int, int> pos);
    void set_is_in_city(bool b);
    virtual void reset_velocity() = 0;
    int sell_all_cargo();



    virtual void move() = 0;


};



#endif //CARAVAN_H
