//
// Created by Руслан Давлетшин on 24/03/16.
//

#ifndef CPHW_TD_BULLET_H
#define CPHW_TD_BULLET_H

class Enemy;

#include "enemies/Enemy.h"

class Bullet : public GraphicObject {
public:
    /**
     * Constant represents damage will be dealed to target
     */
    const int damage;

    /**
     * Creates new bullet that flyes from start to given target with specified velocity and deals specified damage
     */
    Bullet(Vector2f start, shared_ptr<Enemy> target, Texture& texture_body, int damage, float velocity);

    /**
     * Returns true if bullet reached target
     */
    bool isReached();

    /**
     * Recount all physics with given time
     */
    void update(float time);

private:
    void calculateSpeed();

    float getAlpha(Vector2f aim);

    float const velocity = 0.005;
    float velocityX = 0, velocityY = 0;
    float time_to_target = 0;

    weak_ptr<Enemy> target_ptr;
};


#endif //CPHW_TD_BULLET_H
