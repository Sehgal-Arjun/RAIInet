#ifndef BOARD_H
#define BOARD_H

#include "tile.h"
#include "player.h"
#include "subject.h"
#include <iostream>
#include <vector>

class Board : public Subject {
    int height, width;
    std::vector<std::vector<std::unique_ptr<Tile>>> grid;

    public:
        void initialiseBoard(std::istream& in, std::vector<Player*> players);
        void placeLink(Link& l, Tile* t);
        void reveal(Link* l, Player& p);
        Tile* getTileAt(int row, int col) const;
        int getHeight() const;
        int getWidth() const;

    private:
        std::vector<std::unique_ptr<Link>> randomiseLinks(Player* p);
};

#endif
