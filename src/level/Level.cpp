//
// Created by Руслан Давлетшин on 24/03/16.
//

#include "../../include/level/Level.h"

Level::Level(string name) :
        window(VideoMode(CURRENT_SIZES->windowX, CURRENT_SIZES->windowY), name, Style::Titlebar | Style::Close),
        waves(readWaves("assets/Levels/" + name + "/waves")) {

    initWindow();
    this->map = readLevel("assets/Levels/" + name + "/map", this->enter);
    this->ground_paths = readPaths("assets/Levels/" + name + "/paths");
    this->air_paths = readPaths("assets/Levels/" + name + "/paths2");
    texture_manager = new TextureManager();

    init();

    available_canons = (Canon**) malloc(sizeof(Canon*) * 2);
    available_canons[0] = Canon::fromFile(-1, -1, texture_manager, &enemies, "assets/Objects/Canons/ground");
    available_canons[1] = Canon::fromFile(-1, -1, texture_manager, &enemies, "assets/Objects/Canons/air");

    available_enemies = (Enemy**) malloc(sizeof(Enemy*) * 3);
    available_enemies[0] = new Car(-1, -1, texture_manager, distances, ground_paths);
    available_enemies[1] = new Panzer(-1, -1, texture_manager, distances, ground_paths);
    available_enemies[2] = new Plane(-1, -1, texture_manager, distances, air_paths);
}

Level::~Level() {
    for (size_t i = 0; i < mapH; i++) {
        delete [] map[i];
        delete [] ground_paths[i];
        delete [] air_paths[i];
        delete [] distances[i];
    }
    delete [] map;
    delete [] ground_paths;
    delete [] air_paths;
    delete [] distances;

    for (size_t i = 0; i < 2; ++i) {
        delete available_canons[i];
    }
    delete [] available_canons;

    for (size_t i = 0; i < 3; ++i) {
        delete available_enemies[i];
    }
    delete [] available_enemies;

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

void Level::start() {
    int multiplier = 1000;

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

        time /= multiplier; // slowing the time
        if (pause) time = 0;

        if (waves_cool_down <= time && !waves.empty()) {
            current_wave = waves.front();
            waves.pop();
            waves_cool_down = (int)current_wave.size() * enemy_base_cool_down + 10000;
        } else {
            waves_cool_down -= time;

            if (waves.empty() && current_wave.empty() && enemies.empty()) {
                succeed();
            }
        }

        if (enemy_cool_down <= time && !current_wave.empty()) {
            shared_ptr<Enemy> ptr(new Enemy(enter.x, enter.y, *available_enemies[current_wave.front()]));
            enemies.push_back(ptr);
            current_wave.pop();
            enemy_cool_down = enemy_base_cool_down;
        } else {
            enemy_cool_down -= time;
        }

        // Process events
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::MouseButtonPressed) { // press
                Vector2i pos = getTile(event.mouseButton.x, event.mouseButton.y);

                if (map[pos.y][pos.x] == 'A' &&
                        selected_canon != -1 &&
                        money >= available_canons[selected_canon]->price) { // Add a canon

                    money -= available_canons[selected_canon]->price;
                    map[pos.y][pos.x] = 'C';

                    canons.push_back(Canon(pos.x, pos.y, *available_canons[selected_canon]));
                }

//                if (map[pos.y][pos.x] == ' ') {
//                    enemies.push_back(new Panzer(pos.x, pos.y, texture_manager, distances, paths));
//                }
            }

            if (event.type == Event::MouseMoved) {
                hoveredTile = getTile(event.mouseMove.x, event.mouseMove.y);
            }

            if (event.type == Event::KeyPressed) {
                switch (event.key.code) {
                    case Keyboard::P: // pause on P
                        pause = !pause;
                        break;
                    case Keyboard::RBracket: // speed up on ]
                        multiplier = std::max(multiplier / 2, 250);
                        break;
                    case Keyboard::LBracket: // slow down on [
                        multiplier = std::min(multiplier * 2, 4000);
                        break;
                    case Keyboard::Num1:
                        selected_canon = 0;
                        break;
                    case Keyboard::Num2:
                        selected_canon = 1;
                        break;
                    default:
                        break;
                }
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

        text.setPosition(8, 2);
        text.setString("Money: " + std::to_string(money));
        window.draw(text);

        text.setPosition(text.getGlobalBounds().left + text.getGlobalBounds().width + 30, 2);
        text.setString("Wave: " + to_string(waves.size()));
        window.draw(text);

        text.setPosition(text.getGlobalBounds().left + text.getGlobalBounds().width + 30, 2);
        text.setString("Next in: " + std::to_string(waves_cool_down));
        window.draw(text);

        text.setPosition(text.getGlobalBounds().left + text.getGlobalBounds().width + 30, 2);
        text.setString("Lives: " + std::to_string(lives));
        window.draw(text);

        if (pause) drawHelper(text);

        window.display();
    }
}

