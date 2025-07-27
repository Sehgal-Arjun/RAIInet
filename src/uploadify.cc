#include "../include/uploadify.h"
#include "../include/link.h"
#include "../include/player.h"
#include "../include/tile.h"

using namespace std;

Uploadify::Uploadify(int id): Ability("Uploadify", id) {};

void Uploadify::applyAbility(Link& l, Player& p, Tile& location) {
    // We need to move it from downloadedLinks and pass ownership to upload
    string key = string(1, l.getId());
    
    // Get the unique_ptr from downloadedLinks
    auto& downloadedLinks = p.getDownloadedLinks();
    auto it = downloadedLinks.find(key);
    if (it != downloadedLinks.end()) {
        auto linkPtr = std::move(it->second);
        downloadedLinks.erase(it);
        
        p.upload(std::move(linkPtr), &location);
    }
}

bool Uploadify::isValidUse(Link* l, Player* p, Tile* location) const {
    // location that is being uploaded to is empty, can only upload your own link, and cannot upload to a server tile!
    return (l->getOwner() == p && location->getOccupant() == nullptr && !location->isServerPortTile());
}

void Uploadify::applyAbility(Link& l) {
    // Empty implementation
}

void Uploadify::applyAbility(Tile& t, Player& p) {
    // Empty implementation
}

void Uploadify::applyAbility(Link& l, Player& p) {
    // Empty implementation
}

void Uploadify::applyAbility(Link& l1, Link& l2) {
    // Empty implementation
}

bool Uploadify::isValidUse(Link* l) const {
    // Empty implementation
    return false;
}

bool Uploadify::isValidUse(Link* l, Player* p) const {
    // Empty implementation
    return false;
}

bool Uploadify::isValidUse(Link* l1, Link* l2) const {
    // Empty implementation
    return false;
}

bool Uploadify::isValidUse(Tile* t) const {
    // Empty implementation
    return false;
}
