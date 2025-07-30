#include "../include/controller.h"
#include "../include/basiclink.h"
#include "../include/graphicdisplay.h"

#include <iostream>
#include <memory>
#include <sstream>
#include <fstream>

using namespace std;

std::pair<int, int> Controller::calculateMove(Link* l, std::string direction){
    if (l->getTile() == nullptr) {
        // Link has been downloaded, return invalid position
        return make_pair(-1, -1);
    }
    
    int row = l->getTile()->getLocation().first;
    int col = l->getTile()->getLocation().second;

    if (direction == "up") {
        return make_pair(row - l->getTravelDistance(), col);
    }
    else if (direction == "down") {
        return make_pair(row + l->getTravelDistance(), col);
    }
    else if (direction == "left") {
        return make_pair(row, col - l->getTravelDistance());
    }
    else { // direction == "right"
        return make_pair(row, col + l->getTravelDistance());
    }
}

std::pair<int, int> Controller::calculateMove(Link* l, std::string direction1, std::string direction2){
    if (l->getTile() == nullptr) {
        // Link has been downloaded, return invalid position
        return make_pair(-1, -1);
    }
    
    int row = l->getTile()->getLocation().first;
    int col = l->getTile()->getLocation().second;

    if (direction1 == "up") {
        if (direction2 == "left"){
            return make_pair(row - l->getTravelDistance() * 2, col - l->getTravelDistance());
        }
        else{ // direction2 == "right"
            return make_pair(row - l->getTravelDistance() * 2, col + l->getTravelDistance());
        }
    }
    else if (direction1 == "down") {
        if (direction2 == "left"){
            return make_pair(row + l->getTravelDistance() * 2, col - l->getTravelDistance());
        }
        else{ // direction2 == "right"
            return make_pair(row + l->getTravelDistance() * 2, col + l->getTravelDistance());
        }
    }
    else if (direction1 == "left") {
        if (direction2 == "up"){
            return make_pair(row - l->getTravelDistance(), col - l->getTravelDistance() * 2);
        }
        else{ // direction2 == "down"
            return make_pair(row + l->getTravelDistance() * 2, col - l->getTravelDistance() * 2);
        }
    }
    else { // direction1 == "right"
        if (direction2 == "up"){
            return make_pair(row - l->getTravelDistance(), col + l->getTravelDistance() * 2);
        }
        else{ // direction2 == "down"
            return make_pair(row + l->getTravelDistance() * 2, col + l->getTravelDistance() * 2);
        }
    }
}

void Controller::move(pair<int, int> location, Link& l, Player& p) {
    int row = location.first;
    int col = location.second;
    int height = board->getHeight();

    // Check if moving off opponent's edge
    if ((p.getPlayerId() == 1 && row >= height) || (p.getPlayerId() == 2 && row < 0)) {
        // Player downloads their own link
        auto downloadedLink = p.download(&l);

        // Store the downloaded link in the player's collection
        p.storeDownloadedLink(std::move(downloadedLink));
        // No notification here since it's the player's own choice
        return;
    }

    Tile* destination = board->getTileAt(row, col);

    // if moving onto a firewall tile that isn't yours
    if (destination->isFirewallTile() && destination->getFirewallOwner() != &p) {
        // reveal to all players
        for (auto& player : this->players) {
            player->reveal(&l);
        }
        
        // if it's a virus, then download it to the firewall owner
        if (l.getLinkType() == LinkType::VIRUS) {
            auto downloadedLink = l.getOwner()->download(&l);
            
            // Update download counters for the firewall owner
            Player* firewallOwner = destination->getFirewallOwner();
            firewallOwner->incrementVirusDownloaded();
            
            // Store the downloaded link in the firewall owner's collection
            firewallOwner->storeDownloadedLink(std::move(downloadedLink));
        }
        return;
    }
    
    // if moving onto tile which has a link that isn't yours
    if (destination->getOccupant() != nullptr && destination->getOccupant()->getOwner() != &p) {
        // if the battle leads to your link losing (ie, don't need to move it), then return
        if (&battle(l, *destination->getOccupant(), *destination, *l.getTile()) != &l) {
            return;
        }
    }

    // move the tile
    l.getTile()->setOccupant(nullptr);
    l.setTile(destination);
    destination->setOccupant(&l);
    
    // After moving, check if we're on an opponent's server port
    if (destination->isServerPortTile() && destination->getServerPortOwner() != &p) {
        Player* serverOwner = destination->getServerPortOwner();
        auto downloadedLink = l.getOwner()->download(&l);
        
        // Update download counters for the server owner
        if (l.getLinkType() == LinkType::DATA) {
            serverOwner->incrementDataDownloaded();
        } else if (l.getLinkType() == LinkType::VIRUS) {
            serverOwner->incrementVirusDownloaded();
        }
        
        // Store the downloaded link in the server owner's collection
        serverOwner->storeDownloadedLink(std::move(downloadedLink));
        return;
    }
}