void Level::drawHelper(Text& text) {
//    window.c
    RectangleShape rect;
    rect.setFillColor(Color(25, 52, 65, 220));
    rect.setSize(Vector2f(CURRENT_SIZES->windowX, CURRENT_SIZES->windowY));
    rect.setPosition(0, 0);
    window.draw(rect);

    rectangle.setFillColor(Color::White);
    drawButton(50, 50, text, "[", " - slow down time");
    drawButton(50, 120, text, "]", " - speed up time");
    drawButton(50, 190, text, "P", " - pause game");
    
    drawButton(50, 330, text, "1", " - canon for ground targets [price: " + to_string(available_canons[0]->price) + "]");
    drawButton(50, 400, text, "2", " - canon for air targets [price: " + to_string(available_canons[1]->price) + "]");


//    te
//    rect.set
//    window.clear(Color(243, 255, 226, 120));
    text.setOrigin(0, 0);
}

void Level::drawButton(float x, float y, Text &text, string button, string description) {
    rectangle.setPosition(x - CURRENT_SIZES->tileW / 2, y - CURRENT_SIZES->tileH / 2);
    window.draw(rectangle);

    text.setColor(Color::Black);
    text.setPosition(x, y);
    text.setString(button);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2 + 6 / CURRENT_SIZES->multiplier);
    window.draw(text);

    text.setColor(Color::White);
    text.setPosition(x + CURRENT_SIZES->tileW, y);
    text.setString(description);
    text.setOrigin(0, text.getGlobalBounds().height / 2 + 6 / CURRENT_SIZES->multiplier);
    window.draw(text);
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
            }
            rectangle.setPosition(j * CURRENT_SIZES->tileW, i * CURRENT_SIZES->tileH);
            window.draw(rectangle);

            if (hoveredTile.y >= 0 && hoveredTile.x >= 0 &&
                    map[hoveredTile.y][hoveredTile.x] == 'A' &&
                    selected_canon != -1) {
                if (getDistance(Vector2f(hoveredTile.x, hoveredTile.y), Vector2f(j, i)) <= available_canons[selected_canon]->radius) {
                    rectangle.setFillColor(LevelColors::HS);
                    window.draw(rectangle);
                }
            }
        }
    }
}

void Level::drawEnemies(float time) {
    for (auto it = enemies.rbegin(); it != enemies.rend() ; ++it) {
        if ((*it)->isDead() || (*it)->getDistanceToExit() == 0) {
            if ((*it)->isDead()) {
                money += (*it)->price;
            } else {
                lives--;
                if (lives == 0) failed();
            }
            enemies.erase(next(it).base());
        } else {
            (*it)->update(time);
            window.draw((*it)->sprite_body);
            for (size_t j = 0; j < (*it)->bullets->size(); j ++) {
                window.draw((*it)->bullets->at(j)->sprite_body);
            }
        }
    }
}

void Level::drawCanons(float time) {
    for (auto &canon: canons) {
        canon.update(time);

        window.draw(canon.sprite_body);
        window.draw(canon.sprite_barrel);
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