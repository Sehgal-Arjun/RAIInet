#ifndef BOARD_H
#define BOARD_H

#include "tile.h"
#include "player.h"
#include "subject.h"
#include <iostream>
#include <vector>
#include <memory>

class Board : public Subject {
    int height, width;
    std::vector<std::vector<std::unique_ptr<Tile>>> grid;

    public:
        ~Board() {}
        void initialise(std::vector<Player*> players);
        void initialiseBoard(std::istream& in, std::vector<Player*> players);
        void initialiseBoard(std::istream& in, std::vector<Player*> players, const std::vector<std::string>& link1Order, const std::vector<std::string>& link2Order);
        void placeLink(Link& l, Tile* t);
        void reveal(Link* l, Player& p);
        Tile* getTileAt(int row, int col) const;
        int getHeight() const;
        int getWidth() const;

    private:
        void placeLinkVectors(std::vector<std::unique_ptr<Link>>& linksP1, std::vector<std::unique_ptr<Link>>& linksP2, std::vector<Player*> players);
        std::vector<std::unique_ptr<Link>> randomiseLinks(Player* p);
        std::vector<std::unique_ptr<Link>> createLinksFromOrder(Player* p, const std::vector<std::string>& linkOrder);
};

#endif
