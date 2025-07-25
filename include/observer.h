#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
public:
    virtual void notifyCell(int r, int c, int change) = 0;
    virtual void notifyFull() = 0;
    virtual ~Observer() = default;
};

#endif