bool Controller::checkValidMove(Link* l, pair<int, int> location) {
    int row = location.first;
    int col = location.second;

    int height = board->getHeight();
    int width = board->getWidth();

    if (col < 0 || col >= width) {
        return false;
    }

    // Allow moves off opponent's edge (for downloading), but not off own edge
    if (currentTurn->getPlayerId() == 1) {
        if (row < 0) {  // Player 1 can't move off their own edge (top)
            return false;
        }
        // Player 1 CAN move off bottom edge (row >= height) - opponent's edge
    }
    else if (currentTurn->getPlayerId() == 2) {
        if (row >= height) {  // Player 2 can't move off their own edge (bottom)
            return false;
        }
        // Player 2 CAN move off top edge (row < 0) - opponent's edge
    }

    // If moving off opponent's edge, it's valid (handled in move method)
    if ((currentTurn->getPlayerId() == 1 && row >= height) || 
        (currentTurn->getPlayerId() == 2 && row < 0)) {
        return true;
    }

    // For normal moves on the board, check destination tile
    Tile* destination = board->getTileAt(row, col);
    if (!destination) {
        return false;
    }

    Link* occupant = destination->getOccupant();
    if (occupant && occupant->getOwner() == currentTurn) {
        return false;
    }

    if (destination->isServerPortTile() && destination->getServerPortOwner() == currentTurn) {
        return false;
    }

    return true;
}

bool Controller::makeMove(Link& l, const std::string direction, Player& p) {
    if (!isValidMove(&l, direction)) {
        cout << "INVALID MOVE" << endl;
        return false;
    }

    move(calculateMove(&l, direction), l, p);
    return true;
}

bool Controller::makeMove(Link& l, const std::string directionFirst, const std::string directionSecond, Player& p) {
    if (!isValidMove(&l, directionFirst, directionSecond)) {
        cout << "INVALID MOVE" << endl;
        return false;
    }

    move(calculateMove(&l, directionFirst, directionSecond), l, p);
    return true;
}

bool Controller::isValidMove(Link* l, const std::string& direction) {    
    if (direction != "up" && direction != "down" && direction != "left" && direction != "right") { 
        return false; 
    }

    if (l->getOwner() != currentTurn) {
        return false;
    }

    // Check if link has been downloaded
    if (l->getTile() == nullptr) {
        return false;
    }

    pair<int, int> targetLocation = calculateMove(l, direction);
    bool result = checkValidMove(l, targetLocation);

    return result;
}

bool Controller::isValidMove(Link* l, const std::string& directionFirst, const std::string& directionSecond) {
    if (directionFirst != "up" && directionFirst != "down" && directionFirst != "left" && directionFirst != "right") { 
        return false; 
    }

    if (directionFirst == "up" || directionFirst == "down") {
        if (directionSecond != "left" && directionSecond != "right") { 
            return false; 
        }
    }
    else { // directionFirst == "left" || directionFirst == "right")
        if (directionSecond != "up" && directionSecond != "down") { 
            return false; 
        }
    }

    if (l->getOwner() != currentTurn) {
        return false;
    }

    // Check if link has been downloaded
    if (l->getTile() == nullptr) {
        return false;
    }

    return checkValidMove(l, calculateMove(l, directionFirst, directionSecond));
}

