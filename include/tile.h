#ifndef TILE_H
#define TILE_H

#include "link.h"

class Tile {
    bool isBasic, isFirewall, isServerPort;
    Link* occupant;
    std::pair<int, int> location;
    Player* firewallOwner;
    Player* serverPortOwner;

    public:
        Tile() : isBasic{true}, isFirewall{false}, isServerPort{false}, 
                 occupant{nullptr}, location{0, 0}, firewallOwner{nullptr}, 
                 serverPortOwner{nullptr} {}
        virtual ~Tile() = default;

        bool isBasicTile();
        bool isFirewallTile();
        bool isServerPortTile();
        void enableFirewall();
        void enableServerPort();
        void setOccupant(Link* l);
        Link* getOccupant() const;
        std::pair<int, int> getLocation() const;
        void setLocation(std::pair<int, int> location);
        Player* getFirewallOwner() const;
        void setFirewallOwner(Player* p);
        Player* getServerPortOwner() const;
        void setServerPortOwner(Player* p);
};

#endif
