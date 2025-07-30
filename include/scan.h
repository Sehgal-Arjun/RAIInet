#ifndef SCAN_H
#define SCAN_H

#include "ability.h"

class Scan: public LinkPlayerAbility {
    public:
        Scan(int id);
        void apply(Link& l, Player& p) override;
        bool isValid(Link* l, Player* p) const override;
};

#endif // SCAN_H
