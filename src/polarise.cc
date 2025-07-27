#include "../include/polarise.h"
#include "../include/basiclink.h"
#include "../include/link.h"

Polarise::Polarise(int id): Ability("Polarise", id) {}

void Polarise::applyAbility(Link& l) {
    // change the LinkType of the link
    if (l.getLinkType() == LinkType::DATA){
        l.setLinkType(LinkType::VIRUS);
    }
    else{
        l.setLinkType(LinkType::DATA);
    }
}

bool Polarise::isValidUse(Link* l) const {
    // polarise only works on data or viruses!
    return (l->getLinkType() == LinkType::DATA || l->getLinkType() == LinkType::VIRUS);
}

// Fix these - they need return statements and proper syntax
void Polarise::applyAbility(Tile& t, Player& p) {
    // Empty implementation
}

void Polarise::applyAbility(Link& l, Player& p) {
    // Empty implementation
}

void Polarise::applyAbility(Link& l1, Link& l2) {
    // Empty implementation
}

void Polarise::applyAbility(Link& l, Player& p, Tile& location) {
    // Empty implementation
}

bool Polarise::isValidUse(Link* l, Player* p) const {
    // Empty implementation
    return false;
}

bool Polarise::isValidUse(Link* l1, Link* l2) const {
    // Empty implementation
    return false;
}

bool Polarise::isValidUse(Tile* t) const {
    // Empty implementation
    return false;
}

bool Polarise::isValidUse(Link* l, Player* p, Tile* location) const {
    // Empty implementation
    return false;
}