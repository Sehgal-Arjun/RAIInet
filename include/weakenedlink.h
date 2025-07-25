#ifndef WEAKENEDLINK_H
#define WEAKENEDLINK_H

#include "linkdecorator.h"

class WeakenedLink : public LinkDecorator {
private:
    int debuffAmount;
public:
    WeakenedLink(Link* next, int debuffAmount);
    int getStrength() const override;
    int getTravelDistance() const override;
    bool isKnight() const override;
};

#endif // WEAKENEDLINK_H 