#include "../include/boostedlink.h"

using namespace std;

BoostedLink::BoostedLink(Link* next, int boostAmount)
    : LinkDecorator(next), boostAmount(boostAmount) {}

int BoostedLink::getStrength() const {
    return next->getStrength();
}

int BoostedLink::getTravelDistance() const {
    return next->getTravelDistance() + boostAmount;
}

bool BoostedLink::isKnight() const {
    return next->isKnight();
}
