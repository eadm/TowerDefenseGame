//
// Created by Руслан Давлетшин on 24/03/16.
//

#include "../../include/objects/Canon.h"


Canon::Canon(int dx, int dy, TextureManager* tm, vector<Enemy*>* enemies, size_t c, EnemyType type,
             int r, int d, float velocity, int bullet_t, int body_t, int barrel_t):
        GraphicObject(tm->textures[body_t]),
        rect(dx, dy, CURRENT_SIZES->tileW, CURRENT_SIZES->tileH),
        texture_manager(tm),
        price(c),
        enemyType(type),
        enemies(enemies),
        radius(r),
        damage(d),
        bullet_texture(bullet_t),
        bullet_velocity(velocity) {
    init(dx, dy, texture_manager->textures[barrel_t]);
}

Canon* Canon::fromFile(int x, int y, TextureManager* tm, vector<Enemy*>* enemies, string name) {
    ifstream file(name);

    int enemy_type;
    (file >> enemy_type).ignore(255, '\n');

    int radius;
    (file >> radius).ignore(255, '\n');

    size_t price;
    (file >> price).ignore(255, '\n');

    int body_texture;
    (file >> body_texture).ignore(255, '\n');

    int barrel_texture;
    (file >> barrel_texture).ignore(255, '\n');

    int bullet_texture;
    (file >> bullet_texture).ignore(255, '\n');

    int bullet_damage;
    (file >> bullet_damage).ignore(255, '\n');

    float bullet_velocity;
    (file >> bullet_velocity).ignore(255, '\n');

    Canon* canon = new Canon(x, y, tm, enemies,
                             price, static_cast<EnemyType>(enemy_type), radius,
                             bullet_damage, bullet_velocity, bullet_texture,
                             body_texture, barrel_texture);
    return canon;
}

Canon::Canon(int dx, int dy, Canon const & other):
        GraphicObject(*other.sprite_body.getTexture()),
        rect(dx, dy, CURRENT_SIZES->tileW, CURRENT_SIZES->tileH),
        texture_manager(other.texture_manager),
        price(other.price),
        enemyType(other.enemyType),
        enemies(other.enemies),
        radius(other.radius),
        damage(other.damage),
        bullet_texture(other.bullet_texture),
        bullet_velocity(other.bullet_velocity) {
    init(dx, dy, *other.sprite_barrel.getTexture());
}

void Canon::init(int dx, int dy, const Texture &barrel_texture) {
    sprite_body.setPosition(dx * CURRENT_SIZES->tileW, dy * CURRENT_SIZES->tileH);

    sprite_barrel.setTexture(barrel_texture);
    sprite_barrel.setPosition((dx + 0.5f) * CURRENT_SIZES->tileW, (dy + 0.5f) * CURRENT_SIZES->tileH);
    sprite_barrel.setOrigin(CURRENT_SIZES->tileW / 2, CURRENT_SIZES->tileH / 2);
    sprite_barrel.setRotation(alpha);
    sprite_barrel.setTextureRect(IntRect(0, 0, CURRENT_SIZES->tileW, CURRENT_SIZES->tileH));

    target = nullptr;
}

void Canon::setTarget(Enemy* target) {
    this->target = target;
}

void Canon::setAim(Vector2f aim) {
    if (getDistance(aim) > radius) return;

    float tmp_alpha = atan2f( aim.x - (rect.left + 0.5f) * CURRENT_SIZES->tileW, (rect.top + 0.5f) * CURRENT_SIZES->tileH - aim.y ) * 180 / PI;
    alpha = tmp_alpha > 0 ? tmp_alpha : 360.0f + tmp_alpha;
}

void Canon::shoot(Enemy* enemy) {
    if (enemy == nullptr) return;
    shoot_cool_down = base_shoot_cool_down;
    enemy->addBullet(new Bullet(sprite_barrel.getPosition(), enemy, texture_manager->textures[bullet_texture], damage, bullet_velocity));
}

void Canon::update(float time) {
    if (target != nullptr && (!target->isTarget() || getDistance(target->getPosition()) > radius)) {
        target = nullptr;
    }

    if (shoot_cool_down > time) {
        shoot_cool_down -= time;
    } else {
        shoot_cool_down = 0;
    }

    if (target != nullptr) {
        setAim(target->getPosition());


        float cur_alpha = sprite_barrel.getRotation();
        float dif_alpha = std::abs(cur_alpha - alpha);

        if (dif_alpha > alpha_velocity * time) { // поворачиваем дуло в сторону цели
            sprite_barrel.rotate(getDirection(cur_alpha, dif_alpha, alpha) * alpha_velocity * time);
        } else {
            sprite_barrel.setRotation(alpha);

            if (shoot_cool_down == 0) { // если мы смотрим в сторону цели и готовы стрелять - стреляем
                shoot(target);
            }
        }
    } else {
        chooseTarget();
    }
}

void Canon::chooseTarget() {
    Enemy* t = nullptr;
    for (size_t i = 0; i < enemies->size(); i++) {                          // ищем врага, который в нашем радиусе и ближе к выходу
        if ((enemyType == MIXED || enemies->at(i)->enemyType == enemyType)  // можем ли стрелять в этот тип врагов
            && enemies->at(i)->isTarget()                                   // жив ли враг
            && getDistance(enemies->at(i)->getPosition()) < radius) {       // достаем ли мы до врага
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

