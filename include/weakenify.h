#ifndef WEAKENIFY_H
#define WEAKENIFY_H

#include "ability.h"

class Weakenify: public Ability {
public:
    Weakenify(int id);
    void applyAbility(Link& l) override;
    bool isValidUse(Link* l, Player* p) const override;

    void applyAbility(Tile& t, Player& p) override;
    void applyAbility(Link& l, Player& p) override;
    void applyAbility(Link& l1, Link& l2) override;
    void applyAbility(Link& l, Player& p, Tile& location) override;
    bool isValidUse(Link* l) const override;
    bool isValidUse(Link* l1, Link* l2) const override;
    bool isValidUse(Tile* t) const override;
    bool isValidUse(Link* l, Player* p, Tile* location) const override;
};

#endif // WEAKENIFY_H
