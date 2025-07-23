#include "../include/download.h"
#include "../include/link.h"
#include "../include/player.h"

void Download::applyAbility(Link& l, Player& p) {
    // we are sure that l is not owned by p, so we can download it safely
    p.download(&l);
}

bool Download::isValidUse(Link* l, Player* p) const {
    // can only download an opponents link!
    return (l->getOwner() != p);
}
