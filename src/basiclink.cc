#include "../include/basiclink.h"
#include "../include/player.h"

using namespace std;

int BasicLink::getStrength() const {
    return strength;
}

int BasicLink::getTravelDistance() const {
    return travelDistance;
}

LinkType BasicLink::getLinkType() const {
    return linkType;
}

Player* BasicLink::getOwner() const {
    return owner;
}

bool BasicLink::isInUse() const {
    return inUse;
}

bool BasicLink::isKnight() const {
    return false;
} 

void BasicLink::setInUse(bool inUse) {
    this->inUse = inUse;
}

void BasicLink::setLinkType(LinkType t) {
    this->linkType = t;
}

Tile* BasicLink::getTile() const {
    return place;
}

void BasicLink::setTile(Tile* t){
    this->place = t;
}
