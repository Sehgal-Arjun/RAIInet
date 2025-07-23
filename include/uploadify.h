#ifndef UPLOADIFY_H
#define UPLOADIFY_H

#include "ability.h"

class Uploadify : public Ability {
public:
    void applyAbility(Link*) override;
    bool isValidUse(Link*) const override;
    AbilityID getID() const override;
};

#endif // UPLOADIFY_H 