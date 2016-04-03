//
// Created by Руслан Давлетшин on 24/03/16.
//

#include "../../../include/objects/enemies/Enemy.h"

const Vector2i getTile(int x, int y) {
    return Vector2i(x / CURRENT_SIZES->tileW, y / CURRENT_SIZES->tileH);
}

Enemy::Enemy(int dx, int dy, TextureManager* texture_manager, Texture& texture_body, unsigned char** distances, DIRECTION** paths) : GraphicObject(texture_body) {
    sprite_body.setTextureRect(IntRect(0, 0, CURRENT_SIZES->tileW, CURRENT_SIZES->tileH));
    sprite_body.setPosition((dx + 0.5f) * CURRENT_SIZES->tileW, (dy + 0.5f) * CURRENT_SIZES->tileH);
    sprite_body.setOrigin(CURRENT_SIZES->tileW / 2, CURRENT_SIZES->tileH / 2);

    this->distances = distances;
    this->paths = paths;
    this->texture_manager = texture_manager;

    this->bullets = new std::vector<Bullet*>();
}

Enemy::~Enemy() {
    delete this->bullets;
}

unsigned char Enemy::getDistanceToExit() {
    Vector2f pos = sprite_body.getPosition();
    Vector2i posTile = getTile(pos.x, pos.y);

    if (posTile.x < 0 || posTile.x >= mapW || posTile.y < 0 || posTile.y >= mapH) { // если мы выехали за карту
        health = 0;
        potential_health = 0;
        return static_cast<char>(mapW * mapH);
    }

    return distances[posTile.y][posTile.x];
}

bool Enemy::isTarget() { return potential_health > 0; }
bool Enemy::isDead() { return health <= 0; }

void Enemy::rotate(float target_alpha, float time) {
    float cur_alpha = sprite_body.getRotation();
    float dif_alpha = std::abs(cur_alpha - target_alpha);

    if (dif_alpha > alpha_velocity * time) {
        sprite_body.rotate(getDirection(cur_alpha, dif_alpha, target_alpha) * alpha_velocity * time);
    } else {
        sprite_body.setRotation(target_alpha);
    }
}

void Enemy::addBullet(Vector2f start) {
    Bullet* b = new Bullet(start, this, texture_manager);
    potential_health -= b->damage;
    bullets->push_back(b);
}

void Enemy::update(float time) {
    Vector2f pos = sprite_body.getPosition();
    Vector2i posTile = getTile(pos.x, pos.y);


    if (std::abs(pos.x - (posTile.x + 0.5) * CURRENT_SIZES->tileW) <= std::abs(velocityX) * time &&
        std::abs(pos.y - (posTile.y + 0.5) * CURRENT_SIZES->tileH) <= std::abs(velocityY) * time) {
        sprite_body.setPosition((posTile.x + 0.5f) * CURRENT_SIZES->tileW, (posTile.y + 0.5f) * CURRENT_SIZES->tileH);

        velocityX = 0;
        velocityY = 0;

        switch (paths[posTile.y][posTile.x]) {
            case DIRECTION::UP:
                if (sprite_body.getRotation() == 0) {
                    velocityX = 0;
                    velocityY = -velocity;
                } else {
                    rotate(0, time);
                }
                break;

            case DIRECTION::DOWN:
                if (sprite_body.getRotation() == 180) {
                    velocityX = 0;
                    velocityY = velocity;
                } else {
                    rotate(180, time);
                }
                break;

            case DIRECTION::LEFT:
                if (sprite_body.getRotation() == 270) {
                    velocityX = -velocity;
                    velocityY = 0;
                } else {
                    rotate(270, time);
                }
                break;

            case DIRECTION::RIGHT:
                if (sprite_body.getRotation() == 90) {
                    velocityX = velocity;
                    velocityY = 0;
                } else {
                    rotate(90, time);
                }
                break;
            case DIRECTION::NONE:
                break;
        }
    }

    sprite_body.move(velocityX * time, velocityY * time);

    for (long i = bullets->size() - 1; i >= 0; i--) { // расчет полета пуль, летящих в танк
        if (bullets->at(i)->isReached()) {

            health -= bullets->at(i)->damage;

            delete (bullets->at(i));
            bullets->erase(bullets->begin() + i);
        } else {
            bullets->at(i)->update(time);
        }
    }

    if (health < 300) {
        sprite_body.setTextureRect(IntRect(2 * CURRENT_SIZES->tileW, 0, CURRENT_SIZES->tileW, CURRENT_SIZES->tileH));
    } else if (health < 600) {
        sprite_body.setTextureRect(IntRect(CURRENT_SIZES->tileW, 0, CURRENT_SIZES->tileW, CURRENT_SIZES->tileH));
    }
}

void Enemy::initHealth() {
    this->health = base_health;
    this->potential_health = base_health;
}