#include "../include/controller.h"
#include "../include/textdisplay.h"
#include "../include/graphicdisplay.h"
#include "../include/player.h"
#include "../include/board.h"
#include <vector>
#include <memory>
#include <cstring>
#include <iostream>

int main(int argc, char* argv[]) {
    // Create players
    std::unique_ptr<Player> p1(new Player(1));
    std::unique_ptr<Player> p2(new Player(2));
    std::vector<Player*> players{p1.get(), p2.get()};

    // Create board and initialize
    std::unique_ptr<Board> board(new Board());
    board->initialiseBoard(std::cin, players);

    // Create controller
    Controller controller;
    controller.setPlayers(players);

    // Check for -graphics argument
    bool useGraphics = false;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-graphics") == 0) {
            useGraphics = true;
            break;
        }
    }

    // Create displays for each player perspective
    TextDisplay* textDisplay1 = new TextDisplay(board.get(), &players, p1.get());
    TextDisplay* textDisplay2 = new TextDisplay(board.get(), &players, p2.get());
    controller.addView(textDisplay1);
    controller.addView(textDisplay2);

    if (useGraphics) {
        std::cout << "Graphics enabled." << std::endl;
        GraphicDisplay* graphicDisplay1 = new GraphicDisplay(board.get(), &players, p1.get(), 8);
        GraphicDisplay* graphicDisplay2 = new GraphicDisplay(board.get(), &players, p2.get(), 8);
        controller.addView(graphicDisplay1);
        controller.addView(graphicDisplay2);
    }

    // Start the game
    controller.play();
    return 0;
}
