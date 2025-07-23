#ifndef TILE_H
#define TILE_H

#include "link.h"

class Tile {
    bool isBasic, isFirewall, isServerPort;
    Link* occupant;

    public:
        bool isBasic();
        bool isFirewall();
        bool isServerPort();
        void enableFirewall();
        void enableServerPort();
};

#endif