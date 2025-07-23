#include "../include/linkboost.h"
#include "../include/link.h"
#include "../include/player.h"

void LinkBoost::applyAbility(Link& l) {
    // need to have the owner of l replace it with a BoostedLink!
    l.getOwner()->boostLink(&l);
}

bool LinkBoost::isValidUse(Link* l, Player* p) const {
    // can only boost a link that you own!
    return (l->getOwner() == p);
}
