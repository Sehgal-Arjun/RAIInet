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
        bool hasLost = false;
        int playerId;

    public:
        ~Player() = default;
        void assignLinks(std::vector<std::unique_ptr<Link>> links);
        void download(Link* l);
        void upload(Link* l, Tile* t);
        void printAbilities(std::ostream& out);
        std::vector<std::unique_ptr<Ability>> getAbilities() const;
        void boostLink(Link* l, int boostAmount);
        void weakenLink(Link* l, int weakenAmount);
        void knightLink(Link*l);
        void reveal(Link* l);
        int getPlayerId() const;
        std::map<std::string, std::unique_ptr<Link>>& getLinks();
        std::unique_ptr<Link> getLink(char link);
        std::map<Player*, std::map<std::string, std::shared_ptr<Link>>>& getKnownOpponentLinks();
        int getDataAmountDownloaded();
        int getVirusAmountDownloaded();
        bool getHasWon();
        bool getHasLost();
        void setHasWon();
        void setHasLost();
};

#endif // PLAYER_H
