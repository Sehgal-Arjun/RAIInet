#include "../include/scan.h"
#include "../include/link.h"
#include "../include/player.h"

Scan::Scan(int id): LinkPlayerAbility("Scan", id) {};

void Scan::apply(Link& l, Player& p) {
    // we are sure that l is not owned by p, so we can reveal it safely
    p.reveal(&l);
}

bool Scan::isValid(Link* l, Player* p) const {
    // can only scan an opponents link!
    return (l->getOwner() != p);
}
