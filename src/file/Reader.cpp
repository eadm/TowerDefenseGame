//
// Created by Руслан Давлетшин on 24/03/16.
//

#include "../../include/file/Reader.h"

char** readLevel(std::string name) {
    std::ifstream file(name);
    std::string str;
    char** map = (char**) malloc(sizeof(char*) * mapH);

    std::getline(file, str);
    for (size_t i = 0; i < mapH; i++, std::getline(file, str)) {
        map[i] = (char*) malloc(sizeof(char) * mapW);
        for (size_t j = 0; j < mapW; j++) {
            map[i][j] = str[j];
        }
    }

    return map;
}