#ifndef LINK_H
#define LINK_H

#include <utility>
#include <string>

class Tile;
class Player;
enum class LinkType;

class Link {
public:
    virtual ~Link() = default;

    virtual char getId() const = 0;
    virtual void setId(char id) = 0;
    virtual int getStrength() const = 0;
    virtual int getTravelDistance() const = 0;
    virtual LinkType getLinkType() const = 0;
    virtual Player* getOwner() const = 0; // non-owning
    virtual void setOwner(Player* p) = 0;
    virtual bool isInUse() const = 0;
    virtual bool isKnight() const = 0;
    virtual void setInUse(bool inUse) = 0;
    virtual void setLinkType(LinkType t) = 0;
    virtual Tile* getTile() const = 0;
    virtual void setTile(Tile* t) = 0;
    std::string makeString();
};

#endif // LINK_H 
