#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "view.h"
#include "board.h"
#include "player.h"

class Controller; // forward declaration

class TextDisplay : public View {
    Board* board;
    std::vector<Player*>* players;
    Player* perspective; // whose perspective to print
    Controller* controller; // to access current turn
public:
    TextDisplay(Board* b, std::vector<Player*>* ps, Player* persp, Controller* ctrl);
    void notifyCell(int r, int c, int change) override;
    void notifyFull() override;
    void print(std::ostream& out) override;
};

#endif
