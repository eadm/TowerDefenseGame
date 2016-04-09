//
// Created by Руслан Давлетшин on 24/03/16.
//

#include "../../include/file/Reader.h"

char** readLevel(string name, sf::Vector2i& enter) {
    ifstream file(name);
    string str;
    char** map = (char**) malloc(sizeof(char*) * mapH);

    getline(file, str);
    for (int i = 0; i < mapH; i++, getline(file, str)) {
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

queue<queue<int>> readWaves(string name) {
    ifstream file(name);
    string str;
    int enemy;

    queue<queue<int>> waves;

    while (getline(file, str)) {
        queue<int> wave;
        stringstream ss(str);

        while (ss >> enemy) {
            wave.push(enemy);
        }
        waves.push(wave);
    }

    return waves;
}

DIRECTION** readPaths(string name) {
    ifstream file(name);
    string str;
    DIRECTION** paths = (DIRECTION**) malloc(sizeof(DIRECTION*) * mapH);
    getline(file, str);
    for (size_t i = 0; i < mapH; i++, getline(file, str)) {
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