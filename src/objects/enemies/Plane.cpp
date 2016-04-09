//
// Created by Руслан Давлетшин on 24/03/16.
//

#include "../../../include/objects/enemies/Plane.h"

Plane::Plane(int dx, int dy, TextureManager* texture_manager, unsigned char** distances, DIRECTION** paths)
        : Enemy(dx, dy, texture_manager->texture_plane1_body, distances, paths, 500, AIR) {
    this->base_health = 400;
    this->velocity = (float) 0.15 / CURRENT_SIZES->multiplier;
    this->initHealth();
}