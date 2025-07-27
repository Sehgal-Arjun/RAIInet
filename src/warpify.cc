#include "../include/warpify.h"
#include "../include/link.h"
#include "../include/tile.h"
#include <utility>

using namespace std;

Warpify::Warpify(int id): Ability("Warpify", id) {};

void Warpify::applyAbility(Link& l1, Link& l2) {
    Tile* tile1 = l1.getTile();
    Tile* tile2 = l2.getTile();

    // Swap the tiles
    l1.setTile(tile2);
    l2.setTile(tile1);

    // Update occupants
    tile1->setOccupant(&l2);
    tile2->setOccupant(&l1);
}

bool Warpify::isValidUse(Link* l1, Link* l2) const {
    // links must be distinct
    return !((l1->getStrength() == l2->getStrength()) && (l1->getLinkType() == l2->getLinkType()) && (l1->getOwner() == l2->getOwner()));
}


void Warpify::applyAbility(Link& l) {
    // Empty implementation
}

void Warpify::applyAbility(Tile& t, Player& p) {
    // Empty implementation
}

void Warpify::applyAbility(Link& l, Player& p) {
    // Empty implementation
}

void Warpify::applyAbility(Link& l, Player& p, Tile& location) {
    // Empty implementation
}

bool Warpify::isValidUse(Link* l) const {
    // Empty implementation
    return false;
}

bool Warpify::isValidUse(Link* l, Player* p) const {
    // Empty implementation
    return false;
}

bool Warpify::isValidUse(Tile* t) const {
    // Empty implementation
    return false;
}

bool Warpify::isValidUse(Link* l, Player* p, Tile* location) const {
    // Empty implementation
    return false;
}

