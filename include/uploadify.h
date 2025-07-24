#ifndef UPLOADIFY_H
#define UPLOADIFY_H

#include "ability.h"
#include "tile.h"

class Uploadify: public Ability {
public:
    void applyAbility(Link& l, Player& p, Tile& location) override;

    // p is the player who called uploadify
    bool isValidUse(Link* l, Player* p, Tile& location) const override;
};

#endif // UPLOADIFY_H 