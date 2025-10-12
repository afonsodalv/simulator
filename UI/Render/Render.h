//
// Created by afons on 07/10/2025.
//

#ifndef RENDER_H
#define RENDER_H
#include <vector>
#include <string>

class Buffer;


#include "..\\..\\Utils\\HelperView.h"
#include "..\\Buffer\\Buffer.h"

class Render {

    Buffer buf;

public:

    Render(int row, int col);

    void render(std::vector<SimulationMap> map, std::string info);
    void render(const std::string& message) const;
};



#endif //RENDER_H
