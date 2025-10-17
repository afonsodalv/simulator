//
// Created by afons on 09/10/2025.
//

#ifndef CARAVAN_H
#define CARAVAN_H
#include <string>
#include <vector>

#include "..\\..\\Utils\\HelperType.h"
#include "..\\..\\Utils\\Status.h"

class Caravan {

    char id;
    int row;
    int col;
    int speed;
    int crew_members;
    int turns_left;
    bool autonomous_behavior;
    int current_water;
    int current_cargo;
    int max_cargo;
    int max_water;
    int max_crew;
    bool is_in_city;

public:
    virtual ~Caravan() = default;


    Caravan(char id, int row, int col, int speed,int crew_members,int turns_left ,bool autonomous_behavior,int max_water, int max_cargo ,int water, int cargo,int max_crew ,bool is_in_city);


    int get_row() const;
    int get_col() const;

    std::pair<int, int> get_position() const;
    int get_speed() const;
    char get_id() const;
    int get_crew_members() const;
    int get_turns_left() const;
    bool get_autonomous_behavior() const;
    int get_cargo() const;
    int get_current_water() const;
    bool get_is_in_city() const;
    virtual std::string get_info() const = 0;

    virtual int add_cargo(int qtd);
    void add_crew_members(int qtd);
    void add_speed(int v);
    void add_turns_left(int t);
    void decrement_water(int qtd);
    void set_speed(int v);
    void set_position(std::pair<int, int> pos);
    void set_is_in_city(bool b);
    void set_autonomous_behavior(bool ab);
    void set_turns_left(int t);
    virtual void reset_speed() = 0;
    virtual void consume_water() = 0;
    int sell_all_cargo();


    virtual void set_last_direction(std::pair<int, int> ld) {}
    virtual std::pair<int, int> move_autonomous(const std::vector<SimulationMap>&caravans, MoveContext& mc) = 0;
    static int distance_between(std::pair<int,int> a, std::pair<int,int> b, int rows, int cols) ;
    std::pair<int, int> get_closest_target_position(int row, int col,int dist, char target_id,const std::vector<SimulationMap>&target) const;
    std::pair<int, int> get_closest_player_caravan_position(int row, int col, int max_dist,const std::vector<SimulationMap>&targets) const;
    std::pair<int, int> move_random(int max_row, int max_col) const;

};



#endif //CARAVAN_H
