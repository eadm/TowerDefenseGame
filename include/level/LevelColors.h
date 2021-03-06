//
// Created by Руслан Давлетшин on 24/03/16.
//

#ifndef CPHW_TD_LEVELCOLORS_H
#define CPHW_TD_LEVELCOLORS_H

#ifndef __SFML__
#include <SFML/Graphics.hpp>
#endif

/**
 * Constants represents map colors
 */
namespace LevelColors {
    extern sf::Color
            B, // border
            X, // exit
            C, // canon
            H, // hovered
            HS; // hovered zone
}

#endif //CPHW_TD_LEVELCOLORS_H
