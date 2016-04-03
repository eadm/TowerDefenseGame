//
// Created by Руслан Давлетшин on 02/04/16.
//

#ifndef TOWERDEFENCEGAME_SIZESETTINGS_H
#define TOWERDEFENCEGAME_SIZESETTINGS_H

//#include "iostream"
#include <string>
#include "Sizes.h"

struct SizeSettings {
    unsigned int const windowX, windowY;
    unsigned int const tileH, tileW;
    unsigned int const font;
    float const multiplier;
    std::string const prefix;

    SizeSettings(unsigned int wX, unsigned int wY, unsigned int f, float m, std::string prefix);
};

namespace Settings {
    static const SizeSettings S_48(48 * mapH, 48 * mapW, 30, 1.0, "48");
    static const SizeSettings S_32(32 * mapH, 32 * mapW, 24, 1.5, "32");
    static const SizeSettings S_24(24 * mapH, 24 * mapW, 16, 2.0, "24");


};

extern SizeSettings const * CURRENT_SIZES;

//static extern SizeSettings const * CURRENT_SIZES;

#endif //TOWERDEFENCEGAME_SIZESETTINGS_H
