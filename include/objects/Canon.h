//
// Created by Руслан Давлетшин on 24/03/16.
//

#ifndef CPHW_TD_CANON_H
#define CPHW_TD_CANON_H

#ifndef __SFML__
#define __SFML__
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../constants/Sizes.h"

#include "GraphicObject.h"
#include <iostream>
#endif


#ifndef __MATH__
#define __MATH__
#include <cmath>

#define PI 3.14159265
#endif

#include "enemies/Enemy.h"

using namespace sf;

class Canon : public GraphicObject {
public:
    FloatRect rect;
    Sprite sprite_barrel;
    const TextureManager* texture_manager;

    Canon(int dx, int dy, TextureManager* texture_manager, std::vector<Enemy*>* enemies);

    void setTarget(Enemy* target);

    void setAim(Vector2f aim);

    void shoot(Enemy* enemy);

    void update(float time);

private:
    void chooseTarget();

    int const radius = 10;
    float const alpha_velocity = 0.5;
    float const base_shoot_cooldown = 1000.0;

    float alpha = 0;
    float shoot_cooldown = 0.0;

    Enemy* target;

    std::vector<Enemy*>* enemies;
};


#endif //CPHW_TD_CANON_H
