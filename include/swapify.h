#ifndef SWAPIFY_H
#define SWAPIFY_H

#include "ability.h"

class Swapify: public Ability {
public:
    void applyAbility(Link& l1, Link& l2) override;
    
    // p is the person who used the download ability, l should be owned by another player
    bool isValidUse(Link* l1, Link* l2) const override;
};

#endif // SWAPIFY_H 
