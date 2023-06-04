#ifndef RUBIKCUBE_HELPINGFUNCTIONS_H
#define RUBIKCUBE_HELPINGFUNCTIONS_H
#include <iostream>
#include "../Rubik/RubikConfig.h"
using std::string, Colors::yellow, Colors::white, Colors::blue, Colors::green, Colors::orange, Colors::red;

int getRGB(const string& color) {
    if (color == "Y") {
        return yellow;
    } else if (color == "W") {
        return white;
    } else if (color == "B") {
        return blue;
    } else if (color == "G") {
        return green;
    } else if (color == "O") {
        return orange;
    } else if (color == "R") {
        return red;
    }
    return 0;
}

#endif //RUBIKCUBE_HELPINGFUNCTIONS_H
