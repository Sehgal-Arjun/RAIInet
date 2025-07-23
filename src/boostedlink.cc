#include "../include/boostedlink.h"

using namespace std;

BoostedLink::BoostedLink(Link* next, int boostAmount)
    : LinkDecorator(next), boostAmount(boostAmount) {}

int BoostedLink::getStrength() const {
    return next->getStrength() + boostAmount;
}

int BoostedLink::getTravelDistance() const {
    return next->getTravelDistance();
}

LinkType BoostedLink::getLinkType() const {
    return next->getLinkType();
}

pair<int, int> BoostedLink::getLocation() const {
    return next->getLocation();
}

Player* BoostedLink::getOwner() const {
    return next->getOwner();
}

bool BoostedLink::isInUse() const {
    return next->isInUse();
}

bool BoostedLink::isKnight() const {
    return next->isKnight();
}

void BoostedLink::setInUse(bool inUse) {
    next->setInUse(inUse);
}

void BoostedLink::setLocation(std::pair<int, int> loc) const {
    next->setLocation(loc);
}

void BoostedLink::setLinkType(LinkType t) const {
    next->setLinkType(t);
} 
