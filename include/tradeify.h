#ifndef TRADEIFY_H
#define TRADEIFY_H

#include "ability.h"

class Tradeify: public Ability {
public:
    Tradeify(int id);
    void applyAbility(Link& l1, Link& l2) override;
    
    // p is the person who used the download ability, l should be owned by another player
    bool isValidUse(Link* l1, Link* l2) const override;

    void applyAbility(Link& l) override;
    void applyAbility(Tile& t, Player& p) override;
    void applyAbility(Link& l, Player& p) override;
    void applyAbility(Link& l, Player& p, Tile& location) override;
    bool isValidUse(Link* l) const override;
    bool isValidUse(Link* l, Player* p) const override;
    bool isValidUse(Tile* t) const override;
    bool isValidUse(Link* l, Player* p, Tile* location) const override;
};

#endif // TRADEIFY_H 
