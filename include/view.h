#ifndef __DISPLAY_H__
#define __DISPLAY_H__
#include <iostream>

enum class NotificationType {
    GAME_START,
    MOVE_MADE,
    ABILITY_USED,
    TURN_SWITCHED,
    BATTLE_OCCURRED,
    DOWNLOAD_OCCURRED,
    FULL_UPDATE
};

class View {
  public:
  virtual void notify(NotificationType type) = 0;
  virtual void notifyFull() = 0;  // Keep for backward compatibility
  virtual void print(std::ostream &out) = 0;
  virtual ~View() = 0;
};

#endif
