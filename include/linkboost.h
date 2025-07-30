#ifndef LINKBOOST_H
#define LINKBOOST_H

#include "ability.h"

class LinkBoost: public LinkPlayerAbility {
    public:
        LinkBoost(int id);
        void apply(Link& l, Player& p) override;
        bool isValid(Link* l, Player* p) const override;
};

#endif // LINKBOOST_H
