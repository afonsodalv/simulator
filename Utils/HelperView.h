//
// Created by afons on 08/10/2025.
//

#ifndef HELPERVIEW_H
#define HELPERVIEW_H

#include "HelperType.h"


namespace view {
    inline char get_char(Type type) {
        switch (type) {
            case Type::Mountain: return '+';
            case Type::Desert: return '.';
            case Type::Item:        return '?';
            case Type::Storm:       return '~';
            default:                      return '.';
        }
    }
}


#endif //HELPERVIEW_H
