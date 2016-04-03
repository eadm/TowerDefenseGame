//
// Created by Руслан Давлетшин on 24/03/16.
//

#include "../../include/objects/TextureManager.h"

TextureManager::TextureManager() {
    texture_canon_body.loadFromFile("assets/Textures/" + CURRENT_SIZES->prefix + "/canon.png");
    texture_canon_barrel.loadFromFile("assets/Textures/" + CURRENT_SIZES->prefix + "/canon_barrel.png");
    texture_enemy_body.loadFromFile("assets/Textures/" + CURRENT_SIZES->prefix + "/enemy.png");
    texture_bullet.loadFromFile("assets/Textures/" + CURRENT_SIZES->prefix + "/bullet.png");
    texture_plane1_body.loadFromFile("assets/Textures/" + CURRENT_SIZES->prefix + "/plane-1.png");
}