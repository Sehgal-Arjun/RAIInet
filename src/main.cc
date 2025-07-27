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
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {
    // Default ability orders (LinkBoost, Firewall, Download, Scan, Polarize)
    string ability1Order = "LFDSP";
    string ability2Order = "LFDSP";
    string link1File = "";
    string link2File = "";
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
        else if (strcmp(argv[i], "-link1") == 0) {
            if (i + 1 < argc) {
                link1File = argv[i + 1];
                ++i; // Skip the next argument since we used it
            } else {
                cerr << "Error: -link1 requires a placement file" << endl;
                return 1;
            }
        }
        else if (strcmp(argv[i], "-link2") == 0) {
            if (i + 1 < argc) {
                link2File = argv[i + 1];
                ++i; // Skip the next argument since we used it
            } else {
                cerr << "Error: -link2 requires a placement file" << endl;
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

    // Read link placement files if provided
    vector<string> link1Order, link2Order;
    
    if (!link1File.empty()) {
        ifstream file(link1File);
        if (!file.is_open()) {
            cerr << "Error: Cannot open link placement file: " << link1File << endl;
            return 1;
        }
        string link;
        while (file >> link && link1Order.size() < 8) {
            link1Order.push_back(link);
        }
        file.close();
        
        if (link1Order.size() != 8) {
            cerr << "Error: Link placement file must contain exactly 8 links for player 1" << endl;
            return 1;
        }
    }
    
    if (!link2File.empty()) {
        ifstream file(link2File);
        if (!file.is_open()) {
            cerr << "Error: Cannot open link placement file: " << link2File << endl;
            return 1;
        }
        string link;
        while (file >> link && link2Order.size() < 8) {
            link2Order.push_back(link);
        }
        file.close();
        
        if (link2Order.size() != 8) {
            cerr << "Error: Link placement file must contain exactly 8 links for player 2" << endl;
            return 1;
        }
    }

    // Create players
    unique_ptr<Player> p1(new Player(1));
    unique_ptr<Player> p2(new Player(2));
    vector<Player*> players{p1.get(), p2.get()};

    // Create board and initialize with custom link orders if provided
    unique_ptr<Board> board(new Board());
    board->initialiseBoard(cin, players, link1Order, link2Order);

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
    auto textDisplay1 = make_unique<TextDisplay>(controller.getBoard(), &players, p1.get(), &controller);
    auto textDisplay2 = make_unique<TextDisplay>(controller.getBoard(), &players, p2.get(), &controller);
    controller.addView(textDisplay1.get());
    controller.addView(textDisplay2.get());

    unique_ptr<GraphicDisplay> graphicDisplay;
    if (useGraphics) {
        cout << "Graphics enabled." << endl;
        graphicDisplay = make_unique<GraphicDisplay>(controller.getBoard(), &players, p1.get(), 8);
        controller.addView(graphicDisplay.get());
        controller.setGraphicDisplay(graphicDisplay.get());  // Give controller access to switch perspectives
    }

    // Start the game
    controller.play();

    // Clear views before objects are destroyed
    controller.clearViews();  // Add this method to Controller

    return 0;
}
