//
// Created by Руслан Давлетшин on 24/03/16.
//

#include "../../include/objects/TextureManager.h"

TextureManager::TextureManager() {
    texture_canon_body.loadFromFile("assets/Textures/" + CURRENT_SIZES->prefix + "/canon.png");
    texture_canon_barrel.loadFromFile("assets/Textures/" + CURRENT_SIZES->prefix + "/canon_barrel.png");
    texture_panzer_body.loadFromFile("assets/Textures/" + CURRENT_SIZES->prefix + "/panzer.png");
    texture_car_body.loadFromFile("assets/Textures/" + CURRENT_SIZES->prefix + "/car.png");
    texture_bullet.loadFromFile("assets/Textures/" + CURRENT_SIZES->prefix + "/bullet.png");
    texture_plane1_body.loadFromFile("assets/Textures/" + CURRENT_SIZES->prefix + "/plane-1.png");

    textures[0] = texture_canon_body;
    textures[1] = texture_canon_barrel;
    textures[2] = texture_panzer_body;
    textures[3] = texture_car_body;
    textures[4] = texture_bullet;
    textures[5] = texture_plane1_body;
    textures[6].loadFromFile("assets/Textures/" + CURRENT_SIZES->prefix + "/canon_barrel_air.png");
}