#ifndef ABILITY_H
#define ABILITY_H

#include <string>

class Link;
class Player;
class Tile;

class Ability {
protected:
    bool used;
    std::string name;
    int id;
public:
    virtual ~Ability() = default;
    virtual void applyAbility(Link& l) = 0;
    virtual void applyAbility(Tile& t) = 0;
    virtual void applyAbility(Tile& t, Player& p) = 0;
    virtual void applyAbility(Link& l1, Link& l2) = 0;
    virtual bool isValidUse(Link* l) const = 0;
    virtual bool isValidUse(Link* l, Player* p) const = 0;
    virtual bool isValidUse(Link* l1, Link* l2) const = 0;
    virtual bool isValidUse(Tile* t) const = 0;
    int getID() const;
    bool isUsed() const;
    std::string getName() const;
};

#endif // ABILITY_H 