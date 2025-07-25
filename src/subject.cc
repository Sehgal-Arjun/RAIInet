#include "../include/subject.h"

void Subject::attach(Observer* o) {
    observers.push_back(o);
}

void Subject::detach(Observer* o) {
    observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end()); // erase-remove
}

void Subject::notifyObserversCell(int r, int c, int change) {
    for (Observer* o : observers) {
        if (o) o->notifyCell(r, c, change);
    }
}
void Subject::notifyObserversFull() {
    for (Observer* o : observers) {
        if (o) o->notifyFull();
    }
}
