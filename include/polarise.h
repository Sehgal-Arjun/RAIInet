#ifndef POLARISE_H
#define POLARISE_H

#include "ability.h"

class Polarise: public LinkAbility {
    public:
        Polarise(int id);
        void apply(Link& l) override;
        bool isValid(Link* l) const override;
};

#endif // POLARISE_H
