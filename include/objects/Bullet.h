//
// Created by Руслан Давлетшин on 24/03/16.
//

#ifndef CPHW_TD_BULLET_H
#define CPHW_TD_BULLET_H

class Enemy;

#include "enemies/Enemy.h"

class Bullet : public GraphicObject {
public:
    const int damage;

    Bullet(Vector2f start, Enemy* target, Texture& texture_body, int damage, float velocity);
    bool isReached();

    void update(float time);

private:
    void calculateSpeed();

    float getAlpha(Vector2f aim);

    float const velocity = 0.005;
    float velocityX = 0, velocityY = 0;
    float time_to_target = 0;

    Enemy* target;
};


#endif //CPHW_TD_BULLET_H
