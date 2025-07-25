#ifndef __GRAPHICDISPLAY_H__
#define __GRAPHICDISPLAY_H__
#include <iostream>
#include <vector>
#include "view.h"
#include "window.h"
#include "board.h"
#include "player.h"

class GraphicDisplay : public View {
    Xwindow xw;
    int gridSize;
    int cellSize;
    Board* board;
    std::vector<Player*>* players;
    Player* perspective;

public:
    // change encoding:
    // 0: empty, 1: unknown, 2: data, 3: virus, 4: firewall (p1), 5: firewall (p2), 6: server port
    GraphicDisplay(Board* b, std::vector<Player*>* ps, Player* persp, int n);
    ~GraphicDisplay();
    void notifyCell(int row, int col, int change) override;
    void notifyFull() override;
    void print(std::ostream &out) override;
};

#endif 
