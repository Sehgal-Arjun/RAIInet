#include "../include/download.h"
#include "../include/link.h"
#include "../include/player.h"
#include "../include/basiclink.h"

using namespace std;

Download::Download(int id): LinkPlayerAbility("Download", id) {}

void Download::apply(Link& l, Player& p) {
    // Get the current owner of the link
    Player* currentOwner = l.getOwner();
    // Remove the link from the current owner's map (without updating download counters)
    auto downloadedLink = currentOwner->download(&l);
    // Update download counters for the DOWNLOADING player (not the owner who lost the link)
    if (l.getLinkType() == LinkType::DATA) {
        p.incrementDataDownloaded();
    }
    else if (l.getLinkType() == LinkType::VIRUS){
        p.incrementVirusDownloaded();
    }
    
    // Set the new owner
    l.setOwner(&p);
    // Store the downloaded link in the downloading player
    p.storeDownloadedLink(move(downloadedLink));
}

bool Download::isValid(Link* l, Player* p) const {
    // can only download an opponents link!
    return (l->getOwner() != p);
}
