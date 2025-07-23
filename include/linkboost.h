#ifndef LINKBOOST_H
#define LINKBOOST_H

#include "ability.h"

class LinkBoost : public Ability {
public:
    void applyAbility(Link& l) override;
    bool isValidUse(Link* l, Player* p) const override;
};

#endif // LINKBOOST_H 
