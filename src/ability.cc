#include "../include/ability.h"
#include <string>

using namespace std;

Ability::Ability(const std::string& name, int id) : used(false), name(name), id(id) {}

int Ability::getID() const { return id; }

bool Ability::isUsed() const { return used; }

string Ability::getName() const { return name; }

void Ability::applyAbility(Link&, Player&, Tile&) {
    // Default: do nothing
}

void Ability::applyAbility(Tile&, Player&) {
    // Default: do nothing
}

bool Ability::isValidUse(Link*, Player*, Tile*) const {
    // Default: not valid
    return false;
}

void Ability::setUsed(bool used) {
    this->used = used;
}