//
// Created by Руслан Давлетшин on 24/03/16.
//

#include "../../include/file/Reader.h"

char** readLevel(std::string name, sf::Vector2i& enter) {
    std::ifstream file(name);
    std::string str;
    char** map = (char**) malloc(sizeof(char*) * mapH);

    std::getline(file, str);
    for (int i = 0; i < mapH; i++, std::getline(file, str)) {
        map[i] = (char*) malloc(sizeof(char) * mapW);
        for (int j = 0; j < mapW; j++) {
            map[i][j] = str[j];
            if (map[i][j] == 'E') {
                enter.x = j;
                enter.y = i;
            }
        }
    }

    return map;
}

int** readWaves(std::string name, int& waves_count) {
    std::ifstream file(name);
//    std::string str;

    file >> waves_count;
    int** waves = (int**) malloc(sizeof(int*) * waves_count);
    for (size_t i = 0; i < waves_count; ++i) {
        waves[i] = (int*) malloc(sizeof(int) * 2);
        file >> waves[i][0] >> waves[i][1];
    }
    return waves;
}

DIRECTION** readPaths(std::string name) {
    std::ifstream file(name);
    std::string str;
    DIRECTION** paths = (DIRECTION**) malloc(sizeof(DIRECTION*) * mapH);
    std::getline(file, str);
    for (size_t i = 0; i < mapH; i++, std::getline(file, str)) {
        paths[i] = (DIRECTION*) malloc(sizeof(DIRECTION) * mapW);
        for (size_t j = 0; j < mapW; j++) {
            switch (str[j]) {
                case 'U':
                    paths[i][j] = DIRECTION::UP;
                    break;
                case 'D':
                    paths[i][j] = DIRECTION::DOWN;
                    break;
                case 'R':
                    paths[i][j] = DIRECTION::RIGHT;
                    break;
                case 'L':
                    paths[i][j] = DIRECTION::LEFT;
                    break;
                default:
                    paths[i][j] = DIRECTION::NONE;
            }
        }
    }
    return paths;
}