#include "../include/warpify.h"
#include "../include/link.h"
#include "../include/tile.h"
#include <utility>

using namespace std;

Warpify::Warpify(int id): Ability("Warpify", id) {};

void Warpify::applyAbility(Link& l1, Link& l2) {
    // we are sure that l is not owned by p, so we can Warpify it safely
    Tile* tempTile = l1.getTile();
    l2.getTile()->setOccupant(&l1);
    l1.setTile(l2.getTile());
    l1.getTile()->setOccupant(&l2);
    l2.setTile(tempTile);
}

bool Warpify::isValidUse(Link* l1, Link* l2) const {
    // links must be distinct
    return &l1 == &l2;
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

