//
// Created by Руслан Давлетшин on 24/03/16.
//

#include "../../include/level/Level.h"

Level::Level(String name, char** map) : window(VideoMode(windowX, windowY), name) {
    init();
    initWindow();
    this->map = map;
    texture_manager = new TextureManager();
    getPaths(paths, distances, this->map);
}

Level::~Level() {
    for (size_t i = 0; i < mapH; i++) {
        delete [] map[i];
        delete [] paths[i];
        delete [] distances[i];
    }
    delete [] map;
    delete [] paths;
    delete [] distances;

    delete texture_manager;
}

void Level::init() { // выделяем память под наши массивы
    paths = (DIRECTION**) malloc(mapH * sizeof(DIRECTION*));
    distances = (unsigned char**) malloc(mapH * sizeof(unsigned char*));

    for (size_t i = 0; i < mapH; i++) {
        paths[i] = (DIRECTION*) malloc(mapW * sizeof(DIRECTION));
        distances[i] = (unsigned char*) malloc(mapW * sizeof(unsigned char));
    }
}

void Level::initWindow() {
    Image icon;
    if (!icon.loadFromFile("assets/Textures/icon.png")) {
        return;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    rectangle.setSize(Vector2f(tileW, tileH));
    window.setFramerateLimit(FPS_LIMIT);
}

void Level::start() {
    Font font;
    if (!font.loadFromFile("assets/Fonts/sansation.ttf")) {
        return;
//        return EXIT_FAILURE;
    }
    Text text("", font, 20);
    text.setColor(Color::White);

    Vector2i hoveredTile(-1, -1);

    while (window.isOpen()) {

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

        time /= 1000; // slowing the time

        // Process events
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::MouseButtonPressed) { // press
                Vector2i pos = getTile(event.mouseButton.x, event.mouseButton.y);

                if (map[pos.y][pos.x] == 'A' && money >= canon_price) {
                    money -= canon_price;
                    map[pos.y][pos.x] = 'C';
                    canons.push_back(Canon(pos.x, pos.y, texture_manager, &enemies));
                }

                if (map[pos.y][pos.x] == ' ') {
                    enemies.push_back(new Plane(pos.x, pos.y, texture_manager, distances, paths));
                }
            }

            if (event.type == Event::MouseMoved) {
                hoveredTile = getTile(event.mouseMove.x, event.mouseMove.y);
            }



            // Close window: exit
            if (event.type == Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                window.close();
            }
        }

        window.clear(Color(243, 255, 226));

        drawMap(hoveredTile);
        drawEnemies(time);
        drawCanons(time);

        text.setPosition(0, 0);
        text.setString("FPS: " + std::to_string(1000.0/time));
        window.draw(text);

        text.setPosition(0, 22);
        text.setString("Money: " + std::to_string(money));
        window.draw(text);

        window.display();
    }
}

void Level::drawMap(Vector2i hoveredTile) {
    for (int i = 0; i < mapH; i++) { // draw map
        for (int j = 0; j < mapW; j++) {
            switch (map[i][j]) {
                case 'B':
                    rectangle.setFillColor(LevelColors::B);
                    break;
                case 'X':
                    rectangle.setFillColor(LevelColors::X);
                    break;

                case 'C':
                    rectangle.setFillColor(LevelColors::C);
                    break;
                case 'A':
                    if (hoveredTile.x == j && hoveredTile.y == i) {
                        rectangle.setFillColor(LevelColors::H);
                    } else {
                        rectangle.setFillColor(LevelColors::C);
                    }
                    break;
                default:
                    continue;
                    break;
            }
            rectangle.setPosition(j * tileW, i * tileH);
            window.draw(rectangle);
        }
    }
}

void Level::drawEnemies(float time) {
    for (long i = enemies.size() - 1; i >= 0 ; i--) {
        if (enemies[i]->isDead()) {
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
            money += enemy_price;
            // RECYCLE
        } else {
            enemies[i]->update(time);
            window.draw(enemies[i]->sprite_body);
            for (size_t j = 0; j < enemies[i]->bullets->size(); j ++) {
                window.draw(enemies[i]->bullets->at(j)->sprite_body);
            }
        }
    }
}

void Level::drawCanons(float time) {
    for (size_t i = 0; i < canons.size(); i++) {
        canons[i].update(time);

        window.draw(canons[i].sprite_body);
        window.draw(canons[i].sprite_barrel);
    }
}