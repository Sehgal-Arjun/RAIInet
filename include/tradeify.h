#ifndef TRADEIFY_H
#define TRADEIFY_H

#include "ability.h"

class Tradeify: public LinkLinkAbility {
    public:
        Tradeify(int id);
        void apply(Link& l1, Link& l2) override;
        bool isValid(Link* l1, Link* l2) const override;
};

#endif // TRADEIFY_H
