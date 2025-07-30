#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "view.h"

class Subject {
    std::vector<View*> observers;

public:
    void attach(View* o);
    void detach(View* o);
    void notifyObserversFull();
    virtual ~Subject() = default;
};

#endif
