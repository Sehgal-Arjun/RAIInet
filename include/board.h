#ifndef BOARD_H
#define BOARD_H

#include "tile.h"
#include "player.h"
#include <iostream>
#include <vector>

class Board {
    int height, width;
    std::vector<std::vector<Tile&>> grid;

    public:
        void initialiseBoard(std::istream& in);
        void placeLink(Link& l, Tile& t);
        void reveal(Link* l, Player& p);
        std::vector<std::vector<Tile&>> getBoard();

    private:
        void randomiseLinks();
};

#endif