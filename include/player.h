#ifndef PLAYER_H
#define PLAYER_H

#include <utility>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include "link.h"
#include "ability.h"

class Player {
    private:
        std::vector<std::unique_ptr<Ability>> chosenAbilities;
        std::map<std::string, std::unique_ptr<Link>> links;
        std::map<std::string, std::unique_ptr<Link>> downloadedLinks; // Store downloaded links
        std::map<Player*, std::map<std::string, Link*>> knownOpponentLinks;
        std::map<std::string, Link*> originalLinks; // Track original links for display even after download/upload
        int dataAmountDownloaded = 0;
        int virusAmountDownloaded = 0;
        bool hasWon = false;
        bool hasLost = false;
        int playerId;

    public:
        Player(int id) : playerId(id) {}
        ~Player() {}
        void assignLinks(std::vector<std::unique_ptr<Link>>&& links);
        std::unique_ptr<Link> download(Link* l);
        void upload(std::unique_ptr<Link> l, Tile* t);
        void printAbilities(std::ostream& out);
        std::vector<std::unique_ptr<Ability>>& getAbilities();
        Ability* getAbility(int id) const;
        void addAbility(Ability* a);
        void storeDownloadedLink(std::unique_ptr<Link> l);
        void incrementDataDownloaded();
        void incrementVirusDownloaded();
        void boostLink(Link* l, int boostAmount);
        void weakenLink(Link* l, int weakenAmount);
        void knightLink(Link*l);
        void reveal(Link* l);
        int getPlayerId() const;
        std::map<std::string, std::unique_ptr<Link>>& getLinks();
        std::map<std::string, std::unique_ptr<Link>>& getDownloadedLinks();
        Link* getLink(char link);
        std::map<Player*, std::map<std::string, Link*>>& getKnownOpponentLinks();
        std::map<std::string, Link*>& getOriginalLinks();
        int getDataAmountDownloaded();
        int getVirusAmountDownloaded();
        bool getHasWon();
        bool getHasLost();
        void setHasWon();
        void setHasLost();
};

#endif // PLAYER_H
