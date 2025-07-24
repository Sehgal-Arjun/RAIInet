#include "../include/firewall.h"
#include "../include/tile.h"

void Firewall::applyAbility(Tile& t, Player* p) {
    // we're sure that the tile is empty, so we can turn it into a firewall
    t.enableFirewall();
    t.setFirewallOwner(p);
}

bool Firewall::isValidUse(Tile* t) const {
    // tile needs to be empty to put a firewall on it!
    return (t->isBasicTile() && t->getOccupant() == nullptr);
}
