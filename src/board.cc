#include "../include/board.h"
#include "../include/tile.h"
#include "../include/player.h"
#include "../include/basiclink.h"
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
#include <random>
#include <map>
#include <string>

using namespace std;

void Board::initialiseBoard(std::istream& in) {
    height = 8;
    width = 8;
    grid.clear();

    for (int r = 0; r < height; ++r) {
        std::vector<std::unique_ptr<Tile>> row;

        for (int c = 0; c < width; ++c) {
            unique_ptr<Tile> tile = make_unique<Tile>();
            row.push_back(tile);
            tile->setLocation(make_pair(r, c));
        }

        grid.push_back(std::move(row));
    }

    grid.at(0).at(width / 2)->enableServerPort();
    grid.at(0).at(width / 2 - 1)->enableServerPort();
    grid.at(height - 1).at(width / 2)->enableServerPort();
    grid.at(height - 1).at(width / 2 - 1)->enableServerPort();    
}

void Board::placeLink(Link& l, Tile* t) {
    t->setOccupant(&l);
    l.setTile(t);
    notifyObservers();
}

void Board::reveal(Link* l, Player& p) {
    Player* owner = l->getOwner();
    std::string label;

    for (const auto& pair : owner->getLinks()) {
        if (pair.second.get() == l) {
            label = pair.first;
            break;
        }
    }

    if (!label.empty()) {
        p.getKnownOpponentLinks()[owner][label] = std::shared_ptr<Link>(l, [](Link*){});
    }

    notifyObservers();
}

std::vector<std::unique_ptr<Link>> Board::randomiseLinks(Player* p) {
    std::vector<int> linkNums = {0, 1, 2, 3, 4, 5, 6, 7};

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(linkNums.begin(), linkNums.end(), g);

    std::vector<std::unique_ptr<Link>> randomisedOrder(8);

    int y = (p->getPlayerId() == 2) ? height - 1 : 0;
    bool isData = true;

    for (int i = 0; i < 8; i++) {
        if (i == 4) isData = false;

        int strength = (i % 4) + 1;

        randomisedOrder[linkNums[i]] = std::make_unique<BasicLink>(strength, isData, i, y, p);
    }
    return randomisedOrder;
}
