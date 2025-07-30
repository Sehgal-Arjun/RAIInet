#include "../include/linkboost.h"
#include "../include/link.h"
#include "../include/player.h"

using namespace std;

LinkBoost::LinkBoost(int id): LinkPlayerAbility("LinkBoost", id) {};

void LinkBoost::apply(Link& l, Player& p) {
    // need to have the owner of l replace it with a BoostedLink!
    l.getOwner()->boostLink(&l, 1);
}

bool LinkBoost::isValid(Link* l, Player* p) const {
    // can only boost a link that you own!
    return (l->getOwner() == p);
}

