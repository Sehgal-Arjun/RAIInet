#ifndef SCAN_H
#define SCAN_H

#include "ability.h"

class Scan: public Ability {
public:
    Scan(int id);
    // should reveal the link l to the player p
    void applyAbility(Link& l, Player& p) override;
    
    // p is the person who used the scan ability, l should be owned by another player
    bool isValidUse(Link* l, Player* p) const override;

    void applyAbility(Link& l) override;
    void applyAbility(Tile& t, Player& p) override;
    void applyAbility(Link& l1, Link& l2) override;
    void applyAbility(Link& l, Player& p, Tile& location) override;
    bool isValidUse(Link* l) const override;
    bool isValidUse(Link* l1, Link* l2) const override;
    bool isValidUse(Tile* t) const override;
    bool isValidUse(Link* l, Player* p, Tile* location) const override;
};

#endif // SCAN_H 
