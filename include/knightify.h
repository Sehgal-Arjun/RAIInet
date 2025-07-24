#ifndef KNIGHTIFY_H
#define KNIGHTIFY_H

#include "ability.h"

class Knightify: public Ability {
public:
    void applyAbility(Link& l) override;
    bool isValidUse(Link* l) const override;
};

#endif // KNIGHTIFY_H 
