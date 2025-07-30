#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include "ability.h"

class Download: public LinkPlayerAbility {
public:
    Download(int id);
    void apply(Link& l, Player& p) override;
    bool isValid(Link* l, Player* p) const override;
};

#endif // DOWNLOAD_H
