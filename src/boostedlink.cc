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

void BoostedLink::setLinkType(LinkType t) {
    next->setLinkType(t);
} 
