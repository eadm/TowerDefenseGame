//
// Created by Руслан Давлетшин on 24/03/16.
//

#include "../../include/algo/Paths.h"

void getPaths(DIRECTION** paths, unsigned char** distances, char** map) {
    for (int i = 0; i < mapH; i++) {
        for (int j = 0; j < mapW; j ++) {
            if (j == 14 || j == 15) {
                if (j == 14 ) {
                    paths[i][j] = DIRECTION::RIGHT;
                    distances[i][j] = i + 1;
                } else {
                    paths[i][j] = DIRECTION::UP;
                    distances[i][j] = i;
                }
            } else paths[i][j] = DIRECTION::NONE;
        }
    }
    for (int i = 0; i < 15; i++) {
        paths[15][i] = DIRECTION::RIGHT;
        distances[15][i] = 30 - i;
    }
}