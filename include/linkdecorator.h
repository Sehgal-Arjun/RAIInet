#ifndef LINKDECORATOR_H
#define LINKDECORATOR_H

#include "link.h"

class LinkDecorator : public Link {
protected:
    Link* next;
public:
    explicit LinkDecorator(Link* next);
    virtual ~LinkDecorator() = default;
    Player* getOwner() const override;
    bool isInUse() const override;
    void setInUse(bool inUse) override;
    LinkType getLinkType() const override;
    void setLinkType(LinkType t) override;
    Tile* getTile() const override;
    void setTile(Tile* t) override;
};

#endif // LINKDECORATOR_H 