#include "../include/weakenify.h"
#include "../include/link.h"
#include "../include/player.h"

void Weakenify::applyAbility(Link& l) {
    // need to have the owner of l (yourself) replace it with a WeakenedLink!
    l.getOwner()->weakenLink(&l, 1);
}

bool Weakenify::isValidUse(Link* l, Player* p) const {
    // can only weaken a link that you don't own!
    return (l->getOwner() != p);
}
