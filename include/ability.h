#ifndef ABILITY_H
#define ABILITY_H

#include <string>

class Link;
class Player;
class Tile;

enum class AbilityID {
    POLARIZE,
    WEAKENIFY,
    LINKBOOST,
    UPLOADIFY,
    SWAPIFY,
    KNIGHTIFY,
    SCAN,
    DOWNLOAD,
    FIREWALL
};

class Ability {
protected:
    bool used;
    std::string name;
public:
    virtual ~Ability() = default;
    virtual void applyAbility(Link*) = 0;
    virtual void applyAbility(Link*, Player*) = 0;
    virtual void applyAbility(Link*, Tile*) = 0;
    virtual void applyAbility(Link*, Link*) = 0;
    virtual bool isValidUse(Link*) const = 0;
    virtual bool isValidUse(Link*, Player*) const = 0;
    virtual bool isValidUse(Link*, Tile*) const = 0;
    virtual bool isValidUse(Link*, Link*) const = 0;
    virtual AbilityID getID();
};

#endif // ABILITY_H 