#ifndef PLAYER_H
#define PLAYER_H

#include <utility>
#include <vector>
#include <map>
#include <string>
#include "link.h"
#include "ability.h"

class Player {
    private:
        std::vector<Ability> chosenAbilities;
        std::map<std::string, Link*> links;
        int dataAmountDownloaded;
        int virusAmountDownloaded;
        std::map<Player*, std::map<std::string, Link*>> knownOpponentLinks;
        bool hasWon;
        int playerId;

    public:
        ~Player() = default;
        void download(Link* l);
        void printAbilities(std::ostream& out);
        std::vector<Ability> getAbilities();
        void boostLink(Link* l);
        void reveal(Link* l);
};

#endif // PLAYER_H
