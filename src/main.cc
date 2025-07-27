#include "../include/controller.h"
#include "../include/textdisplay.h"
#include "../include/graphicdisplay.h"
#include "../include/player.h"
#include "../include/board.h"
#include "../include/ability.h"
#include "../include/download.h"
#include "../include/linkboost.h"
#include "../include/firewall.h"
#include "../include/scan.h"
#include "../include/polarise.h"
#include "../include/knightify.h"
#include "../include/tradeify.h"
#include "../include/uploadify.h"
#include "../include/weakenify.h"

#include <vector>
#include <memory>
#include <cstring>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    // Default ability orders (LinkBoost, Firewall, Download, Scan, Polarize)
    string ability1Order = "LFDSP";
    string ability2Order = "LFDSP";
    bool useGraphics = false;

    // Parse command line arguments
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-graphics") == 0) {
            useGraphics = true;
        }
        else if (strcmp(argv[i], "-ability1") == 0) {
            if (i + 1 < argc) {
                ability1Order = argv[i + 1];
                ++i; // Skip the next argument since we used it
            } else {
                cerr << "Error: -ability1 requires an ability order string" << endl;
                return 1;
            }
        }
        else if (strcmp(argv[i], "-ability2") == 0) {
            if (i + 1 < argc) {
                ability2Order = argv[i + 1];
                ++i; // Skip the next argument since we used it
            } else {
                cerr << "Error: -ability2 requires an ability order string" << endl;
                return 1;
            }
        }
    }

    // Validate ability orders
    if (ability1Order.length() != 5) {
        cerr << "Error: Player 1 ability order must contain exactly 5 characters" << endl;
        return 1;
    }
    if (ability2Order.length() != 5) {
        cerr << "Error: Player 2 ability order must contain exactly 5 characters" << endl;
        return 1;
    }

    // Create players
    unique_ptr<Player> p1(new Player(1));
    unique_ptr<Player> p2(new Player(2));
    vector<Player*> players{p1.get(), p2.get()};

    // Create board and initialize
    unique_ptr<Board> board(new Board());
    board->initialiseBoard(cin, players);

    // Create controller with the initialized board
    Controller controller(std::move(board));
    controller.setPlayers(players);

    // Add abilities to player 1 based on ability1Order
    for (int i = 0; i < 5; ++i) {
        char c = ability1Order[i];
        Ability* ability = nullptr;
        switch (c) {
            case 'L': ability = new LinkBoost(i); break;
            case 'F': ability = new Firewall(i); break;
            case 'D': ability = new Download(i); break;
            case 'S': ability = new Scan(i); break;
            case 'P': ability = new Polarise(i); break;
            case 'K': ability = new Knightify(i); break;
            case 'W': ability = new Weakenify(i); break;
            case 'U': ability = new Uploadify(i); break;
            case 'T': ability = new Tradeify(i); break;
            default:
                cerr << "Error: Unknown ability character '" << c << "'" << endl;
                return 1;
        }
        p1->addAbility(ability);
    }

    for (int i = 0; i < 5; ++i) {
        char c = ability2Order[i];
        Ability* ability = nullptr;
        switch (c) {
            case 'L': ability = new LinkBoost(i); break;
            case 'F': ability = new Firewall(i); break;
            case 'D': ability = new Download(i); break;
            case 'S': ability = new Scan(i); break;
            case 'P': ability = new Polarise(i); break;
            case 'K': ability = new Knightify(i); break;
            case 'W': ability = new Weakenify(i); break;
            case 'U': ability = new Uploadify(i); break;
            case 'T': ability = new Tradeify(i); break;
            default:
                cerr << "Error: Unknown ability character '" << c << "'" << endl;
                return 1;
        }
        p2->addAbility(ability);
    }

    // Create displays for each player perspective
    TextDisplay* textDisplay1 = new TextDisplay(controller.getBoard(), &players, p1.get(), &controller);
    TextDisplay* textDisplay2 = new TextDisplay(controller.getBoard(), &players, p2.get(), &controller);
    controller.addView(textDisplay1);
    controller.addView(textDisplay2);

    if (useGraphics) {
        cout << "Graphics enabled." << endl;
        GraphicDisplay* graphicDisplay1 = new GraphicDisplay(board.get(), &players, p1.get(), 8);
        GraphicDisplay* graphicDisplay2 = new GraphicDisplay(board.get(), &players, p2.get(), 8);
        controller.addView(graphicDisplay1);
        controller.addView(graphicDisplay2);
    }

    // Start the game
    controller.play();
    return 0;
}
