#include <iostream>
#include <map>
#include <string>
#include "../include/textdisplay.h"
#include "../include/controller.h"

using namespace std;

TextDisplay::TextDisplay(Board* b, vector<Player*>* ps, Player* persp, Controller* ctrl)
    : board(b), players(ps), perspective(persp), controller(ctrl) {}

void TextDisplay::notifyCell(int r, int c, int change) {
    // Empty for now
}

void TextDisplay::notifyFull() {
    // Only print if this display's perspective matches the current turn
    if (controller && controller->getCurrentTurn() == perspective) {
        print(cout);
    }
}

void TextDisplay::print(ostream& out) {
    Player* p1 = (*players)[0];
    Player* p2 = (*players)[1];
    Player* pov = perspective;
    Player* opp = (pov == p1) ? p2 : p1;

    // --- Player 1 Header ---
    out << "Player 1:\n";
    out << "Downloaded: " << p1->getDataAmountDownloaded() << "D, " << p1->getVirusAmountDownloaded() << "V\n";
    int p1Abilities = 0;
    for (const auto& ab : p1->getAbilities()) {
        if (!ab->isUsed()) ++p1Abilities;
    }
    out << "Abilities: " << p1Abilities << "\n";
    
    // Show Player 1's links from the current perspective
    if (pov == p1) {
        // If viewing from Player 1's perspective, show all their links
        for (int i = 0; i < 8; ++i) {
            char k = 'a' + i;
            auto it = p1->getLinks().find(string(1, k));
            if (it != p1->getLinks().end()) {
                if (it->second) {
                    out << k << ": " << it->second->makeString();
                } else {
                    out << k << ": ?";
                }
            } else {
                out << k << ": ?";
            }
            if (i % 4 == 3) out << "\n";
            else out << " ";
        }
    } else {
        // If viewing from Player 2's perspective, only show what Player 2 knows
        auto known = pov->getKnownOpponentLinks().find(p1);
        for (int i = 0; i < 8; ++i) {
            char k = 'a' + i;
            if (known != pov->getKnownOpponentLinks().end()) {
                auto it = known->second.find(string(1, k));
                if (it != known->second.end() && it->second) {
                    out << k << ": " << it->second->makeString();
                } else {
                    out << k << ": ?";
                }
            } else {
                out << k << ": ?";
            }
            if (i % 4 == 3) out << "\n";
            else out << " ";
        }
    }
    out << "========\n";

    // --- Board ---
    int height = board->getHeight();
    int width = board->getWidth();
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            Tile* t = board->getTileAt(r, c);
            char symbol = '.';
            if (t->isServerPortTile()) {
                symbol = 'S';
            } 
            else if (t->isFirewallTile()) {
                if (t->getOccupant() == nullptr){
                    symbol = (t->getFirewallOwner() == p1 ? 'm' : 'w');
                }
                else {
                    Link* occ = t->getOccupant();
                    // Find letter for this link
                    for (const auto& pair : occ->getOwner()->getLinks()) {
                        if (pair.second.get() == occ) {
                            symbol = pair.first[0];
                            break;
                        }
                    }
                }
            } 
            else if (t->getOccupant()) {
                Link* occ = t->getOccupant();
                // Find letter for this link
                for (const auto& pair : occ->getOwner()->getLinks()) {
                    if (pair.second.get() == occ) {
                        symbol = pair.first[0];
                        break;
                    }
                }
            }
            out << symbol;
        }
        out << "\n";
    }
    out << "========\n";

    // --- Player 2 Header ---
    out << "Player 2:\n";
    out << "Downloaded: " << p2->getDataAmountDownloaded() << "D, " << p2->getVirusAmountDownloaded() << "V\n";
    int p2Abilities = 0;
    for (const auto& ab : p2->getAbilities()) {
        if (!ab->isUsed()) ++p2Abilities;
    }
    out << "Abilities: " << p2Abilities << "\n";
    
    // Show Player 2's links from the current perspective
    if (pov == p2) {
        // If viewing from Player 2's perspective, show all their links
        for (int i = 0; i < 8; ++i) {
            char k = 'A' + i;
            auto it = p2->getLinks().find(string(1, k));
            if (it != p2->getLinks().end()) {
                if (it->second) {
                    out << k << ": " << it->second->makeString();
                } else {
                    out << k << ": ?";
                }
            } else {
                out << k << ": ?";
            }
            if (i % 4 == 3) out << "\n";
            else out << " ";
        }
    } else {
        // If viewing from Player 1's perspective, only show what Player 1 knows
        auto known = pov->getKnownOpponentLinks().find(p2);
        for (int i = 0; i < 8; ++i) {
            char k = 'A' + i;
            if (known != pov->getKnownOpponentLinks().end()) {
                auto it = known->second.find(string(1, k));
                if (it != known->second.end() && it->second) {
                    out << k << ": " << it->second->makeString();
                } else {
                    out << k << ": ?";
                }
            } else {
                out << k << ": ?";
            }
            if (i % 4 == 3) out << "\n";
            else out << " ";
        }
    }
    out << "\n";

    out << "Player " << pov->getPlayerId() << "'s turn! \n";
}
