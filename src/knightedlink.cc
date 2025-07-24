#include "../include/knightedlink.h"

using namespace std;

KnightedLink::KnightedLink(Link* next) : LinkDecorator(next) {}

int KnightedLink::getStrength() const {
    return next->getStrength();
}

int KnightedLink::getTravelDistance() const {
    return next->getTravelDistance();
}

LinkType KnightedLink::getLinkType() const {
    return next->getLinkType();
}

Player* KnightedLink::getOwner() const {
    return next->getOwner();
}

bool KnightedLink::isInUse() const {
    return next->isInUse();
}

bool KnightedLink::isKnight() const {
    return true;
} 

void KnightedLink::setInUse(bool inUse) {
    next->setInUse(inUse);
}

void KnightedLink::setLinkType(LinkType t) {
    next->setLinkType(t);
} 

Tile* KnightedLink::getTile() const {
    return next->getTile();
}

void KnightedLink::setTile(Tile* t){
    next->setTile(t);
}
