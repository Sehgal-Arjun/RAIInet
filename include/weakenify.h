#ifndef WEAKENIFY_H
#define WEAKENIFY_H

#include "ability.h"

class Weakenify: public LinkPlayerAbility {
    public:
        Weakenify(int id);
        void apply(Link& l, Player& p) override;
        bool isValid(Link* l, Player* p) const override;
};

#endif // WEAKENIFY_H
