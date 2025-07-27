#ifndef UPLOADIFY_H
#define UPLOADIFY_H

#include "ability.h"
#include "tile.h"

class Uploadify: public Ability {
public:
    Uploadify(int id);
    void applyAbility(Link& l, Player& p, Tile& location) override;

    // p is the player who called uploadify
    bool isValidUse(Link* l, Player* p, Tile* location) const override;


    void applyAbility(Link& l) override;
    void applyAbility(Tile& t, Player& p) override;
    void applyAbility(Link& l, Player& p) override;
    void applyAbility(Link& l1, Link& l2) override;
    bool isValidUse(Link* l) const override;
    bool isValidUse(Link* l, Player* p) const override;
    bool isValidUse(Link* l1, Link* l2) const override;
    bool isValidUse(Tile* t) const override;
};

#endif // UPLOADIFY_H 