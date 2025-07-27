#include "../include/scan.h"
#include "../include/link.h"
#include "../include/player.h"

Scan::Scan(int id): Ability("Scan", id) {};

void Scan::applyAbility(Link& l, Player& p) {
    // we are sure that l is not owned by p, so we can reveal it safely
    p.reveal(&l);
}

bool Scan::isValidUse(Link* l, Player* p) const {
    // can only scan an opponents link!
    return (l->getOwner() != p);
}


void Scan::applyAbility(Link& l) {
    // Empty implementation
}

void Scan::applyAbility(Tile& t, Player& p) {
    // Empty implementation
}

void Scan::applyAbility(Link& l1, Link& l2) {
    // Empty implementation
}

void Scan::applyAbility(Link& l, Player& p, Tile& location) {
    // Empty implementation
}

bool Scan::isValidUse(Link* l) const {
    // Empty implementation
    return false;
}

bool Scan::isValidUse(Link* l1, Link* l2) const {
    // Empty implementation
    return false;
}

bool Scan::isValidUse(Tile* t) const {
    // Empty implementation
    return false;
}

bool Scan::isValidUse(Link* l, Player* p, Tile* location) const {
    // Empty implementation
    return false;
}
