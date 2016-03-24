//
// Created by Руслан Давлетшин on 24/03/16.
//

#ifndef CPHW_TD_ENEMY_H
#define CPHW_TD_ENEMY_H

#include "../GraphicObject.h"
#include "../TextureManager.h"
#include "../../constants/Directions.h"

#ifndef GET_TILE
#define GET_TILE

const Vector2i getTile(int x, int y);
#endif

class Bullet;

#include "../Bullet.h"

class Enemy : public GraphicObject {
public:

    Enemy(int dx, int dy, TextureManager* texture_manager, Texture& texture_body, unsigned char** distances, DIRECTION** paths);

    ~Enemy();
    unsigned char getDistanceToExit();

    bool isTarget();
    bool isDead();

    void update(float time);

    void addBullet(Vector2f start);

    std::vector<Bullet*>* bullets;
private:
    float const alpha_velocity = 0.5;
    int health,potential_health;

    float velocityX = 0, velocityY = 0;
    TextureManager* texture_manager;

    void rotate(float target_alpha, float time);

    unsigned char** distances;
    DIRECTION** paths;
protected:
    void initHealth();

    float velocity = .05;
    int base_health = 1000;
};


#endif //CPHW_TD_ENEMY_H
