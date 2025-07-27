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

#include <vector>
#include <memory>
#include <cstring>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
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

    // Check for -graphics argument
    bool useGraphics = false;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-graphics") == 0) {
            useGraphics = true;
            break;
        }
    }

    p1->addAbility(new Download(0));
    p1->addAbility(new Scan(1));
    p1->addAbility(new Polarise(2));
    p1->addAbility(new LinkBoost(3));
    p1->addAbility(new Firewall(4));

    p2->addAbility(new Download(0));
    p2->addAbility(new Scan(1));
    p2->addAbility(new Polarise(2));
    p2->addAbility(new LinkBoost(3));
    p2->addAbility(new Firewall(4));

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
