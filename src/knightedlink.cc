#include "../include/knightedlink.h"

using namespace std;

KnightedLink::KnightedLink(Link* next) : LinkDecorator(next) {}

int KnightedLink::getStrength() const {
    return next->getStrength();
}

int KnightedLink::getTravelDistance() const {
    return next->getTravelDistance();
}

bool KnightedLink::isKnight() const {
    return true;
} 
