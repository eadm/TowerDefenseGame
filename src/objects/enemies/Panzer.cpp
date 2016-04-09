//
// Created by Руслан Давлетшин on 24/03/16.
//

#include "../../../include/objects/enemies/Panzer.h"

Panzer::Panzer(int dx, int dy, TextureManager* texture_manager, unsigned char** distances, DIRECTION** paths) :
        Enemy(dx, dy, texture_manager->texture_panzer_body, distances, paths, 300, GROUND) {
    this->base_health = 1000;
    this->velocity = (float) 0.05 / CURRENT_SIZES->multiplier;
    this->initHealth();
}