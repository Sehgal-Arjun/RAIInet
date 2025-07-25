#ifndef WARPIFY_H
#define WARPIFY_H

#include "ability.h"

class Warpify: public Ability {
public:
    void applyAbility(Link& l1, Link& l2) override;
    
    // p is the person who used the download ability, l should be owned by another player
    bool isValidUse(Link* l1, Link* l2) const override;
};

#endif // WARPIFY_H 
