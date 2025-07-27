#include "../include/graphicdisplay.h"
#include "../include/basiclink.h"
#include <iostream>
#include <string>

using namespace std;

GraphicDisplay::GraphicDisplay(Board* b, vector<Player*>* ps, Player* persp, int n)
    : xw(500, 750), gridSize{n}, cellSize{50}, board(b), players(ps), perspective(persp) {}

GraphicDisplay::~GraphicDisplay() {}

void GraphicDisplay::clearWindow() {
    xw.fillRectangle(0, 0, 500, 750, Xwindow::White);
}

void GraphicDisplay::drawPlayerInfo(Player* player, int yOffset) {
    int xOffset = 10;
    
    // Player title
    xw.drawString(xOffset, yOffset, "Player " + to_string(player->getPlayerId()) + ":");
    yOffset += 20;
    
    // Downloaded counts
    xw.drawString(xOffset, yOffset, "Downloaded: " + to_string(player->getDataAmountDownloaded()) + "D, " + to_string(player->getVirusAmountDownloaded()) + "V");
    yOffset += 20;
    
    // Abilities count
    int abilitiesCount = 0;
    for (const auto& ability : player->getAbilities()) {
        if (!ability->isUsed()) abilitiesCount++;
    }
    xw.drawString(xOffset, yOffset, "Abilities: " + to_string(abilitiesCount));
    yOffset += 20;
    
    // Player's links - show details if this is the current perspective, otherwise show as known opponent links
    char linkID = (player->getPlayerId() == 1) ? 'a' : 'A';
    
    if (player == perspective) {
        // This is the current player's perspective - show their original links
        for (int i = 0; i < 8; ++i) {
            string linkKey(1, linkID);
            auto& originalLinks = player->getOriginalLinks();
            auto it = originalLinks.find(linkKey);
            
            string linkInfo;
            if (it != originalLinks.end() && it->second) {
                linkInfo = linkKey + ": " + it->second->makeString();
            } else {
                linkInfo = linkKey + ": ?";
            }
            
            if (i % 4 == 0 && i > 0) {
                yOffset += 20;
                xOffset = 10;
            }
            
            xw.drawString(xOffset, yOffset, linkInfo);
            xOffset += 60;
            linkID++;
        }
    } 
    else {
        // This is the opponent from current perspective - show only known links
        auto known = perspective->getKnownOpponentLinks().find(player);
        
        for (int i = 0; i < 8; ++i) {
            string linkKey(1, linkID);
            string linkInfo;
            
            if (known != perspective->getKnownOpponentLinks().end()) {
                auto it = known->second.find(linkKey);
                if (it != known->second.end() && it->second) {
                    linkInfo = linkKey + ": " + it->second->makeString();
                } else {
                    linkInfo = linkKey + ": ?";
                }
            } 
            else {
                linkInfo = linkKey + ": ?";
            }
            
            if (i % 4 == 0 && i > 0) {
                yOffset += 20;
                xOffset = 10;
            }
            
            xw.drawString(xOffset, yOffset, linkInfo);
            xOffset += 60;
            linkID++;
        }
    }
}

