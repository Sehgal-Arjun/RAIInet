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
        std::vector<std::unique_ptr<Ability>> chosenAbilities;
        std::map<std::string, std::unique_ptr<Link>> links;
        std::map<Player*, std::map<std::string, std::shared_ptr<Link>>> knownOpponentLinks;
        int dataAmountDownloaded = 0;
        int virusAmountDownloaded = 0;
        bool hasWon = false;
        int playerId;

    public:
        ~Player() = default;
        void download(Link* l);
        void printAbilities(std::ostream& out);
        std::vector<Ability> getAbilities();
        void boostLink(Link* l, int boostAmount);
        void weakenLink(Link* l, int weakenAmount);
        void knightLink(Link*l);
        void reveal(Link* l);
        int getPlayerId() { return playerId; }
        const std::vector<std::unique_ptr<Ability>>& getChosenAbilities() const { return chosenAbilities; }
        std::vector<std::unique_ptr<Ability>>& getChosenAbilities() { return chosenAbilities; }
        const std::map<std::string, std::unique_ptr<Link>>& getLinks() const { return links; }
        std::map<std::string, std::unique_ptr<Link>>& getLinks() { return links; }
        const std::map<Player*, std::map<std::string, std::shared_ptr<Link>>>& getKnownOpponentLinks() const { return knownOpponentLinks; }
        std::map<Player*, std::map<std::string, std::shared_ptr<Link>>>& getKnownOpponentLinks() { return knownOpponentLinks; }
};

#endif // PLAYER_H
