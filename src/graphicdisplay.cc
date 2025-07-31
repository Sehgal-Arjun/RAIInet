#include "../include/graphicdisplay.h"
#include "../include/basiclink.h"
#include <iostream>
#include <string>

using namespace std;

GraphicDisplay::GraphicDisplay(Board* b, vector<Player*>* ps, Player* persp, int n)
    : xw(500, 750), gridSize{n}, cellSize{50}, board(b), players(ps), perspective(persp),
      previousBoard(n, vector<string>(n, "")), 
      previousP1Data(-1), previousP1Virus(-1), previousP1Abilities(-1),
      previousP2Data(-1), previousP2Virus(-1), previousP2Abilities(-1),
      needsFullRedraw(true) {
    initializePreviousState();
}

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
            auto displayData = getTileDisplayData(tile);
            
            int x = boardStartX + (c * cellSize);
            int y = boardStartY + (r * cellSize);
            
            renderTileContent(x, y, displayData.first, displayData.second);
        }
    }
}

void GraphicDisplay::notify(NotificationType type) {
    // Respond differently based on notification type
    switch (type) {
        case NotificationType::MOVE_MADE:
            // For moves, we can use partial update optimization
            needsFullRedraw = false;
            if (perspective && board) {
                print(cout);
            }
            break;
            
        case NotificationType::ABILITY_USED:
            needsFullRedraw = true;
            if (perspective && board) {
                print(cout);
            }
            break;
            
        case NotificationType::BATTLE_OCCURRED:
        case NotificationType::DOWNLOAD_OCCURRED:
            needsFullRedraw = false;
            if (perspective && board) {
                print(cout);
            }
            break;
            
        case NotificationType::TURN_SWITCHED:
            // Turn switch may require perspective change, minimal update
            needsFullRedraw = false;
            if (perspective && board) {
                print(cout);
            }
            break;
            
        case NotificationType::GAME_START:
        case NotificationType::FULL_UPDATE:
        default:
            // Full redraw for these cases
            needsFullRedraw = true;
            if (perspective && board) {
                print(cout);
            }
            break;
    }
}

void GraphicDisplay::notifyFull() {
    if (perspective && board) {
        print(cout);
    }
}

void GraphicDisplay::print(ostream &out) {
    if (needsFullRedraw) {
        clearWindow();
        
        Player* player1;
        Player* player2;
        findPlayers(player1, player2);
        
        if (!player1 || !player2) return; // Safety check
        
        // Always draw Player 1 info at top (but visibility depends on perspective)
        drawPlayerInfo(player1, 20);
        
        // Draw the board in the middle
        drawBoard();
        
        // Always draw Player 2 info at bottom (but visibility depends on perspective)
        drawPlayerInfo(player2, 600);
        
        // Update our tracking state
        initializePreviousState();
        needsFullRedraw = false;
    } else {
        Player* player1;
        Player* player2;
        findPlayers(player1, player2);
        
        if (!player1 || !player2) return;
        
        // Check and update player info only if changed
        int p1Data = player1->getDataAmountDownloaded();
        int p1Virus = player1->getVirusAmountDownloaded();
        int p1Abilities = 0;
        for (const auto& ability : player1->getAbilities()) {
            if (!ability->isUsed()) p1Abilities++;
        }
        
        int p2Data = player2->getDataAmountDownloaded();
        int p2Virus = player2->getVirusAmountDownloaded();
        int p2Abilities = 0;
        for (const auto& ability : player2->getAbilities()) {
            if (!ability->isUsed()) p2Abilities++;
        }
        
        if (previousP1Data != p1Data || previousP1Virus != p1Virus || previousP1Abilities != p1Abilities ||
            previousP2Data != p2Data || previousP2Virus != p2Virus || previousP2Abilities != p2Abilities) {
            updatePlayerInfo(player1);
            updatePlayerInfo(player2);
        }
        
        // Check each tile and only update if it actually changed
        for (int r = 0; r < gridSize; ++r) {
            for (int c = 0; c < gridSize; ++c) {
                string currentDisplay = getTileDisplayString(r, c);
                if (previousBoard[r][c] != currentDisplay) {
                    drawSingleTile(r, c);
                    previousBoard[r][c] = currentDisplay;
                }
            }
        }
    }
}

