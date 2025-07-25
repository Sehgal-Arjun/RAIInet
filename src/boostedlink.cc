#include "../include/boostedlink.h"
#include "../include/basiclink.h"
#include <string>

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

Tile* BoostedLink::getTile() const {
    return next->getTile();
}

void BoostedLink::setTile(Tile* t){
    next->setTile(t);
}

string BoostedLink::makeString(){
    LinkType type = getLinkType();
    string strength = string(1, getStrength());
    if (type == LinkType::DATA){
        return "D" + strength;
    }
    else if (type == LinkType::VIRUS){
        return "V" + strength;
    }
    else {
        return "ERROR";
    }
}
