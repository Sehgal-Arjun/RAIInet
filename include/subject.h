#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "observer.h"

class Subject {
    public:
        void attach(Observer* o);
        void detach(Observer* o);
        void notifyObservers();
        virtual ~Subject() = default;
        
    private:
    std::vector<Observer*> observers;
};

#endif
