#include "../include/polarise.h"
#include "../include/basiclink.h"
#include "../include/link.h"

Polarise::Polarise(int id): LinkAbility("Polarise", id) {}

void Polarise::apply(Link& l) {
    // change the LinkType of the link
    if (l.getLinkType() == LinkType::DATA){
        l.setLinkType(LinkType::VIRUS);
    }
    else{
        l.setLinkType(LinkType::DATA);
    }
}

bool Polarise::isValid(Link* l) const {
    // polarise only works on data or viruses!
    return (l->getLinkType() == LinkType::DATA || l->getLinkType() == LinkType::VIRUS);
}
