#include "../include/swapify.h"
#include "../include/link.h"
#include "../include/tile.h"
#include <utility>

using namespace std;

void Swapify::applyAbility(Link& l1, Link& l2) {
    // we are sure that l is not owned by p, so we can download it safely
    pair<int, int> tempLoc = l1.getLocation();
    Tile* tempTile = l1.getTile();

    l1.setLocation(l2.getLocation());
    l1.setTile(l2.getTile());

    l2.setLocation(tempLoc);
    l2.setTile(tempTile);
}

bool Swapify::isValidUse(Link* l1, Link* l2) const {
    // links must be distinct
    return &l1 == &l2;
}
