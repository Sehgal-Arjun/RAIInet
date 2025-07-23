#ifndef KNIGHTEDLINK_H
#define KNIGHTEDLINK_H

#include "linkdecorator.h"

class KnightedLink : public LinkDecorator {
public:
    KnightedLink(Link* next);
    int getStrength() const override;
    int getTravelDistance() const override;
    LinkType getLinkType() const override;
    std::pair<int, int> getLocation() const override;
    Player* getOwner() const override;
    bool isInUse() const override;
    bool isKnight() const override;
};

#endif // KNIGHTEDLINK_H 