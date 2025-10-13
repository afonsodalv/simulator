//
// Created by afons on 13/10/2025.
//

#ifndef IECONOMY_H
#define IECONOMY_H

class IEconomy {
public:
    virtual ~IEconomy() = default;
    virtual void add_coins(int qtd) = 0;
    virtual int get_coins() const = 0;
};

#endif //IECONOMY_H
