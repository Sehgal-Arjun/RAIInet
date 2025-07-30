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

void Board::initialise(vector<Player*> players) {
    height = 8;
    width = 8;
    grid.clear();

    for (int r = 0; r < height; ++r) {
        vector<unique_ptr<Tile>> row;

        for (int c = 0; c < width; ++c) {
            unique_ptr<Tile> tile = make_unique<Tile>();
            tile->setLocation(make_pair(r, c));
            row.push_back(move(tile));
        }

        grid.push_back(move(row));
    }

    grid.at(0).at(width / 2)->enableServerPort();
    grid.at(0).at(width / 2)->setServerPortOwner(players.at(0));
    grid.at(0).at(width / 2 - 1)->enableServerPort();
    grid.at(0).at(width / 2 - 1)->setServerPortOwner(players.at(0));
    grid.at(height - 1).at(width / 2)->enableServerPort();
    grid.at(height - 1).at(width / 2)->setServerPortOwner(players.at(1));
    grid.at(height - 1).at(width / 2 - 1)->enableServerPort();    
    grid.at(height - 1).at(width / 2 - 1)->setServerPortOwner(players.at(1));
}

void Board::placeLinkVectors(vector<unique_ptr<Link>>& linksP1, vector<unique_ptr<Link>>& linksP2, vector<Player*> players) {
    for (size_t i = 0; i < grid.at(0).size(); i++){
        int row = 0;
        if (grid.at(0).at(i)->isServerPortTile()){
            row = 1;
        }
        grid.at(row).at(i)->setOccupant(linksP1.at(i).get());
        linksP1.at(i)->setTile(grid.at(row).at(i).get());
    }

    for (size_t i = 0; i < grid.at(height-1).size(); i++){
        int row = height - 1;
        if (grid.at(row).at(i)->isServerPortTile()){
            row = height - 2;
        }
        grid.at(row).at(i)->setOccupant(linksP2.at(i).get());
        linksP2.at(i)->setTile(grid.at(row).at(i).get());
    }

    players.at(0)->assignLinks(move(linksP1));
    players.at(1)->assignLinks(move(linksP2));
}

void Board::initialiseBoard(istream& in, vector<Player*> players) {
    initialise(players);

    vector<unique_ptr<Link>> linksP1 = randomiseLinks(players.at(0));
    vector<unique_ptr<Link>> linksP2 = randomiseLinks(players.at(1));

    placeLinkVectors(linksP1, linksP2, players);
}

void Board::initialiseBoard(istream& in, vector<Player*> players, const vector<string>& link1Order, const vector<string>& link2Order) {
    initialise(players);

    vector<unique_ptr<Link>> linksP1, linksP2;
    
    if (link1Order.empty()) {
        linksP1 = randomiseLinks(players.at(0));
    } else {
        linksP1 = createLinksFromOrder(players.at(0), link1Order);
    }
    
    if (link2Order.empty()) {
        linksP2 = randomiseLinks(players.at(1));
    } else {
        linksP2 = createLinksFromOrder(players.at(1), link2Order);
    }

    placeLinkVectors(linksP1, linksP2, players);
}

void Board::reveal(Link* l, Player& p) {
    Player* owner = l->getOwner();
    string label;
    const unique_ptr<Link>* linkPtr = nullptr;

    for (const auto& pair : owner->getLinks()) {
        if (pair.second.get() == l) {
            label = pair.first;
            linkPtr = &pair.second;
            break;
        }
    }

    if (!label.empty() && linkPtr) {
        p.getKnownOpponentLinks()[owner][label] = linkPtr->get();
    }

    if (l->getTile() != nullptr) {
        notifyObserversFull();
    }
}

vector<unique_ptr<Link>> Board::randomiseLinks(Player* p) {
    vector<int> linkNums = {0, 1, 2, 3, 4, 5, 6, 7};

    random_device rd;
    mt19937 g(rd());
    shuffle(linkNums.begin(), linkNums.end(), g);

    vector<unique_ptr<Link>> randomisedOrder(8);

    int y = (p->getPlayerId() == 2) ? height - 1 : 0;
    bool isData = true;

    for (int i = 0; i < 8; i++) {
        if (i == 4) isData = false;

        int strength = (i % 4) + 1;

        randomisedOrder[linkNums[i]] = make_unique<BasicLink>(strength, isData, getTileAt(y, i), p);
    }
    return randomisedOrder;
}

vector<unique_ptr<Link>> Board::createLinksFromOrder(Player* p, const vector<string>& linkOrder) {
    vector<unique_ptr<Link>> orderedLinks(8);
    
    int y = (p->getPlayerId() == 2) ? height - 1 : 0;
    
    for (int i = 0; i < 8; i++) {
        string linkSpec = linkOrder[i];
        if (linkSpec.length() != 2) {
            throw invalid_argument("Invalid link specification: " + linkSpec);
        }
        
        char type = linkSpec[0];
        int strength = linkSpec[1] - '0';
        
        if ((type != 'V' && type != 'D') || strength < 1 || strength > 4) {
            throw invalid_argument("Invalid link specification: " + linkSpec);
        }
        
        bool isData = (type == 'D');
        orderedLinks[i] = make_unique<BasicLink>(strength, isData, getTileAt(y, i), p);
    }
    
    return orderedLinks;
}

Tile* Board::getTileAt(int row, int col) const {
    if (row < 0 || row >= height || col < 0 || col >= width) {
        return nullptr;
    }

    return grid[row][col].get();
}

int Board::getHeight() const {
    return height;
}

int Board::getWidth() const {
    return width;
}