void GraphicDisplay::setPerspective(Player* newPerspective) {
    perspective = newPerspective;
    
    // Force redraw of all tiles with occupants since colors change with perspective
    for (int r = 0; r < gridSize; ++r) {
        for (int c = 0; c < gridSize; ++c) {
            Tile* tile = board->getTileAt(r, c);
            if (tile && tile->getOccupant()) {
                drawSingleTile(r, c);
                previousBoard[r][c] = getTileDisplayString(r, c);
            }
        }
    }
    
    // Update player info sections
    Player* player1;
    Player* player2;
    findPlayers(player1, player2);
    
    if (player1 && player2) {
        // Clear and redraw player info sections
        xw.fillRectangle(0, 15, 500, 120, Xwindow::White);
        drawPlayerInfo(player1, 20);
        
        xw.fillRectangle(0, 595, 500, 120, Xwindow::White);
        drawPlayerInfo(player2, 600);
        
        // Update tracking state
        updatePlayerStats(player1);
        updatePlayerStats(player2);
    }
}

void GraphicDisplay::initializePreviousState() {
    // Initialize the previous board state
    for (int r = 0; r < gridSize; ++r) {
        for (int c = 0; c < gridSize; ++c) {
            previousBoard[r][c] = getTileDisplayString(r, c);
        }
    }
    
    // Initialize player stats
    if (!players->empty() && players->size() >= 2) {
        updatePlayerStats((*players)[0]);
        updatePlayerStats((*players)[1]);
    }
}

std::string GraphicDisplay::getTileDisplayString(int row, int col) {
    Tile* tile = board->getTileAt(row, col);
    auto displayData = getTileDisplayData(tile);
    return displayData.first;
}

void GraphicDisplay::drawSingleTile(int row, int col) {
    Tile* tile = board->getTileAt(row, col);
    if (!tile) return;
    
    int boardStartY = 150;
    int boardStartX = 50;
    
    auto displayData = getTileDisplayData(tile);
    
    int x = boardStartX + (col * cellSize);
    int y = boardStartY + (row * cellSize);
    
    renderTileContent(x, y, displayData.first, displayData.second);
}

void GraphicDisplay::updatePlayerInfo(Player* player) {
    if (!player) return;
    
    int currentData = player->getDataAmountDownloaded();
    int currentVirus = player->getVirusAmountDownloaded();
    int currentAbilities = 0;
    for (const auto& ability : player->getAbilities()) {
        if (!ability->isUsed()) currentAbilities++;
    }
    
    bool dataChanged = false, virusChanged = false, abilitiesChanged = false;
    int* prevData = nullptr;
    int* prevVirus = nullptr;
    int* prevAbilities = nullptr;
    
    if (player->getPlayerId() == 1) {
        prevData = &previousP1Data;
        prevVirus = &previousP1Virus;
        prevAbilities = &previousP1Abilities;
    } else if (player->getPlayerId() == 2) {
        prevData = &previousP2Data;
        prevVirus = &previousP2Virus;
        prevAbilities = &previousP2Abilities;
    } else {
        return; // Invalid player ID
    }
    
    dataChanged = (*prevData != currentData);
    virusChanged = (*prevVirus != currentVirus);
    abilitiesChanged = (*prevAbilities != currentAbilities);
    
    if (dataChanged) *prevData = currentData;
    if (virusChanged) *prevVirus = currentVirus;
    if (abilitiesChanged) *prevAbilities = currentAbilities;
    
    // Only redraw specific lines that changed
    if (dataChanged || virusChanged || abilitiesChanged) {
        int yOffset = (player->getPlayerId() == 1) ? 20 : 600;
        
        if (dataChanged || virusChanged) {
            // Clear and redraw only the downloaded line
            xw.fillRectangle(10, yOffset + 10, 480, 20, Xwindow::White);
            xw.drawString(10, yOffset + 20, "Downloaded: " + to_string(currentData) + "D, " + to_string(currentVirus) + "V");
        }
        
        if (abilitiesChanged) {
            // Clear and redraw only the abilities line
            xw.fillRectangle(10, yOffset + 30, 480, 20, Xwindow::White);
            xw.drawString(10, yOffset + 40, "Abilities: " + to_string(currentAbilities));
        }
    }
}

void GraphicDisplay::forceFullRedraw() {
    needsFullRedraw = true;
}

// Helper method to find player 1 and player 2
void GraphicDisplay::findPlayers(Player*& player1, Player*& player2) {
    player1 = nullptr;
    player2 = nullptr;
    for (Player* p : *players) {
        if (p->getPlayerId() == 1) {
            player1 = p;
        } else if (p->getPlayerId() == 2) {
            player2 = p;
        }
    }
}

