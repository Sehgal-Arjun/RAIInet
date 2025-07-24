#ifndef FIREWALL_H
#define FIREWALL_H

#include "ability.h"
#include "tile.h"

class Firewall: public Ability {
public:
    void applyAbility(Tile& t, Player* p) override;
    
    bool isValidUse(Tile* t) const override;
};

#endif // FIREWALL_H 
