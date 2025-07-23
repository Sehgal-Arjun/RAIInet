#ifndef LINKDECORATOR_H
#define LINKDECORATOR_H

#include "link.h"

class LinkDecorator : public Link {
protected:
    Link* next;
public:
    explicit LinkDecorator(Link* next);
    virtual ~LinkDecorator() = default;
};

#endif // LINKDECORATOR_H 