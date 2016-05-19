//
// Created by Руслан Давлетшин on 24/03/16.
//

#ifndef CPHW_TD_READER_H
#define CPHW_TD_READER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <queue>
#include "../constants/Sizes.h"
#include "../constants/Directions.h"

using namespace std;

/**
 * Reads level from file
 */
char** readLevel(string name, sf::Vector2i& enter);

/**
 * Reads paths from file
 */
DIRECTION** readPaths(string name);

/**
 * Reads waves from file
 */
queue<queue<int>> readWaves(string name);

#endif //CPHW_TD_READER_H
