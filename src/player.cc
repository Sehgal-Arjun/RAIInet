#include "../include/player.h"
#include "../include/link.h"
#include "../include/basiclink.h"
#include "../include/ability.h"
#include "../include/boostedlink.h"
#include "../include/weakenedlink.h"
#include "../include/knightedLink.h"
#include <iostream>
#include <memory>
#include <string>

using namespace std;

void Player::assignLinks(vector<unique_ptr<Link>> ls){
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
        this->links[string(1, key)] = move(link);
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

void Player::printAbilities(ostream& out) {
    for (const auto& ability : chosenAbilities) {
        out << ability->getID() << ". " << ability->getName()
        << " " << (ability->isUsed() ? "(USED)" : "(UNUSED)")
            << '\n';
    }
}

vector<unique_ptr<Ability>> Player::getAbilities() const {
    return this->chosenAbilities;
}

Ability* Player::getAbility(int id) const {
    if (id > 4) { return nullptr; }
    return this->chosenAbilities.at(id).get();
}

void Player::boostLink(Link* l, int boostAmount) {
    for (auto& pair : links) {
        if (pair.second.get() == l) {
            pair.second = make_unique<BoostedLink>(l, boostAmount);
            break;
        }
    }
}

void Player::weakenLink(Link* l, int debuffAmount) {
    for (auto& pair : links) {
        if (pair.second.get() == l) {
            pair.second = make_unique<WeakenedLink>(l, debuffAmount);
            break;
        }
    }
}

void Player::knightLink(Link* l) {
    for (auto& pair : links) {
        if (pair.second.get() == l) {
            pair.second = make_unique<KnightedLink>(l);
            break;
        }
    }
}

void Player::reveal(Link* l){
    if (l->getOwner() != this){ // make sure we're not adding to the map if it's your own link
        if (l->getLinkType() == LinkType::DATA){
            knownOpponentLinks[l->getOwner()]["D" + to_string(l->getStrength())] = shared_ptr<Link>(l);
        }
        else if (l->getLinkType() == LinkType::VIRUS){
            knownOpponentLinks[l->getOwner()]["V" + to_string(l->getStrength())] = shared_ptr<Link>(l);
        }
    }
}

int Player::getPlayerId() const{ return playerId; }

map<string, unique_ptr<Link>>& Player::getLinks() { return links; }

unique_ptr<Link> Player::getLink(char link) {
    if (!((link >= 'a' && link <= 'h') || (link >= 'A' && link <= 'H'))) {
        return nullptr;
    }
    string key = string(1, link);
    auto it = this->links.find(key);
    
    return (it != this->links.end()) ? std::move(it->second) : nullptr;
}

map<Player*, map<string, shared_ptr<Link>>>& Player::getKnownOpponentLinks() {
    return knownOpponentLinks;
}

int Player::getDataAmountDownloaded(){ return dataAmountDownloaded; }

int Player::getVirusAmountDownloaded(){ return dataAmountDownloaded; }

bool Player::getHasWon() { return hasWon; }

bool Player::getHasLost() { return hasLost; }

void Player::setHasWon() { hasWon = true; }

void Player::setHasLost() { hasLost = true; }