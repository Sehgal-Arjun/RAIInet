#ifndef KNIGHTEDLINK_H
#define KNIGHTEDLINK_H

#include "linkdecorator.h"

class KnightedLink: public LinkDecorator {
public:
    KnightedLink(Link* next);
    int getStrength() const override;
    int getTravelDistance() const override;
    bool isKnight() const override;
};

#endif // KNIGHTEDLINK_H 