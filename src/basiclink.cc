#include "basiclink.h"
#include "player.h"

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

void setInUse(bool inUse) const {
    this->inUse = inUse;
}

void setLocation(std::pair<int, int> loc) const {
    this->location = loc;
}
