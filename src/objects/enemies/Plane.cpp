//
// Created by Руслан Давлетшин on 24/03/16.
//

#include "../../../include/objects/enemies/Plane.h"

Plane::Plane(int dx, int dy, TextureManager* texture_manager, unsigned char** distances, DIRECTION** paths)
        : Enemy(dx, dy, texture_manager, texture_manager->texture_plane1_body, distances, paths) {
    this->base_health = 400;
    this->velocity = 0.15;
    this->initHealth();
}