#include "../include/controller.h"

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

void useAbility(Ability& a, Player& p, Link& l) {

}

void useAbility(Ability& a, Player& p, Tile& t) {

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