//
// Created by Руслан Давлетшин on 24/03/16.
//

#include "../../include/objects/Canon.h"


Canon::Canon(int dx, int dy, TextureManager* texture_manager, std::vector<Enemy*>* enemies)
        : GraphicObject(texture_manager->texture_canon_body), rect(dx, dy, tileW, tileH) {

    target = nullptr;

//    sprite_body.setTexture(canon_body);
    sprite_body.setPosition(dx * tileW, dy * tileH);

    sprite_barrel.setTexture(texture_manager->texture_canon_barrel);
    sprite_barrel.setPosition((dx + 0.5) * tileW, (dy + 0.5) * tileH);
    sprite_barrel.setOrigin(tileW / 2, tileH / 2);
    sprite_barrel.setRotation(alpha);
    sprite_barrel.setTextureRect(IntRect(0, 0, tileW, tileH));

    this->enemies = enemies;
    this->texture_manager = texture_manager;
}

void Canon::setTarget(Enemy* target) {
    this->target = target;
}

void Canon::setAim(Vector2f aim) {
    if (getDistance(aim) > radius) return;

    float tmp_aplpha = atan2( aim.x - (rect.left + 0.5) * tileW, (rect.top + 0.5) * tileH - aim.y ) * 180 / PI;
    alpha = tmp_aplpha > 0 ? tmp_aplpha : 360.0 + tmp_aplpha;
}

void Canon::shoot(Enemy* enemy) {
    if (enemy == nullptr) return;

    shoot_cooldown = base_shoot_cooldown;

    enemy->addBullet(sprite_barrel.getPosition());
}

void Canon::update(float time) {
    if (target != nullptr && (!target->isTarget() || getDistance(target->getPosition()) > radius)) {
        target = nullptr;
    }

//    if (shoot_cooldown > base_shoot_cooldown / 2) {
//        sprite_barrel.setTextureRect(IntRect(tileW, 0, tileW, tileH));
//    } else {
//        sprite_barrel.setTextureRect(IntRect(2 * tileW, 0, tileW, tileH));
//    }

    if (shoot_cooldown > time) {
        shoot_cooldown -= time;
    } else {
        shoot_cooldown = 0;
    }

    if (target != nullptr) {
        setAim(target->getPosition());


        float cur_alpha = sprite_barrel.getRotation();
        float dif_alpha = std::abs(cur_alpha - alpha);

        if (dif_alpha > alpha_velocity * time) { // поворачиваем дуло в сторону цели
            sprite_barrel.rotate(getDirection(cur_alpha, dif_alpha, alpha) * alpha_velocity * time);
        } else {
            sprite_barrel.setRotation(alpha);

            if (shoot_cooldown == 0) { // если мы смотрим в сторону цели и готовы стрелять - стреляем
                shoot(target);
            }
        }
    } else {
        chooseTarget();
    }
}

void Canon::chooseTarget() {
    Enemy* t = nullptr;
    for (size_t i = 0; i < enemies->size(); i++) { // ищем врага, который в нашем радиусе и ближе к выходу
        if (enemies->at(i)->isTarget() && getDistance(enemies->at(i)->getPosition()) < radius) {
            if (t == nullptr) {
                t = enemies->at(i);
            } else {
                if (t->getDistanceToExit() > enemies->at(i)->getDistanceToExit()) {
                    t = enemies->at(i);
                }
            }
        }
    }
    setTarget(t);
}

