#ifndef WEAKENIFY_H
#define WEAKENIFY_H

#include "ability.h"

class Weakenify: public Ability {
public:
    void applyAbility(Link& l) override;
    bool isValidUse(Link* l, Player* p) const override;
};

#endif // WEAKENIFY_H
