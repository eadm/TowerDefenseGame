//
// Created by Руслан Давлетшин on 24/03/16.
//

#include "../../../include/objects/enemies/Panzer.h"

Panzer::Panzer(int dx, int dy, TextureManager* texture_manager, unsigned char** distances, DIRECTION** paths) :
        Enemy(dx, dy, texture_manager, texture_manager->texture_enemy_body, distances, paths) {
    this->base_health = 1000;
    this->velocity = 0.05;
    this->initHealth();
}