#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include <string>
#include "board.h"
#include "player.h"
#include "link.h"
#include "tile.h"
#include "ability.h"

class Controller {
    std::unique_ptr<Board> board;
    std::vector<Player*> players;
    bool useGraphics;
    Player* currentTurn;
    std::pair<int, int> calculateMove(Link* l, std::string direction);
    std::pair<int, int> calculateMove(Link* l, std::string direction1, std::string direction2);

    public:
        Controller() : board(std::make_unique<Board>()) {}
        Controller(std::unique_ptr<Board> b) : board(std::move(b)) {}
        ~Controller() = default;

        void makeMove(Link& l, const std::string& direction, Player& p);
        void makeMove(Link& l, const std::string& directionFirst, const std::string& directionSecond, Player& p);

        void move(std::pair<int, int> location, Link& l, Player& p);

        bool isValidMove(Link* l, const std::string& direction);
        bool isValidMove(Link* l, const std::string& directionFirst, const std::string& directionSecond);

        bool checkValidMove(Link* l, std::pair<int, int> location);

        Link& battle(Link& l1, Link& l2, Tile& battleTile, Tile& initiatorTile);
        bool isMoveIntoOpponentServerPort(Tile* t);
        bool isMoveIntoOpponentFirewall(Tile* t);
        void useAbility(Ability& a, Player& p, Link& l);
        void useAbility(Ability& a, Player& p, Tile& t);
        void useAbility(Ability& a, Link& l);
        void useAbility(Ability& a, Link& l1, Link& l2);
        void useAbility(Ability& a, Player& p, Link& l, Tile& t);
        bool checkGameWon();
        void switchTurn();
};

#endif // CONTROLLER_H