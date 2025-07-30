#include "../include/subject.h"
#include <algorithm>

void Subject::attach(View* o) {
    observers.push_back(o);
}

void Subject::detach(View* o) {
    observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end()); // erase-remove
}

void Subject::notifyObserversFull() {
    for (View* o : observers) {
        if (o) o->notifyFull();
    }
}
