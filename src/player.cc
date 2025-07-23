#include "player.h"
#include "link.h"
#include "basiclink.h"
#include <string>

using namespace std;

void Player::download(Link* l){
    // 1. mark link as not in use
    l->setInUse(false);
    
    // 2. move link to (-1, -1)
    l->setLocation(pair(-1, -1));

    // 3. increment data/virusAmountDownloaded
    if (l->getLinkType() == LinkType::DATA) {
        this.dataAmountDownloaded++;
    }
    else if (l->getLinkType() == LinkType::VIRUS){
        this.virusAmountDownloaded++;
    }
}

void Player::printAbilities(std::ostream& out) {
    for (const auto& ability : chosenAbilities) {
        out << ability->getID() << ". " << ability.getName()
        << " " << (ability.isUsed() ? "(USED)" : "(UNUSED)")
            << std::endl;
    }
}

vector<Ability> getAbilities(){ return chosenAbilities; }
