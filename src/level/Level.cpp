//
// Created by Руслан Давлетшин on 24/03/16.
//

#include "../../include/level/Level.h"

Level::Level(String name)
        : window(VideoMode(CURRENT_SIZES->windowX, CURRENT_SIZES->windowY), name, Style::Titlebar | Style::Close) {
    initWindow();
    this->map = readLevel("assets/Levels/" + name + "/map", this->enter);
    this->paths = readPaths("assets/Levels/" + name + "/paths");
    this->paths2 = readPaths("assets/Levels/" + name + "/paths2");
    this->waves = readWaves("assets/Levels/" + name + "/waves", this->waves_count);
    texture_manager = new TextureManager();
    init();
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

    for (size_t i = 0; i < waves_count; ++i) {
        delete [] waves[i];
    }
    delete [] waves;

    delete texture_manager;
}

void Level::init() { // выделяем память под наши массивы
    distances = (unsigned char**) malloc(mapH * sizeof(unsigned char*));

    for (size_t i = 0; i < mapH; i++) {
        distances[i] = (unsigned char*) malloc(mapW * sizeof(unsigned char));
        for (int j = 0; j < mapW; ++j) {
            if (map[i][j] == 'X') {
                distances[i][j] = 0;
            } else {
                distances[i][j] = 100;
            }
        }
    }
}

void Level::initWindow() {
    Image icon;
    if (!icon.loadFromFile("assets/Textures/icon.png")) {
        return;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    rectangle.setSize(Vector2f(CURRENT_SIZES->tileW, CURRENT_SIZES->tileH));
    window.setFramerateLimit(FPS_LIMIT);
}

void Level::calcWaveCooldown(int &cooldown, float time, unsigned char type, DIRECTION**& paths) {
    if (cooldown <= time && waves[current_wave][type] > 0) {
        if (type == 0) {
            enemies.push_back(new Panzer(enter.x, enter.y, texture_manager, distances, paths));
        } else {
            enemies.push_back(new Plane(enter.x, enter.y, texture_manager, distances, paths));
        }
        cooldown = enemy_base_cooldown;
        waves[current_wave][type]--;
    } else {
        cooldown -= time;
    }
}

void Level::start() {
    Font font;
    if (!font.loadFromFile("assets/Fonts/SF-UI-Text-Regular.otf")) {
        return;
    }
    Text text("", font, CURRENT_SIZES->font);
    text.setColor(Color::White);

    Vector2i hoveredTile(-1, -1);

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

        time /= 1000; // slowing the time
        if (pause) time = 0;

        if (waves_cooldown <= time && current_wave < waves_count - 1) {
            current_wave++;
            waves_cooldown = (waves[current_wave][0] + waves[current_wave][1]) * enemy_base_cooldown + 10000;
        } else {
            waves_cooldown -= time;
            if (current_wave == waves_count - 1 && enemies.size() == 0) succeed();
        }

        if (0 <= current_wave && current_wave < waves_count) {
            calcWaveCooldown(enemy_cooldown_0, time, 0, paths);
            calcWaveCooldown(enemy_cooldown_1, time, 1, paths2);
        }


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
                    enemies.push_back(new Panzer(pos.x, pos.y, texture_manager, distances, paths));
                }
            }

            if (event.type == Event::MouseMoved) {
                hoveredTile = getTile(event.mouseMove.x, event.mouseMove.y);
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::P) {
                pause = !pause;
            }

            // Escape pressed: exit
            if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) ||
                    event.type == Event::Closed) {
                window.close();
                Menu menu;
                menu.start();
            }
        }

        window.clear(Color(243, 255, 226));

        drawMap(hoveredTile);
        drawEnemies(time);
        drawCanons(time);

//        text.setPosition(0, 0);
//        text.setString("FPS: " + std::to_string(1000.0/time));
//        window.draw(text);

        text.setPosition(8, 2);
        text.setString("Money: " + std::to_string(money));
        window.draw(text);

        text.setPosition(text.getGlobalBounds().left + text.getGlobalBounds().width + 30, 2);
        text.setString("Wave: " + (current_wave > -1 ? std::to_string(current_wave) : "prepare"));
        window.draw(text);

        text.setPosition(text.getGlobalBounds().left + text.getGlobalBounds().width + 30, 2);
        text.setString("Next in: " + std::to_string(waves_cooldown));
        window.draw(text);

        text.setPosition(text.getGlobalBounds().left + text.getGlobalBounds().width + 30, 2);
        text.setString("Lives: " + std::to_string(lives));
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
                    rectangle.setFillColor(Color(243, 255, 226));
                    break;
//                    continue;
            }
            rectangle.setPosition(j * CURRENT_SIZES->tileW, i * CURRENT_SIZES->tileH);
            window.draw(rectangle);

            if (hoveredTile.y >= 0 && hoveredTile.x >= 0 && map[hoveredTile.y][hoveredTile.x] == 'A') {
                if (getDistance(Vector2f(hoveredTile.x, hoveredTile.y), Vector2f(j, i)) <= 10) {
                    rectangle.setFillColor(LevelColors::HS);
                    window.draw(rectangle);
                }
            }
        }
    }
}

void Level::drawEnemies(float time) {
    for (long i = enemies.size() - 1; i >= 0 ; i--) {
        if (enemies[i]->isDead() || enemies[i]->getDistanceToExit() == 0) {
            if (enemies[i]->isDead()) {
                money += enemy_price;
            } else {
                lives--;
                if (lives == 0) failed();
            }
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
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

const float Level::getDistance(Vector2f a, Vector2f b) {
    return sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2));
}

void Level::failed() {
    pause = true;
    std::cout << "Level failed" << std::endl;
}

void Level::succeed() {
    pause = true;
    std::cout << "Level succeed" << std::endl;
}