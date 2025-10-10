//
// Created by afons on 07/10/2025.
//

#include "Render.h"
#include "..\\..\\Data\\Simulation\\Simulation.h"
#include "..\\Buffer\\Buffer.h"
#include<vector>
#include<utility>
#include<iostream>

using namespace std;

void Render::render(vector<SimulationMap> map, string info ,Buffer& buf) const  {

    for(const auto& square :  map) {
        buf.move_cursor(square.row, square.col);

        if(square.id)
            buf<<*square.id;
        else
            buf<<view::get_char(square.type);
    }

    buf.print_string(info);
    cout<<buf;

    buf.reset();

}