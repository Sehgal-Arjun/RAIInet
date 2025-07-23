#include "../include/polarise.h"
#include "../include/basiclink.h"
#include "../include/link.h"

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
