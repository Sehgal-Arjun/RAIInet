#ifndef LINKDECORATOR_H
#define LINKDECORATOR_H

#include "link.h"

class LinkDecorator : public Link {
protected:
    Link* next;
public:
    explicit LinkDecorator(Link* next);
    virtual ~LinkDecorator() = default;
    char getId() const override;
    void setId(char id) override;
    Player* getOwner() const override;
    void setOwner(Player* p) override;
    bool isInUse() const override;
    void setInUse(bool inUse) override;
    LinkType getLinkType() const override;
    void setLinkType(LinkType t) override;
    Tile* getTile() const override;
    void setTile(Tile* t) override;
};

#endif // LINKDECORATOR_H 