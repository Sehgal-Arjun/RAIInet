#include "../include/player.h"
#include "../include/link.h"
#include "../include/basiclink.h"
#include "../include/ability.h"
#include "../include/boostedlink.h"
#include "../include/weakenedlink.h"
#include "../include/knightedLink.h"
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
        out << ability->getID() << ". " << ability->getName()
        << " " << (ability->isUsed() ? "(USED)" : "(UNUSED)")
            << '\n';
    }
}

void Player::boostLink(Link* l, int boostAmount) {
    for (auto& pair : links) {
        if (pair.second.get() == l) {
            pair.second = std::make_unique<BoostedLink>(l, boostAmount);
            break;
        }
    }
}

void Player::weakenLink(Link* l, int debuffAmount) {
    for (auto& pair : links) {
        if (pair.second.get() == l) {
            pair.second = std::make_unique<WeakenedLink>(l, debuffAmount);
            break;
        }
    }
}

void Player::knightLink(Link* l) {
    for (auto& pair : links) {
        if (pair.second.get() == l) {
            pair.second = std::make_unique<KnightedLink>(l);
            break;
        }
    }
}

void Player::reveal(Link* l){
    if (l->getLinkType() == LinkType::DATA){
        knownOpponentLinks[l->getOwner()]["D" + std::to_string(l->getStrength())] = std::shared_ptr<Link>(l);
    }
    else if (l->getLinkType() == LinkType::VIRUS){
        knownOpponentLinks[l->getOwner()]["V" + std::to_string(l->getStrength())] = std::shared_ptr<Link>(l);
    }
}
