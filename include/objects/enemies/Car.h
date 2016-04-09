//
// Created by Руслан Давлетшин on 07/04/16.
//

#ifndef TOWERDEFENCEGAME_CAR_H
#define TOWERDEFENCEGAME_CAR_H

#include "Enemy.h"

class Car : public Enemy {
public:
    Car(int dx, int dy, TextureManager* texture_manager, unsigned char** distances, DIRECTION** paths);
};

#endif //TOWERDEFENCEGAME_CAR_H
