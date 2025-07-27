#include "../include/download.h"
#include "../include/link.h"
#include "../include/player.h"
#include "../include/basiclink.h"

Download::Download(int id): Ability("Download", id) {}

void Download::applyAbility(Link& l, Player& p) {
    // we are sure that l is not owned by p, so we can download it safely
    p.download(&l);
}

bool Download::isValidUse(Link* l, Player* p) const {
    // can only download an opponents link!
    return (l->getOwner() != p);
}


void Download::applyAbility(Link& l) {
    // Empty implementation
}

void Download::applyAbility(Tile& t, Player& p) {
    // Empty implementation
}

void Download::applyAbility(Link& l1, Link& l2) {
    // Empty implementation
}

void Download::applyAbility(Link& l, Player& p, Tile& location) {
    // Empty implementation
}

bool Download::isValidUse(Link* l) const {
    // Empty implementation
    return false;
}

bool Download::isValidUse(Link* l1, Link* l2) const {
    // Empty implementation
    return false;
}

bool Download::isValidUse(Tile* t) const {
    // Empty implementation
    return false;
}

bool Download::isValidUse(Link* l, Player* p, Tile* location) const {
    // Empty implementation
    return false;
}