Link& Controller::battle(Link& initiator, Link& victim, Tile& battleTile, Tile& initiatorTile) {
    // reveal both links to all players
    for (auto& p : this->players) {
        p->reveal(&initiator);
        p->reveal(&victim);
    }

    if (initiator.getStrength() == victim.getStrength()){ // links are same strength, initator wins
        Player* winner = initiator.getOwner();
        auto downloadedLink = victim.getOwner()->download(&victim);
        
        // Update download counters for the winner
        if (victim.getLinkType() == LinkType::DATA) {
            winner->incrementDataDownloaded();
        } else if (victim.getLinkType() == LinkType::VIRUS) {
            winner->incrementVirusDownloaded();
        }
        
        // Store the downloaded link in the winner's collection
        winner->storeDownloadedLink(std::move(downloadedLink));
        return initiator;
    }
    else if (initiator.getStrength() > victim.getStrength()){
        Player* winner = initiator.getOwner();
        auto downloadedLink = victim.getOwner()->download(&victim);
        
        // Update download counters for the winner
        if (victim.getLinkType() == LinkType::DATA) {
            winner->incrementDataDownloaded();
        } else if (victim.getLinkType() == LinkType::VIRUS) {
            winner->incrementVirusDownloaded();
        }
        
        // Store the downloaded link in the winner's collection
        winner->storeDownloadedLink(std::move(downloadedLink));
        return initiator;
    }
    else{
        Player* winner = victim.getOwner();
        auto downloadedLink = initiator.getOwner()->download(&initiator);
        
        // Update download counters for the winner
        if (initiator.getLinkType() == LinkType::DATA) {
            winner->incrementDataDownloaded();
        } else if (initiator.getLinkType() == LinkType::VIRUS) {
            winner->incrementVirusDownloaded();
        }
        
        // Store the downloaded link in the winner's collection
        winner->storeDownloadedLink(std::move(downloadedLink));
        return victim;
    }
}

bool Controller::isMoveIntoOpponentServerPort(Tile* t) {
    return (t->isServerPortTile() && t->getServerPortOwner() != currentTurn);
}

bool Controller::isMoveIntoOpponentFirewall(Tile* t) {
    return (t->isFirewallTile() && t->getFirewallOwner() != currentTurn);
}

// useAbility for Download, Scan, Weakenify, and LinkBoost
void Controller::useAbility(Ability& a, Player& p, Link& l) {
    if (auto* linkPlayerAbility = dynamic_cast<LinkPlayerAbility*>(&a)) {
        if (linkPlayerAbility->isValid(&l, &p)) {
            linkPlayerAbility->apply(l, p);
            a.setUsed(true);
            notify(NotificationType::ABILITY_USED);
        } else {
            cout << "INVALID ABILITY: " << a.getName() << endl;
        }
    } else {
        cout << "INVALID ABILITY: " << a.getName() << endl;
    }
}

// useAbility for Firewall
void Controller::useAbility(Ability& a, Player& p, Tile& t) {
    if (auto* tilePlayerAbility = dynamic_cast<TilePlayerAbility*>(&a)) {
        if (tilePlayerAbility->isValid(&t)) {
            tilePlayerAbility->apply(t, p);
            a.setUsed(true);
            notify(NotificationType::ABILITY_USED);
        } else {
            cout << "INVALID ABILITY: " << a.getName() << endl;
        }
    } else {
        cout << "INVALID ABILITY: " << a.getName() << endl;
    }
}

// useAbility for Knightify and Polarise
void Controller::useAbility(Ability& a, Link& l) {
    if (auto* linkAbility = dynamic_cast<LinkAbility*>(&a)) {
        if (linkAbility->isValid(&l)) {
            linkAbility->apply(l);
            a.setUsed(true);
            notify(NotificationType::ABILITY_USED);
        } else {
            cout << "INVALID ABILITY: " << a.getName() << endl;
        }
    } else {
        cout << "INVALID ABILITY: " << a.getName() << endl;
    }
}

