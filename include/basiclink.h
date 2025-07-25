#ifndef BASICLINK_H
#define BASICLINK_H

#include <utility>
#include "link.h"
#include "tile.h"
#include "player.h"

enum class LinkType {
    DATA,
    VIRUS
};

class BasicLink : public Link {
private:
    int strength;
    bool isData;
    bool inUse;
    Player* owner; // non-owning
    LinkType linkType;
    int travelDistance;
    Tile* place;


public:
    BasicLink(int strength, bool isData, Tile* t, Player* owner) : strength{strength}, 
                                                                        isData{isData}, 
                                                                        inUse{true}, 
                                                                        owner{owner}, 
                                                                        linkType{isData ? LinkType::DATA : LinkType::VIRUS}, 
                                                                        travelDistance{1},
                                                                        place{t} {}

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

#endif // BASICLINK_H
