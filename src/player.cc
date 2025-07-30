#include "../include/player.h"
#include "../include/link.h"
#include "../include/basiclink.h"
#include "../include/ability.h"
#include "../include/boostedlink.h"
#include "../include/weakenedlink.h"
#include "../include/knightedlink.h"
#include <iostream>
#include <memory>
#include <string>

using namespace std;

void Player::assignLinks(std::vector<std::unique_ptr<Link>>&& ls){
    char key;
    if (this->playerId == 1){
        key = 'a';
    }
    else if (this->playerId == 2){
        key = 'A';
    }
    else{
        cerr << "Error: Invalid playerId" << endl;
        return;
    }

    for (auto& link: ls){
        link->setId(key);
        this->links[string(1, key)] = std::move(link);
        this->originalLinks[string(1, key)] = this->links[string(1, key)].get();
        key++;
    }
}

unique_ptr<Link> Player::download(Link* l){
    // mark link as not in use
    l->setInUse(false);
    
    // indicate that the Link isn't on a Tile
    if (l->getTile() != nullptr) {
        l->getTile()->setOccupant(nullptr);
        l->setTile(nullptr);
    }


    // remove the link from the player's vector of links and return it
    string key = string(1, l->getId());
    auto linkPtr = move(links[key]);
    links.erase(key);
    return linkPtr;
}

void Player::upload(unique_ptr<Link> l, Tile* tile){
    // mark link as in use
    l->setInUse(true);
    
    // put the link on the appropriate tile
    l->setTile(tile);

    // decrement data/virusAmountDownloaded
    if (l->getLinkType() == LinkType::DATA) {
        this->dataAmountDownloaded--;
    }
    else if (l->getLinkType() == LinkType::VIRUS){
        this->virusAmountDownloaded--;
    }

    // make sure the tile knows it has an occupant
    tile->setOccupant(l.get());

    // add the link to the player's active links map (move from downloaded to active)
    links[string(1, l->getId())] = std::move(l);
}

void Player::printAbilities(ostream& out) {
    for (const auto& ability : chosenAbilities) {
        out << ability->getID() << ". " << ability->getName()
        << " " << (ability->isUsed() ? "(USED)" : "(UNUSED)")
            << '\n';
    }
}

std::vector<std::unique_ptr<Ability>>& Player::getAbilities() {
    return this->chosenAbilities;
}

Ability* Player::getAbility(int id) const {
    if (id > 4) { return nullptr; }
    return this->chosenAbilities.at(id).get();
}

void Player::addAbility(Ability* a){
    this->chosenAbilities.push_back(unique_ptr<Ability>(a));
}

void Player::storeDownloadedLink(unique_ptr<Link> l) {
    string key = string(1, l->getId());
    downloadedLinks[key] = std::move(l);
}

void Player::incrementDataDownloaded() {
    this->dataAmountDownloaded++;
}

void Player::incrementVirusDownloaded() {
    this->virusAmountDownloaded++;
}

void Player::boostLink(Link* l, int boostAmount) {
    for (auto& pair : links) {
        if (pair.second.get() == l) {
            // store the tile that the link is currently on
            Tile* currentTile = l->getTile();
            
            // release it so we can make a new one that's boosted
            auto releasedLink = pair.second.release();
            pair.second = make_unique<BoostedLink>(releasedLink, boostAmount);
            
            // update the tile's occupant to point to the new decorator
            if (currentTile) {
                currentTile->setOccupant(pair.second.get());
            }
            break;
        }
    }
}

void Player::weakenLink(Link* l, int weakenAmount) {
    for (auto& pair: links) {
        if (pair.second.get() == l) {
            // store the tile that the link is currently on
            Tile* currentTile = l->getTile();
            
            // release it so we can make a new one that's weakened
            auto releasedLink = pair.second.release();
            pair.second = make_unique<WeakenedLink>(releasedLink, weakenAmount);
            
            // update the tile's occupant to point to the new decorator
            if (currentTile) {
                currentTile->setOccupant(pair.second.get());
            }
            break;
        }
    }
}

void Player::knightLink(Link* l) {
    for (auto& pair : links) {
        if (pair.second.get() == l) {
            // store the tile that the link is currently on
            Tile* currentTile = l->getTile();
            
            // release it so we can make a new one that's knighted
            auto releasedLink = pair.second.release();
            pair.second = make_unique<KnightedLink>(releasedLink);
            
            // update the tile's occupant to point to the new decorator
            if (currentTile) {
                currentTile->setOccupant(pair.second.get());
            }
            break;
        }
    }
}

void Player::reveal(Link* l){
    if (l->getOwner() != this){ // make sure we're not adding to the map if it's your own link
        for (const auto& pair : l->getOwner()->getLinks()) {
            if (pair.second.get() == l) {
                knownOpponentLinks[l->getOwner()][pair.first] = pair.second.get();
                break;
            }
        }
    }
}

int Player::getPlayerId() const{ return playerId; }

map<string, unique_ptr<Link>>& Player::getLinks() { return links; }

map<string, unique_ptr<Link>>& Player::getDownloadedLinks() { return downloadedLinks; }

Link* Player::getLink(char link) {
    if (!((link >= 'a' && link <= 'h') || (link >= 'A' && link <= 'H'))) {
        return nullptr;
    }
    string key = string(1, link);
    
    // First check active links
    auto it = this->links.find(key);
    if (it != this->links.end()) {
        return it->second.get();
    }
    
    // Then check downloaded links
    auto downloadedIt = this->downloadedLinks.find(key);
    if (downloadedIt != this->downloadedLinks.end()) {
        return downloadedIt->second.get();
    }
    
    return nullptr;
}

map<Player*, map<string, Link*>>& Player::getKnownOpponentLinks() {
    return knownOpponentLinks;
}

map<string, Link*>& Player::getOriginalLinks() {
    return originalLinks;
}

int Player::getDataAmountDownloaded(){ return dataAmountDownloaded; }

int Player::getVirusAmountDownloaded(){ return virusAmountDownloaded; }

bool Player::getHasWon() { return hasWon; }

bool Player::getHasLost() { return hasLost; }

void Player::setHasWon() { hasWon = true; }

void Player::setHasLost() { hasLost = true; }