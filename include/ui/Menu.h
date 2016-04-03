//
// Created by Руслан Давлетшин on 02/04/16.
//

#ifndef TOWERDEFENCEGAME_MENU_H
#define TOWERDEFENCEGAME_MENU_H

#include <string>
#include <SFML/Graphics.hpp>
#include "../constants/SizeSettings.h"
#include "../level/Level.h"
#include "../file/Reader.h"

using namespace sf;

bool contains(RectangleShape &rect, Vector2f &pos);

class Menu {
public:
    Menu();

    void start();
private:
    RenderWindow window;

    const static unsigned int wX = 400;
    const static unsigned int wY = 300;

    const String fields[2] = {"Resolution", "Level "};
    const int sizes[2] = {3, 1};
    int positions[2] = {0, 0};
    const String values[2][3] = {{"1536x1536", "1024x1024", "768x768"}, {"01"}};
    const String start_button = "Start";
};

#endif //TOWERDEFENCEGAME_MENU_H