void GraphicDisplay::drawBoard() {
    int boardStartY = 150;
    int boardStartX = 50;
    
    for (int r = 0; r < gridSize; ++r) {
        for (int c = 0; c < gridSize; ++c) {
            Tile* tile = board->getTileAt(r, c);
            int colour = Xwindow::White;
            string cellText = ".";
            
            if (tile->isServerPortTile()) {
                colour = Xwindow::Blue;
                cellText = "S";
            } 
            else if (tile->isFirewallTile()) {
                if (tile->getOccupant() == nullptr) {
                    colour = (tile->getFirewallOwner() == (*players)[0]) ? Xwindow::Blue : Xwindow::Red;
                    cellText = (tile->getFirewallOwner() == (*players)[0]) ? "m" : "w";
                } 
                else {
                    // Firewall tile with occupant - treat as regular occupant
                    Link* occ = tile->getOccupant();
                    Player* owner = occ->getOwner();
                    
                    if (owner == perspective) {
                        // Own link - show actual character
                        for (const auto& pair : perspective->getLinks()) {
                            if (pair.second.get() == occ) {
                                cellText = pair.first;
                                colour = (occ->getLinkType() == LinkType::DATA) ? Xwindow::Green : Xwindow::Red;
                                break;
                            }
                        }
                        // Also check downloaded links
                        for (const auto& pair : perspective->getDownloadedLinks()) {
                            if (pair.second.get() == occ) {
                                cellText = pair.first;
                                colour = (occ->getLinkType() == LinkType::DATA) ? Xwindow::Green : Xwindow::Red;
                                break;
                            }
                        }
                    } else {
                        // Opponent's link - check if revealed
                        auto known = perspective->getKnownOpponentLinks().find(owner);
                        bool revealed = false;
                        if (known != perspective->getKnownOpponentLinks().end()) {
                            for (const auto& pair : known->second) {
                                if (pair.second == occ) {
                                    cellText = pair.first;
                                    colour = (occ->getLinkType() == LinkType::DATA) ? Xwindow::Green : Xwindow::Red;
                                    revealed = true;
                                    break;
                                }
                            }
                        }
                        if (!revealed) {
                            cellText = "?";
                            colour = Xwindow::Black;
                        }
                    }
                }
            } else if (tile->getOccupant()) {
                Link* occ = tile->getOccupant();
                Player* owner = occ->getOwner();
                
                if (owner == perspective) {
                    // Own link - show actual character
                    for (const auto& pair : perspective->getLinks()) {
                        if (pair.second.get() == occ) {
                            cellText = pair.first;
                            colour = (occ->getLinkType() == LinkType::DATA) ? Xwindow::Green : Xwindow::Red;
                            break;
                        }
                    }
                    // Also check downloaded links
                    for (const auto& pair : perspective->getDownloadedLinks()) {
                        if (pair.second.get() == occ) {
                            cellText = pair.first;
                            colour = (occ->getLinkType() == LinkType::DATA) ? Xwindow::Green : Xwindow::Red;
                            break;
                        }
                    }
                } else {
                    // Opponent's link - check if revealed
                    auto known = perspective->getKnownOpponentLinks().find(owner);
                    bool revealed = false;
                    if (known != perspective->getKnownOpponentLinks().end()) {
                        for (const auto& pair : known->second) {
                            if (pair.second == occ) {
                                cellText = pair.first;
                                colour = (occ->getLinkType() == LinkType::DATA) ? Xwindow::Green : Xwindow::Red;
                                revealed = true;
                                break;
                            }
                        }
                    }
                    if (!revealed) {
                        cellText = "?";
                        colour = Xwindow::Black;
                    }
                }
            }
            
            int x = boardStartX + (c * cellSize);
            int y = boardStartY + (r * cellSize);
            
            xw.fillRectangle(x, y, cellSize, cellSize, colour);
            
            // Draw border
            xw.fillRectangle(x, y, cellSize, 1, Xwindow::Black);
            xw.fillRectangle(x, y, 1, cellSize, Xwindow::Black);
            xw.fillRectangle(x + cellSize - 1, y, 1, cellSize, Xwindow::Black);
            xw.fillRectangle(x, y + cellSize - 1, cellSize, 1, Xwindow::Black);
            
            // Draw text centered
            int textX = x + cellSize / 2 - 4;
            int textY = y + cellSize / 2 + 4;
            xw.drawString(textX, textY, cellText);
        }
    }
}

void GraphicDisplay::notifyCell(int row, int col, int change) {
    // Update the display when notified of a cell change
    print(cout);
}

void GraphicDisplay::notifyFull() {
    // Redraw the entire display
    print(cout);
}

void GraphicDisplay::print(ostream &out) {
    // Clear the window
    clearWindow();
    
    Player* player1 = nullptr;
    Player* player2 = nullptr;
    
    // Find Player 1 and Player 2
    for (Player* p : *players) {
        if (p->getPlayerId() == 1) {
            player1 = p;
        } 
        else if (p->getPlayerId() == 2) {
            player2 = p;
        }
    }
    
    if (!player1 || !player2) return; // Safety check
    
    // Always draw Player 1 info at top (but visibility depends on perspective)
    drawPlayerInfo(player1, 20);
    
    // Draw the board in the middle
    drawBoard();
    
    // Always draw Player 2 info at bottom (but visibility depends on perspective)
    drawPlayerInfo(player2, 600);
}

void GraphicDisplay::setPerspective(Player* newPerspective) {
    perspective = newPerspective;
    // Immediately refresh the display with the new perspective
    print(cout);
}
