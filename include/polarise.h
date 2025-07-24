#ifndef POLARISE_H
#define POLARISE_H

#include "ability.h"

class Polarise : public Ability {
public:
    void applyAbility(Link& l) override;
    bool isValidUse(Link* l) const override;
};

#endif // POLARISE_H 
