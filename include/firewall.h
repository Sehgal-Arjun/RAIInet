#ifndef FIREWALL_H
#define FIREWALL_H

#include "ability.h"

class Firewall: public TilePlayerAbility {
    public:
        Firewall(int id);
        void apply(Tile& t, Player& p) override;
        bool isValid(Tile* t) const override;
};

#endif // FIREWALL_H