// useAbility for Tradeify
void Controller::useAbility(Ability& a, Link& l1, Link& l2) {
    if (auto* linkLinkAbility = dynamic_cast<LinkLinkAbility*>(&a)) {
        if (linkLinkAbility->isValid(&l1, &l2)) {
            linkLinkAbility->apply(l1, l2);
            a.setUsed(true);
            notify(NotificationType::ABILITY_USED);
        } else {
            cout << "INVALID ABILITY: " << a.getName() << endl;
        }
    } else {
        cout << "INVALID ABILITY: " << a.getName() << endl;
    }
}

// useAbility for Uploadify
void Controller::useAbility(Ability& a, Player& p, Link& l, Tile& t) {
    if (auto* linkPlayerTileAbility = dynamic_cast<LinkPlayerTileAbility*>(&a)) {
        if (linkPlayerTileAbility->isValid(&l, &p, &t)) {
            linkPlayerTileAbility->apply(l, p, t);
            a.setUsed(true);
            notify(NotificationType::ABILITY_USED);
        } else {
            cout << "INVALID ABILITY: " << a.getName() << endl;
        }
    } else {
        cout << "INVALID ABILITY: " << a.getName() << endl;
    }
}

int Controller::checkGameWon() {
    for (auto& p : this->players) {
        if (p->getDataAmountDownloaded() >= 4) {
            return p->getPlayerId();  // Just return, don't modify state
        }

        if (p->getVirusAmountDownloaded() >= 4) {
            int remainingPlayers = players.size();

            for (auto& pl : this->players) {
                if (pl->getVirusAmountDownloaded() >= 4) {  // Check the actual condition
                    remainingPlayers--;
                }
            }

            if (remainingPlayers == 1) {
                for (auto& pl : this->players) {
                    if (pl->getVirusAmountDownloaded() < 4) {  // Check the actual condition
                        return pl->getPlayerId();
                    }
                }
            }
        }
    }

    return -1;
}

void Controller::switchTurn() {
    if (players.at(players.size() - 1) == currentTurn) {
        currentTurn = players.at(0);
    }
    else {
        bool cur = false;
        for (auto& p : players) {
            if (currentTurn == p) {
                cur = true;
                continue;
            }
            
            if (cur) {
                currentTurn = p;
                break;
            }
        }
    }
    
    // Update graphics perspective if graphics are enabled
    if (graphicDisplay) {
        graphicDisplay->setPerspective(currentTurn);
    }
}

void Controller::addView(View* v) {
    attach(v);  // Use Subject's attach method
}

void Controller::setGraphicDisplay(GraphicDisplay* gd) {
    graphicDisplay = gd;
}

Link* Controller::getLink(char name){
    // Search both players for the link
    for (auto player : players) {
        Link* link = player->getLink(name);
        if (link != nullptr) {
            return link;
        }
    }
    
    return nullptr;
}

