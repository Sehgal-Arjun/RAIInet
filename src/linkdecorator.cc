#include "../include/linkdecorator.h"

LinkDecorator::LinkDecorator(Link* next) : next(next) {} 

Player* LinkDecorator::getOwner() const {
    return next->getOwner();
}

bool LinkDecorator::isInUse() const {
    return next->isInUse();
}

void LinkDecorator::setInUse(bool inUse){
    next->setInUse(inUse);
}

void LinkDecorator::setLinkType(LinkType t){
    next->setLinkType(t);
}

LinkType LinkDecorator::getLinkType() const {
    return next->getLinkType();
}

Tile* LinkDecorator::getTile() const {
    return next->getTile();
}

void LinkDecorator::setTile(Tile* t) {
    next->setTile(t);
}
