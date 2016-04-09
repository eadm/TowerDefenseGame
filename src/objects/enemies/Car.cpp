//
// Created by Руслан Давлетшин on 07/04/16.
//

#include "../../../include/objects/enemies/Car.h"

Car::Car(int dx, int dy, TextureManager* texture_manager, unsigned char** distances, DIRECTION** paths) :
        Enemy(dx, dy, texture_manager->texture_car_body, distances, paths, 100, GROUND) {
    this->base_health = 250;
    this->velocity = (float) 0.075 / CURRENT_SIZES->multiplier;
    this->initHealth();
}