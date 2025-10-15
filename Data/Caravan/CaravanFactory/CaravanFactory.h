//
// Created by afons on 09/10/2025.
//

#ifndef CARAVANFACTORY_H
#define CARAVANFACTORY_H

#include <memory>
#include "..\\Caravan.h"
#include "..\\..\\..\\Utils\\HelperType.h"

class CaravanFactory {

public:
    static std::unique_ptr<Caravan> createCaravan(CaravanType type, int row, int col,int bandits_duration);

};



#endif //CARAVANFACTORY_H
