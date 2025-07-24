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

pair<int, int> WeakenedLink::getLocation() const {
    return next->getLocation();
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
