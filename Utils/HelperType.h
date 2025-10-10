//
// Created by afons on 08/10/2025.
//

#ifndef HELPERTYPE_H
#define HELPERTYPE_H

#include <optional>

enum class Type { City, Caravan, Bandit, Item, Storm, Mountain, Desert};

enum class CaravanType  {Builder, Commercial, Military};

struct SimulationMap {
    Type type;
    int row;
    int col;
    std::optional<char> id;
};


#endif //HELPERTYPE_H
