#ifndef KNIGHTEDLINK_H
#define KNIGHTEDLINK_H

#include "linkdecorator.h"

class KnightedLink: public LinkDecorator {
public:
    KnightedLink(Link* next);
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
    std::string makeString() override;
};

#endif // KNIGHTEDLINK_H 