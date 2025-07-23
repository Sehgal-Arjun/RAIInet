#ifndef BASICLINK_H
#define BASICLINK_H

#include <utility>

class Player; // Forward declaration

enum class LinkType {
    // Placeholder for actual link types
    DATA,
    VIRUS
};

class BasicLink {
private:
    int strength;
    bool isData;
    std::pair<int, int> location;
    bool inUse;
    Player* owner;
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
};

#endif // BASICLINK_H
