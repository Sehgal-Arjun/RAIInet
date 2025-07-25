#include "../include/player.h"
#include "../include/link.h"
#include "../include/basiclink.h"
#include "../include/ability.h"
#include "../include/boostedlink.h"
#include "../include/weakenedlink.h"
#include "../include/knightedLink.h"
#include <iostream>
#include <string>

using namespace std;

void Player::assignLinks(std::vector<std::unique_ptr<Link>> ls){
    char key;
    if (this->playerId == 1){
        key = 'a';
    }
    else if (this->playerId == 2){
        key = 'A';
    }
    else{
        cout << "ERROR! invalid playerId!" << endl;
        return;
    }

    for (auto& link: ls){
        this->links[string(1, key)] = std::move(link);
        key++;
    }
}

void Player::download(Link* l){
    // 1. mark link as not in use
    l->setInUse(false);
    
    // 2. indicate that the Link isn't on a Tile
    l->getTile()->setOccupant(nullptr);
    l->setTile(nullptr);

    // 3. increment data/virusAmountDownloaded
    if (l->getLinkType() == LinkType::DATA) {
        this->dataAmountDownloaded++;
    }
    else if (l->getLinkType() == LinkType::VIRUS){
        this->virusAmountDownloaded++;
    }
}

void Player::upload(Link* l, Tile* tile){
    // 1. mark link as in use
    l->setInUse(true);
    
    // 2. put the link on the appropriate tile
    l->setTile(tile);

    // 3. decrement data/virusAmountDownloaded
    if (l->getLinkType() == LinkType::DATA) {
        this->dataAmountDownloaded--;
    }
    else if (l->getLinkType() == LinkType::VIRUS){
        this->virusAmountDownloaded--;
    }

    //4. make sure the tile knows it has an occupant
    tile->setOccupant(l);
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
    if (l->getOwner() != this){ // make sure we're not adding to the map if it's your own link
        if (l->getLinkType() == LinkType::DATA){
            knownOpponentLinks[l->getOwner()]["D" + std::to_string(l->getStrength())] = std::shared_ptr<Link>(l);
        }
        else if (l->getLinkType() == LinkType::VIRUS){
            knownOpponentLinks[l->getOwner()]["V" + std::to_string(l->getStrength())] = std::shared_ptr<Link>(l);
        }
    }
}
