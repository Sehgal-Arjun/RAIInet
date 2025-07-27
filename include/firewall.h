#ifndef FIREWALL_H
#define FIREWALL_H

#include "ability.h"
#include "tile.h"

class Firewall: public Ability {
public:
    Firewall(int id);
    void applyAbility(Tile& t, Player& p) override;
    
    bool isValidUse(Tile* t) const override;

    void applyAbility(Link& l) override;
    void applyAbility(Link& l, Player& p) override;
    void applyAbility(Link& l1, Link& l2) override;
    void applyAbility(Link& l, Player& p, Tile& location) override;
    bool isValidUse(Link* l) const override;
    bool isValidUse(Link* l, Player* p) const override;
    bool isValidUse(Link* l1, Link* l2) const override;
    bool isValidUse(Link* l, Player* p, Tile* location) const override;
};

#endif // FIREWALL_H 
