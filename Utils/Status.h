//
// Created by afons on 12/10/2025.
//

#ifndef STATUS_H
#define STATUS_H

struct Status {
    bool ok;
    std::string message;
};

struct MoveContext {
    std::vector<std::pair<int,int>>& desert;
    const std::vector<std::pair<int,int>>& cities_pos;
    const std::vector<std::pair<int,int>>& items;
    int row, col;
};


#endif //STATUS_H
