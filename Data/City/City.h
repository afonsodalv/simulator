//
// Created by afons on 08/10/2025.
//

#ifndef CITY_H
#define CITY_H


#include <map>

#include "..\\..\\Utils\\HelperType.h"

class City {

  char id;
  int row;
  int col;
  std::map<CaravanType, int> available_caravans;


public:
    City(char id,int row, int col);

  char get_id() const;
  int get_row() const;
  int get_col() const;

  bool is_caravan_available(CaravanType type);
};


#endif //CITY_H
