#include "../include/ability.h"
#include <string>

using namespace std;

int Ability::getID() const { return id; }

bool Ability::isUsed() const { return used; }

string Ability::getName() const { return name; }

// don't need implementations for the other functions here, as they're pure virtual
