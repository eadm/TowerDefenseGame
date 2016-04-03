//
// Created by Руслан Давлетшин on 02/04/16.
//

#include "../../include/constants/SizeSettings.h"

SizeSettings::SizeSettings(unsigned int wX, unsigned int wY, unsigned int f, float m, std::string p):
        windowX(wX), windowY(wY), tileH(windowY / mapH), tileW(windowX / mapH - 2), multiplier(m), font(f), prefix(p) { }

SizeSettings const * CURRENT_SIZES = &Settings::S_48;