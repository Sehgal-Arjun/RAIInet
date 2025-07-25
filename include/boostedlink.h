#ifndef BOOSTEDLINK_H
#define BOOSTEDLINK_H

#include "linkdecorator.h"

class BoostedLink : public LinkDecorator {
private:
    int boostAmount;
public:
    BoostedLink(Link* next, int boostAmount);
    int getStrength() const override;
    int getTravelDistance() const override;
    bool isKnight() const override;
};

#endif // BOOSTEDLINK_H 
