//
// Created by Руслан Давлетшин on 24/03/16.
//

#ifndef CPHW_TD_CANON_H
#define CPHW_TD_CANON_H

#ifndef __SFML__
#define __SFML__
#include <SFML/Graphics.hpp>
#include "../constants/Sizes.h"

#include "GraphicObject.h"
#include <iostream>
#endif

#include "../file/Reader.h"

#ifndef __MATH__
#define __MATH__
#include <cmath>

#define PI 3.14159265
#endif

#include "enemies/Enemy.h"

using namespace sf;
using namespace std;

class Canon : public GraphicObject {
public:
    /**
     * Constant represent price of current canon type
     */
    const size_t price;


    const FloatRect rect;

    /**
     * Constant represents radius where canon could shoot targets
     */
    const int radius;

    /**
     * Sprite of current canon barrel
     */
    Sprite sprite_barrel;

    /**
     * Creates new canon object
     */
    Canon(int x, int y, TextureManager*, vector<shared_ptr<Enemy>>*,
          size_t price = 0,
          EnemyType = EnemyType::MIXED,
          int radius = 10,
          int damage = 30,
          float bullet_velocity = 0.005,
          int bullet_texture = 4,
          int body_texture = 0,
          int barrel_texture = 1);

    /**
     * Creates new canon object that takes its properties from given file
     */
    static Canon* fromFile(int x, int y, TextureManager*, vector<shared_ptr<Enemy>>*, string);

    /**
     * Creates new canon object that will be copy of given one
     */
    Canon(int x, int y, Canon const&);

    /**
     * Sets new target for current canon
     */
    void setTarget(weak_ptr<Enemy> target);

    /**
     * Rotate canon barrel towards to enemy
     */
    void setAim(Vector2f aim);

    /**
     * Shoot a bullet to specified enemy
     */
    void shoot(shared_ptr<Enemy> enemy);

    /**
     * Recount all physics with given time
     */
    void update(float time);
private:
    void init(int x, int y, const Texture& barrel_texture);

    const EnemyType enemyType;
    void chooseTarget();

    TextureManager *const texture_manager;

    const float alpha_velocity = 0.5;
    const float base_shoot_cool_down = 1000.0;

    float alpha = 0;
    float shoot_cool_down = 0.0;

    const int damage;
    const float bullet_velocity;
    const int bullet_texture;

    weak_ptr<Enemy> target_ptr;
    shared_ptr<Enemy> getTargetPtr();

    const vector<shared_ptr<Enemy>>* enemies;
};


#endif //CPHW_TD_CANON_H
