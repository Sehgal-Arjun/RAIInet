#ifndef WEAKENLY_H
#define WEAKENLY_H

#include "ability.h"

class Weakenly : public Ability {
public:
    void applyAbility(Link*) override;
    bool isValidUse(Link*) const override;
    AbilityID getID() const override;
};

#endif // WEAKENLY_H 