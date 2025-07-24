#ifndef LINK_H
#define LINK_H

#include <utility>

class Tile;
class Player;
enum class LinkType;

class Link {
public:
    virtual ~Link() = default;

    virtual int getStrength() const = 0;
    virtual int getTravelDistance() const = 0;
    virtual LinkType getLinkType() const = 0;
    virtual Player* getOwner() const = 0; // non-owning
    virtual bool isInUse() const = 0;
    virtual bool isKnight() const = 0;
    virtual void setInUse(bool inUse) = 0;
    virtual void setLinkType(LinkType t) = 0;
    virtual Tile* getTile() const = 0;
    virtual void setTile(Tile* t) = 0;
};

#endif // LINK_H 
