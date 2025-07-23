#ifndef TILE_H
#define TILE_H

#include "link.h"

class Tile {
    bool isBasic, isFirewall, isServerPort;
    Link* occupant;

    public:
        Tile() : isBasic{true}, isFirewall{false}, isServerPort{false} {}
        virtual ~Tile() = default;

        bool isBasicTile();
        bool isFirewallTile();
        bool isServerPortTile();
        void enableFirewall();
        void enableServerPort();
        void setOccupant(Link* l);
};

#endif