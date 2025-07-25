#include "../include/warpify.h"
#include "../include/link.h"
#include "../include/tile.h"
#include <utility>

using namespace std;

void Warpify::applyAbility(Link& l1, Link& l2) {
    // we are sure that l is not owned by p, so we can download it safely
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
