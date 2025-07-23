#ifndef POLARIZE_H
#define POLARIZE_H

#include "ability.h"

class Polarize : public Ability {
public:
    void applyAbility(Link*) override;
    bool isValidUse(Link*) const override;
    AbilityID getID() const override;
};

#endif // POLARIZE_H 