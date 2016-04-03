//
// Created by Руслан Давлетшин on 24/03/16.
//

#ifndef CPHW_TD_LEVEL_H
#define CPHW_TD_LEVEL_H

#include "../objects/Canon.h"
#include "../objects/enemies/Panzer.h"
#include "../objects/enemies/Plane.h"
#include "../algo/Paths.h"
#include "LevelColors.h"
#include "../constants/SizeSettings.h"
#include "../ui/Menu.h"

class Level {
public:
    Level(String name);

    ~Level();

    void start();


private:
    const float getDistance(Vector2f a, Vector2f b);

    void failed();
    void succeed();

    bool pause = false;

    void init();
    void initWindow();

    RenderWindow window;
    Clock clock;

    RectangleShape rectangle;
    Vector2i enter;
//    Text text;

    DIRECTION** paths; // карта путей для танков
    DIRECTION** paths2; // карта путей для самалётов
    unsigned char** distances; // карта с количеством квадратов до выхода
    char** map;

    unsigned int lives = 10;

    int waves_count;
    int waves_cooldown = 10000;
    int current_wave = -1;
    const int enemy_base_cooldown = 1000;
    int enemy_cooldown_0 = enemy_base_cooldown;
    int enemy_cooldown_1 = enemy_base_cooldown;
    int** waves;

    void calcWaveCooldown(int& cooldown, float time, unsigned char type, DIRECTION**& paths);

    TextureManager *texture_manager;

    void drawMap(Vector2i hoveredTile);
    void drawEnemies(float time);
    void drawCanons(float time);

    std::vector<Enemy*> enemies;
    std::vector<Canon> canons;

    long long money = 5000;
    int const canon_price = 1000;
    int const enemy_price = 300;

    int const FPS_LIMIT = 120;
};

#endif //CPHW_TD_LEVEL_H
