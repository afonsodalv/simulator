//
// Created by afons on 07/10/2025.
//

#ifndef RENDER_H
#define RENDER_H
#include <vector>
#include <string>

class Buffer;


#include "..\\..\\Utils\\HelperView.h"

class Render {

public:
    void render(std::vector<SimulationMap> map, std::string info,Buffer& buf) const;
};



#endif //RENDER_H
