#ifndef WEAKENIFY_H
#define WEAKENIFY_H

#include "ability.h"

class Weakenify : public Ability {
public:
    void applyAbility(Link*) override;
    bool isValidUse(Link*) const override;
    AbilityID getID() const override;
};

#endif // WEAKENIFY_H 