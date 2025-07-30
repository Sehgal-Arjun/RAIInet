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
        Ability(const std::string& name, int id);
        
    public:
        virtual ~Ability() = default;
        
        // interface for all abilities
        int getID() const;
        bool isUsed() const ;
        std::string getName() const;
        void setUsed(bool used);
};

// interfaces grouping abilities by their parameter requirements
class LinkAbility: public Ability {
    public:
        LinkAbility(const std::string& name, int id) : Ability(name, id) {}
        virtual void apply(Link& l) = 0;
        virtual bool isValid(Link* l) const = 0;
};

class LinkPlayerAbility: public Ability {
    public:
        LinkPlayerAbility(const std::string& name, int id) : Ability(name, id) {}
        virtual void apply(Link& l, Player& p) = 0;
        virtual bool isValid(Link* l, Player* p) const = 0;
};

class TilePlayerAbility: public Ability {
    public:
        TilePlayerAbility(const std::string& name, int id) : Ability(name, id) {}
        virtual void apply(Tile& t, Player& p) = 0;
        virtual bool isValid(Tile* t) const = 0;
};

class LinkLinkAbility: public Ability {
    public:
        LinkLinkAbility(const std::string& name, int id) : Ability(name, id) {}
        virtual void apply(Link& l1, Link& l2) = 0;
        virtual bool isValid(Link* l1, Link* l2) const = 0;
};

class LinkPlayerTileAbility: public Ability {
    public:
        LinkPlayerTileAbility(const std::string& name, int id) : Ability(name, id) {}
        virtual void apply(Link& l, Player& p, Tile& t) = 0;
        virtual bool isValid(Link* l, Player* p, Tile* t) const = 0;
};

#endif // ABILITY_H