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
    LinkType getLinkType() const override;
    Player* getOwner() const override;
    bool isInUse() const override;
    bool isKnight() const override;
    void setInUse(bool inUse) override;
    void setLinkType(LinkType t) override;
    Tile* getTile() const override;
    void setTile(Tile* t) override;
};

#endif // WEAKENEDLINK_H 