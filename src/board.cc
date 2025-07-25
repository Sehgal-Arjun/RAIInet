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

void Board::initialiseBoard(std::istream& in, vector<Player*> players) {
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
    grid.at(0).at(width / 2)->setServerPortOwner(players.at(0));
    grid.at(0).at(width / 2 - 1)->enableServerPort();
    grid.at(0).at(width / 2 - 1)->setServerPortOwner(players.at(0));
    grid.at(height - 1).at(width / 2)->enableServerPort();
    grid.at(height - 1).at(width / 2)->setServerPortOwner(players.at(1));
    grid.at(height - 1).at(width / 2 - 1)->enableServerPort();    
    grid.at(height - 1).at(width / 2 - 1)->setServerPortOwner(players.at(1));

    // for now, only supporting randomised link order
    vector<std::unique_ptr<Link>> linksP1 = randomiseLinks( players.at(0));
    vector<std::unique_ptr<Link>> linksP2 = randomiseLinks( players.at(1));

    for (auto& l: linksP1){
        l->getTile()->setOccupant(l.get());
    }
    for (auto& l: linksP2){
        l->getTile()->setOccupant(l.get());
    }
    players.at(0)->assignLinks(linksP1);
    players.at(1)->assignLinks(linksP2);
}

void Board::placeLink(Link& l, Tile* t) {
    t->setOccupant(&l);
    l.setTile(t);
    auto loc = t->getLocation();
    int change = (l.getLinkType() == LinkType::DATA) ? 2 : 3; // 2: data, 3: virus
    notifyObserversCell(loc.first, loc.second, change);
    notifyObserversFull();
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

    auto loc = l->getTile()->getLocation();
    int change = (l->getLinkType() == LinkType::DATA) ? 2 : 3;
    notifyObserversCell(loc.first, loc.second, change);
    notifyObserversFull();
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

        randomisedOrder[linkNums[i]] = std::make_unique<BasicLink>(strength, isData, getTileAt(i, y), p);
    }
    return randomisedOrder;
}

Tile* Board::getTileAt(int row, int col) const {
    if (row < 0 || row >= height || col < 0 || col >= width) {
        return nullptr;
    }

    return grid[row][col].get();
}
