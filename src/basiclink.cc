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

pair<int, int> BasicLink::getLocation() const {
    return location;
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

void BasicLink::setLocation(std::pair<int, int> loc) {
    this->location = loc;
}
