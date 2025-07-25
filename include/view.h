#ifndef __DISPLAY_H__
#define __DISPLAY_H__
#include <iostream>
#include "observer.h"

class View : public Observer {
  public:
  virtual void print(std::ostream &out) = 0;
  virtual ~View() = 0;
};

#endif
