#include "../include/controller.h"

#include <iostream>

using namespace std;

void Controller::makeMove(Link& l, const std::string& direction, Player& p) {

}

void makeMove(Link& l, const std::string& direction, Player& p, std::string first, std::string second) {

}

bool isValidMove(Link* l, Tile* t, Player* p) {

}

void battle(Link& l1, Link& l2, Tile& t) {

}

bool isMoveIntoOpponentServerPort(Tile* t) {

}

bool isMoveIntoOpponentFirewall(Tile* t) {

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

void switchTurn() {

}