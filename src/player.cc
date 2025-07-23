#include "../include/player.h"
#include "../include/link.h"
#include "../include/basiclink.h"
#include "../include/ability.h"
#include "../include/boostedlink.h"
#include <iostream>

using namespace std;

void Player::download(Link* l){
    // 1. mark link as not in use
    l->setInUse(false);
    
    // 2. move link to (-1, -1)
    l->setLocation(make_pair(-1, -1));

    // 3. increment data/virusAmountDownloaded
    if (l->getLinkType() == LinkType::DATA) {
        this->dataAmountDownloaded++;
    }
    else if (l->getLinkType() == LinkType::VIRUS){
        this->virusAmountDownloaded++;
    }
}

void Player::printAbilities(std::ostream& out) {
    for (const auto& ability : chosenAbilities) {
        out << ability.getID() << ". " << ability.getName()
        << " " << (ability.isUsed() ? "(USED)" : "(UNUSED)")
            << '\n';
    }
}

vector<Ability> Player::getAbilities(){ return chosenAbilities; }

void Player::boostLink(Link* l) {
    for (auto& pair : links) {
        if (pair.second == l) {
            pair.second = new BoostedLink(l, 1);
            break;
        }
    }
}
