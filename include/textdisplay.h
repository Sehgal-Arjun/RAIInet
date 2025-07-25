#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "view.h"
#include "board.h"
#include "player.h"

class TextDisplay : public View {
    Board* board;
    std::vector<Player*>* players;
    Player* perspective; // whose perspective to print
public:
    TextDisplay(Board* b, std::vector<Player*>* ps, Player* persp);
    void notifyCell(int r, int c, int change) override;
    void notifyFull() override;
    void print(std::ostream& out) override;
};

#endif
