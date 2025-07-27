#include "../include/weakenify.h"
#include "../include/link.h"
#include "../include/player.h"

using namespace std;

Weakenify::Weakenify(int id): Ability("Weakenify", id) {};

void Weakenify::applyAbility(Link& l, Player& p) {
    // need to have the owner of l (yourself) replace it with a WeakenedLink!
    l.getOwner()->weakenLink(&l, 1);
}

bool Weakenify::isValidUse(Link* l, Player* p) const {
    // can only weaken a link that you don't own!
    return (l->getOwner() != p);
}


void Weakenify::applyAbility(Tile& t, Player& p) {
    // Empty implementation
}

void Weakenify::applyAbility(Link& l) {
    // Empty implementation
}

void Weakenify::applyAbility(Link& l1, Link& l2) {
    // Empty implementation
}

void Weakenify::applyAbility(Link& l, Player& p, Tile& location) {
    // Empty implementation
}

bool Weakenify::isValidUse(Link* l) const {
    // Empty implementation
    return false;
}

bool Weakenify::isValidUse(Link* l1, Link* l2) const {
    // Empty implementation
    return false;
}

bool Weakenify::isValidUse(Tile* t) const {
    // Empty implementation
    return false;
}

bool Weakenify::isValidUse(Link* l, Player* p, Tile* location) const {
    // Empty implementation
    return false;
}
