#include "../include/linkboost.h"
#include "../include/link.h"
#include "../include/player.h"

LinkBoost::LinkBoost(int id): Ability("LinkBoost", id) {};

void LinkBoost::applyAbility(Link& l) {
    // need to have the owner of l replace it with a BoostedLink!
    l.getOwner()->boostLink(&l, 1);
}

bool LinkBoost::isValidUse(Link* l, Player* p) const {
    // can only boost a link that you own!
    return (l->getOwner() == p);
}


void LinkBoost::applyAbility(Tile& t, Player& p) {
    // Empty implementation
}

void LinkBoost::applyAbility(Link& l, Player& p) {
    // Empty implementation
}

void LinkBoost::applyAbility(Link& l1, Link& l2) {
    // Empty implementation
}

void LinkBoost::applyAbility(Link& l, Player& p, Tile& location) {
    // Empty implementation
}

bool LinkBoost::isValidUse(Link* l) const {
    // Empty implementation
    return false;
}

bool LinkBoost::isValidUse(Link* l1, Link* l2) const {
    // Empty implementation
    return false;
}

bool LinkBoost::isValidUse(Tile* t) const {
    // Empty implementation
    return false;
}

bool LinkBoost::isValidUse(Link* l, Player* p, Tile* location) const {
    // Empty implementation
    return false;
}