bool Controller::executeCommand(string input){    
    istringstream stream(input);
    string cmd;
    stream >> cmd;
    if (cmd == "move"){ // move a dir, but if link is a knight, then move a dir1 dir2
        char l;
        stream >> l;
        Link* link = getLink(l);
        
        if (link && link->isKnight()){
            string direction1, direction2;
            stream >> direction1 >> direction2;
            if (makeMove(*link, direction1, direction2, *currentTurn)){
                notify(NotificationType::MOVE_MADE);
                switchTurn();
                notify(NotificationType::TURN_SWITCHED);
            }
        }
        else if (link){
            string direction;
            stream >> direction;
            if (makeMove(*link, direction, *currentTurn)){
                notify(NotificationType::MOVE_MADE);
                switchTurn();
                notify(NotificationType::TURN_SWITCHED);
            }
        }
    }

    else if (cmd == "abilities"){
        currentTurn->printAbilities(cout);
    }

    else if (cmd == "ability"){
        int id;
        stream >> id;
        Ability* ability = currentTurn->getAbility(id);
        if (ability == nullptr) {
            cout << "Invalid ability ID!" << endl;
        }
        else {
            if (ability->isUsed()){
                cout << "Ability already used!" << endl;
            }
            else {
                string next;
                stream >> next;

                if (ability->getName() == "Download" || 
                    ability->getName() == "Scan" ||
                    ability->getName() == "LinkBoost" ||
                    ability->getName() == "Weakenify" ){
                    // next should be the link, so should be a-h or A-H
                    char link = next[0];
                    if ((link <= 'h' && link >= 'a') || (link <= 'H' && link >= 'A')) {
                        useAbility(*ability, *currentTurn, *getLink(link));
                    }
                    else{
                        cout << "Invalid input!" << endl;
                    }
                }
                
                else if (ability->getName() == "Firewall" ) {   
                    // next should be the tile, so should be 0-7, and need another char 0-7
                    int x;
                    int y;
                    try {
                        x = stoi(next);
                        stream >> y;
                        if (x <= 7 && x >= 0 && y <= 7 && y >= 0){
                            useAbility(*ability, *currentTurn, *board->getTileAt(x, y));
                        }
                        else{
                            cout << "Invalid input!" << endl;
                        }
                    } catch (const std::invalid_argument& e) {
                        cout << "Invalid input!" << endl;
                    } catch (const std::out_of_range& e) {
                        cout << "Invalid input!" << endl;
                    }
                }

                else if (ability->getName() == "Knightify" || ability->getName() == "Polarise"){
                    // next should be the link, so should be a-h or A-H
                    char link = next[0];
                    if ((link <= 'h' && link >= 'a') || (link <= 'H' && link >= 'A')) {
                        useAbility(*ability, *getLink(link));
                    }
                    else{
                        cout << "Invalid input!" << endl;
                    }
                }

                else if (ability->getName() == "Tradeify"){
                    // next should be a link, and need another link to warp with
                    char link1 = next[0];
                    char link2;
                    stream >> link2;
                    if (((link1 <= 'h' && link1 >= 'a') || (link1 <= 'H' && link1 >= 'A')) && ((link2 <= 'h' && link2 >= 'a') || (link2 <= 'H' && link2 >= 'A'))) {
                        useAbility(*ability, *getLink(link1), *getLink(link2));
                    }
                    else{
                        cout << "Invalid input!" << endl;
                    }
                }

                else if (ability->getName() == "Uploadify") {
                    // next shoud be a link, followed by the coordinates of a tile
                    char link = next[0];
                    int x, y;
                    stream >> x >> y;
                    if (((link <= 'h' && link >= 'a') || (link <= 'H' && link >= 'A')) && ((x >= 0 && x <= board->getWidth() - 1) && (y >= 0 && y <= board->getHeight() - 1))){
                        useAbility(*ability, *currentTurn, *getLink(link), *board->getTileAt(x, y));
                    }
                    else {
                        cout << "Invalid input!" << endl;
                    }
                }

                else {
                    cout << "Invalid ability! Name not found!" << endl;
                }
            }
        }
    }

    else if (cmd == "board"){
        notify(NotificationType::FULL_UPDATE);
        if (graphicDisplay) {
            graphicDisplay->print(cout);
        }
    }

    else if (cmd == "sequence") {
        string filename;
        stream >> filename;
        ifstream file(filename);
        string cmd;
        while(getline(file, cmd)) {
            if (!executeCommand(cmd)) {
                return false;  // If any command says to quit, stop
            }
            int winStatus = checkGameWon();
            if (winStatus != -1) {
                cout << "Player " << winStatus << " wins!" << endl;
                return false;  // Game won, stop executing
            }
        }
    }

    else if (cmd == "quit"){
        return false;
    }

    return true;
}

void Controller::play(){
    currentTurn = players[0];
    string input;
    while(getline(cin, input)) {
        if (!executeCommand(input)) {
            break;
        }
        int winStatus = checkGameWon();
        if (winStatus != -1) {
            cout << "Player " << winStatus << " wins!" << endl;
            break;
        }
    }
}

void Controller::setPlayers(const std::vector<Player*>& players) {
    this->players = players;
}

void Controller::clearViews(){
    // Clear all attached observers (this will be called from Subject's destructor anyway)
}
