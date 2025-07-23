#ifndef BASICLINK_H
#define BASICLINK_H

#include <utility>
#include "link.h"

class Player;

enum class LinkType {
    DATA,
    VIRUS
};

class BasicLink : public Link {
private:
    int strength;
    bool isData;
    std::pair<int, int> location;
    bool inUse;
    Player* owner; // non-owning
    LinkType linkType;
    int travelDistance;

public:
    int getStrength() const;
    int getTravelDistance() const;
    LinkType getLinkType() const;
    std::pair<int, int> getLocation() const;
    Player* getOwner() const;
    bool isInUse() const;
    bool isKnight() const;
    void setInUse(bool inUse);
    void setLocation(std::pair<int, int> loc);
    void setLinkType(LinkType t) = 0;
};

#endif // BASICLINK_H
