#include "../include/knightify.h"
#include "../include/link.h"
#include "../include/player.h"

void Knightify::applyAbility(Link& l) {
    // need to have the owner of l replace it with a KnightedLink!
    l.getOwner()->knightLink(&l);
}

bool Knightify::isValidUse(Link* l) const {
    // there's no limit on which links you can call knightify on!
    return true;
}
