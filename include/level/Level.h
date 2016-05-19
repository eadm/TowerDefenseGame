//
// Created by Руслан Давлетшин on 24/03/16.
//

#ifndef CPHW_TD_LEVEL_H
#define CPHW_TD_LEVEL_H

#include "../objects/Canon.h"
#include "../objects/enemies/Car.h"
#include "../objects/enemies/Panzer.h"
#include "../objects/enemies/Plane.h"
#include "../algo/Paths.h"
#include "LevelColors.h"
#include "../constants/SizeSettings.h"
#include "../ui/Menu.h"
#include <vector>
#include <queue>

using namespace std;

class Level {
public:
    /**
     * Creates new level with given name. Info about level will be loaded from files with name prefix.
     */
    Level(string name);

    ~Level();

    /**
     * Starts new level
     */
    void start();
private:
    const float getDistance(Vector2f a, Vector2f b);

    void failed();
    void succeed();

    bool pause = true;

    void init();
    void initWindow();

    RenderWindow window;
    Clock clock;

    RectangleShape rectangle;
    Vector2i enter;

    DIRECTION** ground_paths; // карта путей для танков
    DIRECTION** air_paths; // карта путей для самалётов
    unsigned char** distances; // карта с количеством квадратов до выхода
    char** map;

    size_t lives = 10;

    int waves_cool_down = 10000;
    const int enemy_base_cool_down = 1000;
    int enemy_cool_down = enemy_base_cool_down;

    queue<int> current_wave;
    queue<queue<int>> waves;

    TextureManager *texture_manager;

    void drawHelper(Text& text);
    void drawButton(float, float, Text& text, string, string);

    void drawMap(Vector2i hoveredTile);
    void drawEnemies(float time);
    void drawCanons(float time);

    vector<shared_ptr<Enemy>> enemies;
    vector<Canon> canons;

    long long money = 5000;

    Canon** available_canons; // templates of canons you can add
    int selected_canon = -1;
    Enemy** available_enemies; // templates of enemies

    size_t const FPS_LIMIT = 120;
};

#endif //CPHW_TD_LEVEL_H
