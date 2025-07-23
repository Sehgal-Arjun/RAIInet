#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include "ability.h"

class Download : public Ability {
public:
    void applyAbility(Link& l, Player& p) override;
    
    // p is the person who used the download ability, l should be owned by another player
    bool isValidUse(Link* l, Player* p) const override;
};

#endif // DOWNLOAD_H 