// Helper method to get link display info
std::pair<std::string, int> GraphicDisplay::getLinkDisplayInfo(Link* link, Player* owner) {
    std::string cellText;
    int colour;
    
    if (owner == perspective) {
        // Own link - find the character
        auto result = findLinkInMaps(link, perspective->getLinks(), perspective->getDownloadedLinks());
        if (result.first) {
            cellText = result.second;
            colour = (link->getLinkType() == LinkType::DATA) ? Xwindow::Green : Xwindow::Red;
            return {cellText, colour};
        }
    } else {
        // Opponent's link - just show the letter
        auto known = perspective->getKnownOpponentLinks().find(owner);
        
        // First, find the letter for this link
        for (const auto& pair : owner->getLinks()) {
            if (pair.second.get() == link) {
                cellText = pair.first;
                break;
            }
        }
        
        // If not found in active links, check downloaded links
        if (cellText.empty()) {
            for (const auto& pair : owner->getDownloadedLinks()) {
                if (pair.second.get() == link) {
                    cellText = pair.first;
                    break;
                }
            }
        }
        
        return {cellText,  Xwindow::Black};
    }
    
    return {"?", Xwindow::Black};
}

// Helper method to render tile content (reduce duplication in drawing)
void GraphicDisplay::renderTileContent(int x, int y, const std::string& cellText, int colour) {
    xw.fillRectangle(x, y, cellSize, cellSize, colour);
    
    // Draw border
    xw.fillRectangle(x, y, cellSize, 1, Xwindow::Black);
    xw.fillRectangle(x, y, 1, cellSize, Xwindow::Black);
    xw.fillRectangle(x + cellSize - 1, y, 1, cellSize, Xwindow::Black);
    xw.fillRectangle(x, y + cellSize - 1, cellSize, 1, Xwindow::Black);
    
    // Draw text centered with appropriate color for contrast
    int textX = x + cellSize / 2 - 4;
    int textY = y + cellSize / 2 + 4;
    
    // Use white text on black background for better contrast
    if (colour == Xwindow::Black) {
        xw.drawString(textX, textY, cellText, Xwindow::White);
    } else {
        xw.drawString(textX, textY, cellText, Xwindow::Black);
    }
}

// Helper method to update player stats tracking
void GraphicDisplay::updatePlayerStats(Player* player) {
    if (!player) return;
    
    int data = player->getDataAmountDownloaded();
    int virus = player->getVirusAmountDownloaded();
    int abilities = 0;
    for (const auto& ability : player->getAbilities()) {
        if (!ability->isUsed()) abilities++;
    }
    
    if (player->getPlayerId() == 1) {
        previousP1Data = data;
        previousP1Virus = virus;
        previousP1Abilities = abilities;
    } else if (player->getPlayerId() == 2) {
        previousP2Data = data;
        previousP2Virus = virus;
        previousP2Abilities = abilities;
    }
}

// Helper method to get tile display data
std::pair<std::string, int> GraphicDisplay::getTileDisplayData(Tile* tile) {
    if (!tile) return {".", Xwindow::White};
    
    if (tile->isServerPortTile()) {
        return {"S", Xwindow::Blue};
    } 
    else if (tile->isFirewallTile()) {
        if (tile->getOccupant() == nullptr) {
            bool isPlayer1Firewall = (tile->getFirewallOwner() == (*players)[0]);
            return {isPlayer1Firewall ? "m" : "w", isPlayer1Firewall ? Xwindow::Blue : Xwindow::Red};
        } 
        else {
            // Firewall tile with occupant
            Link* occ = tile->getOccupant();
            Player* owner = occ->getOwner();
            return getLinkDisplayInfo(occ, owner);
        }
    } else if (tile->getOccupant()) {
        Link* occ = tile->getOccupant();
        Player* owner = occ->getOwner();
        return getLinkDisplayInfo(occ, owner);
    }
    
    return {".", Xwindow::White};
}

// Helper method to find link in multiple maps
std::pair<bool, std::string> GraphicDisplay::findLinkInMaps(Link* link, const std::map<std::string, std::unique_ptr<Link>>& links1, const std::map<std::string, std::unique_ptr<Link>>& links2) {
    for (const auto& pair : links1) {
        if (pair.second.get() == link) {
            return {true, pair.first};
        }
    }
    for (const auto& pair : links2) {
        if (pair.second.get() == link) {
            return {true, pair.first};
        }
    }
    return {false, ""};
}
