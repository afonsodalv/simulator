//
// Created by afons on 07/10/2025.
//

#include "Render.h"
#include<vector>
#include<iostream>

using namespace std;


Render::Render(int row, int col): buf(row, col) {}

void Render::render(vector<SimulationMap> map, string info)  {

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

void Render::render(const std::string& message) const {
    buf.print_string(message);
}