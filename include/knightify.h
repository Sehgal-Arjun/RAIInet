#ifndef KNIGHTIFY_H
#define KNIGHTIFY_H

#include "ability.h"

class Knightify : public LinkAbility {
    public:
        Knightify(int id);
        void apply(Link& l) override;
        bool isValid(Link* l) const override;
};

#endif // KNIGHTIFY_H
