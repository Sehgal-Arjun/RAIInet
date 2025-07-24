#include "../include/uploadify.h"
#include "../include/link.h"
#include "../include/player.h"
#include "../include/tile.h"

using namespace std;

void Uploadify::applyAbility(Link& l, Player& p, Tile& location) {
    // we're sure that l's owner is the caller of uploadify, so we can safely upload the Link
    p.upload(&l, location.getLocation());
}

bool Uploadify::isValidUse(Link* l, Player* p, Tile* location) const {
    // location that is being uploaded to is empty, can only upload your own link, and cannot upload to a server tile!
    return (l->getOwner() == p && location->getOccupant() == nullptr && !location->isServerPortTile());
}
