//
// Created by Руслан Давлетшин on 02/04/16.
//

#ifndef TOWERDEFENCEGAME_SIZESETTINGS_H
#define TOWERDEFENCEGAME_SIZESETTINGS_H

#include <string>
#include "Sizes.h"

/**
 * Struct represents current sizes
 */
struct SizeSettings {
    /**
     * Sizes of window in pixels
     */
    unsigned int const windowX, windowY;

    /**
     * Sizes of tile
     */
    unsigned int const tileH, tileW;

    /**
     * Size of font
     */
    unsigned int const font;

    /**
     * Multiplier that slows object on smaller resolutions
     */
    float const multiplier;

    /**
     * Prefix for texture for selected size
     */
    std::string const prefix;

    SizeSettings(unsigned int wX, unsigned int wY, unsigned int f, float m, std::string prefix);
};

/**
 * Constants represents available resolutions
 */
namespace Settings {
    static const SizeSettings S_48(48 * (mapW), 48 * mapH, 30, 1.0, "48");
    static const SizeSettings S_32(32 * (mapW), 32 * mapH, 24, 1.5, "32");
    static const SizeSettings S_24(24 * (mapW), 24 * mapH, 16, 2.0, "24");
};

extern SizeSettings const * CURRENT_SIZES;

//static extern SizeSettings const * CURRENT_SIZES;

#endif //TOWERDEFENCEGAME_SIZESETTINGS_H
