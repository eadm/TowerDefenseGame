//
// Created by Руслан Давлетшин on 24/03/16.
//

#include "../../include/objects/Bullet.h"

Bullet::Bullet(Vector2f start, shared_ptr<Enemy> target, Texture& texture_body, int d, float v) :
        GraphicObject(texture_body),
        damage(std::max(rand() % d, 10)),
        velocity(v) {
    this->target_ptr = target;
    sprite_body.setPosition(start);
    sprite_body.setOrigin(4, 8);
}

bool Bullet::isReached() {
    if (auto target = target_ptr.lock()) {
        Vector2f c_pos = getPosition();
        Vector2f t_pos = target->getPosition();

        return (std::abs(c_pos.x - t_pos.x) <= CURRENT_SIZES->tileW / 2) && (std::abs(c_pos.y - t_pos.y) <= CURRENT_SIZES->tileH / 2);
    } else {
        return true;
    }
}

void Bullet::update(float time) {
    if (!isReached()) {
        calculateSpeed();
        sprite_body.setRotation(getAlpha(target_ptr.lock()->getPosition()));
        sprite_body.move(velocityX * time, velocityY * time);
    }
}

void Bullet::calculateSpeed() {
    Vector2f c_pos = getPosition();
    Vector2f t_pos = target_ptr.lock()->getPosition();

    time_to_target = getDistance(t_pos) / (velocity / CURRENT_SIZES->multiplier); // slow if in small resolution
    velocityX = (t_pos.x - c_pos.x) / time_to_target;
    velocityY = (t_pos.y - c_pos.y) / time_to_target;
}

float Bullet::getAlpha(Vector2f aim) {
    Vector2f c_pos = getPosition();

    float tmp_alpha = atan2f( aim.x - c_pos.x, c_pos.y - aim.y ) * 180 / PI;
    return tmp_alpha > 0 ? tmp_alpha : 360.0f + tmp_alpha;
}