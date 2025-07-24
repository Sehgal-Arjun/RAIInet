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

pair<int, int> KnightedLink::getLocation() const {
    return next->getLocation();
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
