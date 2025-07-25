#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "observer.h"

class Subject {
    std::vector<Observer*> observers;

public:
    void attach(Observer* o);
    void detach(Observer* o);
    void notifyObserversCell(int r, int c, int change);
    void notifyObserversFull();
    virtual ~Subject() = default;
};

#endif
