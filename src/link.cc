#include "../include/link.h"
#include "../include/basiclink.h"
#include <string>

using namespace std;

string Link::makeString() {
    LinkType type = getLinkType();
    string strength = std::to_string(getStrength());
    if (type == LinkType::DATA){
        return "D" + strength;
    }
    else if (type == LinkType::VIRUS){
        return "V" + strength;
    }
    else {
        return "Error: Unrecognised LinkType";
    }
}
