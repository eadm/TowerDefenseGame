//
// Created by Руслан Давлетшин on 24/03/16.
//

#ifndef CPHW_TD_TEXTUREMANAGER_H
#define CPHW_TD_TEXTUREMANAGER_H

#ifndef __SFML__
#define __SFML__
#include <SFML/Graphics.hpp>
#include "../constants/Sizes.h"

#include "GraphicObject.h"
#include <iostream>
#endif

//#include "ResourcePath.hpp"

struct TextureManager {
    Texture texture_canon_body,
            texture_canon_barrel,
            texture_enemy_body,
            texture_bullet,
            texture_plane1_body;

    TextureManager();
};

#endif //CPHW_TD_TEXTUREMANAGER_H
