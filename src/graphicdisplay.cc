#include "../include/graphicdisplay.h"
#include <iostream>
#include <string>

using namespace std;

GraphicDisplay::GraphicDisplay(Board* b, vector<Player*>* ps, Player* persp, int n)
    : xw(500, 500), gridSize{n}, cellSize{500 / n}, board(b), players(ps), perspective(persp) {}

GraphicDisplay::~GraphicDisplay() {}

// This notify should be called with enough info to update the cell
void GraphicDisplay::notifyCell(int row, int col, int change) {
    // change encoding:
    // 0: empty
    // 1: unknown link
    // 2: data (revealed)
    // 3: virus (revealed)
    // 4: firewall (player 1)
    // 5: firewall (player 2)
    // 6: server port
    // 7+: other features (extend as needed)

    int colour = Xwindow::Black;
    string cellText = "";

    switch (change) {
        case 0: // Empty
            colour = Xwindow::White;
            break;
        case 1: // Unknown link
            colour = Xwindow::Black;
            cellText = "?";
            break;
        case 2: // Data (revealed)
            colour = Xwindow::Green;
            cellText = "D"; // Or show strength/letter if available
            break;
        case 3: // Virus (revealed)
            colour = Xwindow::Red;
            cellText = "V"; // Or show strength/letter if available
            break;
        case 4: // Firewall (player 1)
            colour = Xwindow::Blue;
            cellText = "m";
            break;
        case 5: // Firewall (player 2)
            colour = Xwindow::Red;
            cellText = "w";
            break;
        case 6: // Server port
            colour = Xwindow::White;
            cellText = "S";
            break;
        default:
            colour = Xwindow::Black;
            break;
    }

    int x = col * cellSize;
    int y = row * cellSize;
    xw.fillRectangle(x, y, cellSize, cellSize, colour);

    // Draw text if needed (centered)
    if (!cellText.empty()) {
        int textX = x + cellSize / 2 - 8; // Adjust for centering
        int textY = y + cellSize / 2 + 8;
        xw.drawString(textX, textY, cellText);
    }
}

void GraphicDisplay::notifyFull() {
    // Optionally redraw the whole board or print a summary
    print(cout);
}

void GraphicDisplay::print(ostream &out) {
    Player* p1 = (*players)[0];
    Player* p2 = (*players)[1];
    Player* pov = perspective;
    Player* opp = (pov == p1) ? p2 : p1;
    int height = board->getHeight();
    int width = board->getWidth();
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            Tile* t = board->getTileAt(r, c);
            int colour = Xwindow::White;
            string cellText = "";
            if (t->isServerPortTile()) {
                colour = Xwindow::White;
                cellText = "S";
            } else if (t->isFirewallTile()) {
                colour = (t->getFirewallOwner() == p1) ? Xwindow::Blue : Xwindow::Red;
                cellText = (t->getFirewallOwner() == p1) ? "m" : "w";
            } else if (t->getOccupant()) {
                Link* occ = t->getOccupant();
                Player* owner = occ->getOwner();
                if (owner == pov) {
                    // Find letter for this link
                    for (const auto& pair : pov->getLinks()) {
                        if (pair.second.get() == occ) {
                            cellText = pair.first;
                            colour = Xwindow::Black;
                            break;
                        }
                    }
                } else {
                    // Is this link revealed?
                    auto known = pov->getKnownOpponentLinks().find(owner);
                    bool revealed = false;
                    if (known != pov->getKnownOpponentLinks().end()) {
                        for (const auto& pair : known->second) {
                            if (pair.second == occ) {
                                cellText = pair.first;
                                colour = Xwindow::Black;
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
            int x = c * cellSize;
            int y = r * cellSize;
            xw.fillRectangle(x, y, cellSize, cellSize, colour);
            if (!cellText.empty()) {
                int textX = x + cellSize / 2 - 8;
                int textY = y + cellSize / 2 + 8;
                xw.drawString(textX, textY, cellText);
            }
        }
    }
}
