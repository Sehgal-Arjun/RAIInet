#include "../include/ability.h"
#include <string>

using namespace std;

Ability::Ability(const std::string& name, int id) : used(false), name(name), id(id) {}

int Ability::getID() const { return id; }

bool Ability::isUsed() const { return used; }

string Ability::getName() const { return name; }

void Ability::setUsed(bool used) {
    this->used = used;
}