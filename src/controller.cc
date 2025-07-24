#include "../include/controller.h"
#include "../include/basiclink.h"

#include <iostream>

using namespace std;

void Controller::makeMove(Link& l, const std::string& direction, Player& p) {
    if (!isValidMove(&l, direction)) {
        return;
        cout << "INVALID MOVE" << endl;
    }

    int row = l.getTile()->getLocation().first;
    int col = l.getTile()->getLocation().second;

    if (direction == "up") {
        row -= l.getTravelDistance();
    }
    else if (direction == "down") {
        row += l.getTravelDistance();
    }
    else if (direction == "left") {
        col -= l.getTravelDistance();
    }
    else if (direction == "right") {
        col += l.getTravelDistance();
    }

    Tile* destination = board->getTileAt(row, col);

    // if moving onto a firewall tile that isn't yours
    if (destination->isFirewallTile() && destination->getFirewallOwner() != &p) {
        // reveal to all players
        for (auto& p : this->players) {
            p->reveal(&l);
        }
        
        // if it's a virus, then download it
        if (l.getLinkType() == LinkType::VIRUS) {
            l.getOwner()->download(&l);
            return;
        }
    }
    
    // if moving onto tile which has a link that isn't yours
    if (destination->getOccupant() != nullptr && destination->getOccupant()->getOwner() != &p) {
        
        // if the battle leads to your link losing (ie, don't need to move it), then return
        if (&battle(l, *destination->getOccupant(), *destination, *l.getTile()) != &l) {
            return;
        }
    }
    
    // if moving onto a server port (and we know it'll be an opponent's server tile)
    else if (destination->isServerPortTile()) {
        destination->getServerPortOwner()->download(&l);
        return;
    }

    // move the tile
    l.getTile()->setOccupant(nullptr);
    l.setTile(destination);
    destination->setOccupant(&l);

    switchTurn();
}

void Controller::makeMove(Link& l, const std::string& directionFirst, const std::string& directionSecond, Player& p) {

}

bool Controller::isValidMove(Link* l, const std::string& direction) {
    if (l->getOwner() != currentTurn) {
        return false;
    }

    int row = l->getTile()->getLocation().first;
    int col = l->getTile()->getLocation().second;

    int height = board->getHeight();
    int width = board->getWidth();

    if (direction == "up") {
        row -= l->getTravelDistance();
    }
    else if (direction == "down") {
        row += l->getTravelDistance();
    }
    else if (direction == "left") {
        col -= l->getTravelDistance();
    }
    else if (direction == "right") {
        col += l->getTravelDistance();
    }
    else {
        return false;
    }

    if (col < 0 || col >= width) {
        return false;
    }

    if (currentTurn->getPlayerId() == 1) {
        if (row < 0) {
            return false;
        }
    }
    else if (currentTurn->getPlayerId() == 2) {
        if (row >= height) {
            return false;
        }
    }

    Tile* destination = board->getTileAt(row, col);
    if (!destination) {
        return false;
    }

    Link* occupant = destination->getOccupant();
    if (occupant && occupant->getOwner() == currentTurn) {
        return false;
    }

    if (destination->isServerPortTile() && destination->getServerPortOwner() == currentTurn) {
        return false;
    }

    return true;
}

bool Controller::isValidMove(Link& l, const std::string& directionFirst, const std::string& directionSecond) {

}

Link& Controller::battle(Link& initiator, Link& victim, Tile& battleTile, Tile& initiatorTile) {
    // reveal both links to all players
    for (auto& p : this->players) {
        p->reveal(&initiator);
        p->reveal(&victim);
    }

    if (initiator.getStrength() == victim.getStrength()){ // links are same strength, initator wins
        initiator.getOwner()->download(&victim);
        return initiator;
    }
    else if (initiator.getStrength() > victim.getStrength()){
        initiator.getOwner()->download(&victim);
        return initiator;
    }
    else{
        victim.getOwner()->download(&initiator);
        return victim;
    }
}

bool Controller::isMoveIntoOpponentServerPort(Tile* t) {
    return (t->isServerPortTile() && t->getServerPortOwner() != currentTurn);
}

bool Controller::isMoveIntoOpponentFirewall(Tile* t) {
    return (t->isFirewallTile() && t->getFirewallOwner() != currentTurn);
}

// useAbility for Download, Scan, Weakenify, and LinkBoost
void Controller::useAbility(Ability& a, Player& p, Link& l) {

    if (a.isValidUse(&l, &p)){
        a.applyAbility(l, p);
    }
    else {
        cout << "INVALID ABILITY: " << a.getName() << endl;
    }
}

// useAbility for Firewall
void Controller::useAbility(Ability& a, Player& p, Tile& t) {
    if (a.isValidUse(&t)){
        a.applyAbility(t, p);
    }
    else{
        cout << "INVALID ABILITY: " << a.getName() << endl;
    }
}

// useAbility for Knightify and Polarise
void Controller::useAbility(Ability& a, Link& l){
    if (a.isValidUse(&l)){
        a.applyAbility(l);
    }
    else{
        cout << "INVALID ABILITY: " << a.getName() << endl;
    }
}

// useAbility for Swapify
void Controller::useAbility(Ability& a, Link& l1, Link& l2){
    if (a.isValidUse(&l1, &l2)){
        a.applyAbility(l1, l2);
    }
    else{
        cout << "INVALID ABILITY: " << a.getName() << endl;
    }
}

// useAbility for Uploadify
void Controller::useAbility(Ability& a, Player& p, Link& l, Tile& t){
    if (a.isValidUse(&l, &p, &t)){
        a.applyAbility(l, p, t);
    }
    else{
        cout << "INVALID ABILITY: " << a.getName() << endl;
    }
}

bool Controller::checkGameWon() {
    for (auto& p : this->players) {
        if (p->getDataAmountDownloaded() == 4) {
            p->setHasWon();
            return true;
        }

        if (p->getVirusAmountDownloaded() == 4) {
            p->setHasLost();
            int remainingPlayers = players.size();

            for (auto& pl : this->players) {
                if (pl->getHasLost()) {
                    remainingPlayers--;
                }
            }

            if (remainingPlayers == 1) {
                for (auto& pl : this->players) {
                    if (!pl->getHasLost()) {
                        pl->setHasWon();
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

void Controller::switchTurn() {
    if (players.at(players.size() - 1) == currentTurn) {
        currentTurn = players.at(0);
    }
    else {
        bool cur = false;
        for (auto& p : players) {
            if (currentTurn == p) {
                cur = true;
                continue;
            }
            
            if (cur) {
                currentTurn = p;
            }
        }
    }
}
