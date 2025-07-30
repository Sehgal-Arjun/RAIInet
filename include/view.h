#ifndef __DISPLAY_H__
#define __DISPLAY_H__
#include <iostream>

class View {
  public:
  virtual void notifyFull() = 0;
  virtual void print(std::ostream &out) = 0;
  virtual ~View() = 0;
};

#endif
