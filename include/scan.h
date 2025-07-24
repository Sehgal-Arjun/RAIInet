#ifndef SCAN_H
#define SCAN_H

#include "ability.h"

class Scan: public Ability {
public:
    // should reveal the link l to the player p
    void applyAbility(Link& l, Player& p) override;
    
    // p is the person who used the scan ability, l should be owned by another player
    bool isValidUse(Link* l, Player* p) const override;
};

#endif // SCAN_H 
