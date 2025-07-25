#include <iostream>
#include <map>
#include <string>
#include "../include/textdisplay.h"

using namespace std;

TextDisplay::TextDisplay(Board* b, std::vector<Player*>* ps, Player* persp)
    : board(b), players(ps), perspective(persp) {}

void TextDisplay::notifyCell(int r, int c, int change) {
    // Empty for now
}

void TextDisplay::notifyFull() {
    print(std::cout);
}

void TextDisplay::print(std::ostream& out) {
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
    for (char k = 'a'; k <= 'h'; ++k) {
        auto it = p1->getLinks().find(std::string(1, k));
        if (it != p1->getLinks().end()) {
            if (it->second) {
                out << k << ": ";
                out << it->second->makeString();
            }
        }
    }
    out << "\n========\n";

    // --- Board ---
    int height = board->getHeight();
    int width = board->getWidth();
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            Tile* t = board->getTileAt(r, c);
            char symbol = '.';
            if (t->isServerPortTile()) symbol = 'S';
            else if (t->isFirewallTile()) symbol = (t->getFirewallOwner() == p1 ? 'm' : 'w');
            else if (t->getOccupant()) {
                Link* occ = t->getOccupant();
                Player* owner = occ->getOwner();
                if (owner == pov) {
                    // Find letter for this link
                    for (const auto& pair : pov->getLinks()) {
                        if (pair.second.get() == occ) {
                            symbol = pair.first[0];
                            break;
                        }
                    }
                } else {
                    // Is this link revealed?
                    auto known = pov->getKnownOpponentLinks().find(owner);
                    bool revealed = false;
                    if (known != pov->getKnownOpponentLinks().end()) {
                        for (const auto& pair : known->second) {
                            if (pair.second.get() == occ) {
                                symbol = pair.first[0];
                                revealed = true;
                                break;
                            }
                        }
                    }
                    if (!revealed) symbol = '?';
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
    // Print A-H links (from pov's perspective, use knownOpponentLinks)
    auto known = pov->getKnownOpponentLinks().find(opp);
    for (char k = 'A'; k <= 'H'; ++k) {
        if (known != pov->getKnownOpponentLinks().end()) {
            auto it = known->second.find(std::string(1, k));
            if (it != known->second.end() && it->second) {
                out << k << ": ";
                out << it->second->makeString();
            } else {
                out << k << ": ? ";
            }
        } else {
            out << k << ": ? ";
        }
    }
    out << "\n";
}
