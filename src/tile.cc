#include "../include/tile.h"

using namespace std;

bool Tile::isBasicTile(){ return isBasic; }

bool Tile::isFirewallTile(){ return isFirewall; }

bool Tile::isServerPortTile(){ return isServerPort; }

void Tile::enableFirewall() {
    isBasic = false;
    isFirewall = true;
}

void Tile::enableServerPort() {
    isBasic = false;
    isServerPort = true;
}

void Tile::setOccupant(Link* l){
    occupant = l;
}

Link* Tile::getOccupant() const {
    return occupant;
}

pair<int, int> Tile::getLocation() const {
    return location;
}

void Tile::setLocation(pair<int, int> loc){
    location = loc;
}