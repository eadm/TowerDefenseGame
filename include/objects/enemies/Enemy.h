//
// Created by Руслан Давлетшин on 24/03/16.
//

#ifndef CPHW_TD_ENEMY_H
#define CPHW_TD_ENEMY_H

#include "../GraphicObject.h"
#include "../TextureManager.h"
#include "../../constants/Directions.h"
#include "../../constants/SizeSettings.h"

#ifndef GET_TILE
#define GET_TILE

const Vector2i getTile(float x, float y);
#endif

class Bullet;

#include "../Bullet.h"

enum EnemyType {
    MIXED = 0,
    GROUND = 1,
    AIR = 2
};

class Enemy : public GraphicObject {
public:
    /**
     * Creates new enemy at position dx dy
     */
    Enemy(int dx, int dy, Texture& texture_body, unsigned char** distances, DIRECTION** paths,
          const unsigned int c = 0, EnemyType e = GROUND);
    /**
     * Creates new enemy from another enemy. New one will be copy of given one.
     */
    Enemy(int dx, int dy, Enemy const&);

    /**
     * Destructs object and cleans memory
     */
    ~Enemy();

    /**
     * Counts distance from current object to map exit
     */
    unsigned char getDistanceToExit();

    /**
     * Returns true if potential health above 0
     */
    bool isTarget();

    /**
     * Returns true if health below or equal 0
     */
    bool isDead();

    /**
     * Constant represents EnemyType of current object
     */
    const EnemyType enemyType;

    /**
     * Recount all physics with given time
     */
    void update(float time);

    /**
     * Adds a bullet flying to current object
     */
    void addBullet(Bullet*);

    /**
     * Constant represents price of current EnemyType
     */
    const unsigned int price;

    /**
     * Vector of bullets flying to current object
     */
    vector<Bullet*>* bullets;
private:
    void init(int dx, int dy);

    float const alpha_velocity = 0.5;
    int health,potential_health;

    float velocityX = 0, velocityY = 0;

    void rotate(float target_alpha, float time);

    unsigned char** distances;
    DIRECTION** paths;
protected:
    void initHealth();

    float velocity = .05;
    int base_health = 1000;
};


#endif //CPHW_TD_ENEMY_H
