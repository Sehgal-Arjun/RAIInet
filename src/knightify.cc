#include "../include/knightify.h"
#include "../include/link.h"
#include "../include/player.h"

Knightify::Knightify(int id): Ability("Knightify", id) {};

void Knightify::applyAbility(Link& l) {
    // need to have the owner of l replace it with a KnightedLink!
    l.getOwner()->knightLink(&l);
}

bool Knightify::isValidUse(Link* l) const {
    // there's no limit on which links you can call knightify on!
    return true;
}


void Knightify::applyAbility(Tile& t, Player& p) {
    // Empty implementation
}

void Knightify::applyAbility(Link& l, Player& p) {
    // Empty implementation
}

void Knightify::applyAbility(Link& l1, Link& l2) {
    // Empty implementation
}

void Knightify::applyAbility(Link& l, Player& p, Tile& location) {
    // Empty implementation
}

bool Knightify::isValidUse(Link* l, Player* p) const {
    // Empty implementation
    return false;
}

bool Knightify::isValidUse(Link* l1, Link* l2) const {
    // Empty implementation
    return false;
}

bool Knightify::isValidUse(Tile* t) const {
    // Empty implementation
    return false;
}

bool Knightify::isValidUse(Link* l, Player* p, Tile* location) const {
    // Empty implementation
    return false;
}

