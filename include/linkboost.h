#ifndef LINKBOOST_H
#define LINKBOOST_H

#include "ability.h"

class LinkBoost : public Ability {
public:
    void applyAbility(Link*) override;
    bool isValidUse(Link*) const override;
    AbilityID getID() const override;
};

#endif // LINKBOOST_H 