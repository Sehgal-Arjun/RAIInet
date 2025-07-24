#include "../include/weakenedlink.h"

using namespace std;

WeakenedLink::WeakenedLink(Link* next, int debuffAmount)
    : LinkDecorator(next), debuffAmount(debuffAmount) {}

int WeakenedLink::getStrength() const {
    return next->getStrength() - debuffAmount;
}

int WeakenedLink::getTravelDistance() const {
    return next->getTravelDistance();
}

LinkType WeakenedLink::getLinkType() const {
    return next->getLinkType();
}

Player* WeakenedLink::getOwner() const {
    return next->getOwner();
}

bool WeakenedLink::isInUse() const {
    return next->isInUse();
}

bool WeakenedLink::isKnight() const {
    return next->isKnight();
} 

void WeakenedLink::setInUse(bool inUse) {
    next->setInUse(inUse);
}

void WeakenedLink::setLinkType(LinkType t) {
    next->setLinkType(t);
}

Tile* WeakenedLink::getTile() const {
    return next->getTile();
}

void WeakenedLink::setTile(Tile* t){
    next->setTile(t);
}
