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
    BasicLink(int strength, bool isData, int x, int y, Player* owner) : strength{strength}, 
                                                                        isData{isData}, 
                                                                        location{std::make_pair(x, y)}, 
                                                                        inUse{true}, 
                                                                        owner{owner}, 
                                                                        linkType{isData ? LinkType::DATA : LinkType::VIRUS}, 
                                                                        travelDistance{1} {}

    int getStrength() const override;
    int getTravelDistance() const override;
    LinkType getLinkType() const override;
    std::pair<int, int> getLocation() const override;
    Player* getOwner() const override;
    bool isInUse() const override;
    bool isKnight() const override;
    void setInUse(bool inUse) override;
    void setLocation(std::pair<int, int> loc) override;
    void setLinkType(LinkType t) override;
};

#endif // BASICLINK_H
