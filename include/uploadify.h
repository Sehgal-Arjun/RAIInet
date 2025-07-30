#ifndef UPLOADIFY_H
#define UPLOADIFY_H

#include "ability.h"

class Uploadify: public LinkPlayerTileAbility {
    public:
        Uploadify(int id);
        void apply(Link& l, Player& p, Tile& t) override;
        bool isValid(Link* l, Player* p, Tile* t) const override;
};

#endif // UPLOADIFY_H