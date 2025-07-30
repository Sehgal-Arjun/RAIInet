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
    
    // Partial updates
    std::vector<std::vector<std::string>> previousBoard;
    int previousP1Data, previousP1Virus, previousP1Abilities;
    int previousP2Data, previousP2Virus, previousP2Abilities;
    bool needsFullRedraw;

public:
    GraphicDisplay(Board* b, std::vector<Player*>* ps, Player* persp, int n);
    ~GraphicDisplay();
    void notifyFull() override;
    void print(std::ostream &out) override;
    void setPerspective(Player* newPerspective);
    void updatePlayerInfo(Player* player);
    void forceFullRedraw();
    
private:
    void drawPlayerInfo(Player* player, int yOffset);
    void drawBoard();
    void drawSingleTile(int row, int col);
    void clearWindow();
    void initializePreviousState();
    std::string getTileDisplayString(int row, int col);
    void findPlayers(Player*& player1, Player*& player2);
    std::pair<std::string, int> getLinkDisplayInfo(Link* link, Player* owner);
    void renderTileContent(int x, int y, const std::string& cellText, int colour);
    void updatePlayerStats(Player* player);
    std::pair<std::string, int> getTileDisplayData(Tile* tile);
    std::pair<bool, std::string> findLinkInMaps(Link* link, const std::map<std::string, std::unique_ptr<Link>>& links1, const std::map<std::string, std::unique_ptr<Link>>& links2);
};

#endif 
