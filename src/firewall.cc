#include "../include/firewall.h"
#include "../include/tile.h"

Firewall::Firewall(int id): Ability("Firewall", id) {};

void Firewall::applyAbility(Tile& t, Player& p) {
    // we're sure that the tile is empty, so we can turn it into a firewall
    t.enableFirewall();
    t.setFirewallOwner(&p);
}

bool Firewall::isValidUse(Tile* t) const {
    // tile needs to be empty to put a firewall on it!
    return (t->isBasicTile() && t->getOccupant() == nullptr);
}


void Firewall::applyAbility(Link& l) {
    // Empty implementation
}

void Firewall::applyAbility(Link& l, Player& p) {
    // Empty implementation
}

void Firewall::applyAbility(Link& l1, Link& l2) {
    // Empty implementation
}

void Firewall::applyAbility(Link& l, Player& p, Tile& location) {
    // Empty implementation
}

bool Firewall::isValidUse(Link* l) const {
    // Empty implementation
    return false;
}

bool Firewall::isValidUse(Link* l, Player* p) const {
    // Empty implementation
    return false;
}

bool Firewall::isValidUse(Link* l1, Link* l2) const {
    // Empty implementation
    return false;
}

bool Firewall::isValidUse(Link* l, Player* p, Tile* location) const {
    // Empty implementation
    return false;
}
