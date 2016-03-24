//
// Created by Руслан Давлетшин on 24/03/16.
//

#include "../../include/objects/TextureManager.h"

TextureManager::TextureManager() {
    texture_canon_body.loadFromFile("assets/Textures/canon.png");
    texture_canon_barrel.loadFromFile("assets/Textures/canon_barrel.png");
    texture_enemy_body.loadFromFile("assets/Textures/enemy.png");
    texture_bullet.loadFromFile("assets/Textures/bullet.png");
    texture_plane1_body.loadFromFile("assets/Textures/plane-1.png");
}