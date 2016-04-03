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
    Level(String name, char** map);

    ~Level();

    void start();


private:
    void init();
    void initWindow();

    RenderWindow window;
    Clock clock;

    RectangleShape rectangle;
//    Text text;

    DIRECTION** paths; // карта путей для врагов
    unsigned char** distances; // карта с количеством квадратов до выхода
    char** map;

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
