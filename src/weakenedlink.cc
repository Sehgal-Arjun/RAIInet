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

bool WeakenedLink::isKnight() const {
    return next->isKnight();
} 
