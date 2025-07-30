#include "../include/uploadify.h"
#include "../include/link.h"
#include "../include/player.h"
#include "../include/tile.h"

using namespace std;

Uploadify::Uploadify(int id) : LinkPlayerTileAbility("Uploadify", id) {}

void Uploadify::apply(Link& l, Player& p, Tile& location) {
    // We need to move it from downloadedLinks and pass ownership to upload
    string key = string(1, l.getId());
    
    // Get the unique_ptr from downloadedLinks
    auto& downloadedLinks = p.getDownloadedLinks();
    auto it = downloadedLinks.find(key);
    if (it != downloadedLinks.end()) {
        auto linkPtr = move(it->second);
        downloadedLinks.erase(it);
        
        p.upload(move(linkPtr), &location);
    }
}

bool Uploadify::isValid(Link* l, Player* p, Tile* location) const {
    return (l->getOwner() == p && location->getOccupant() == nullptr && !location->isServerPortTile());
}
