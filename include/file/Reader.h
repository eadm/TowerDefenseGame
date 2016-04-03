//
// Created by Руслан Давлетшин on 24/03/16.
//

#ifndef CPHW_TD_READER_H
#define CPHW_TD_READER_H

#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../constants/Sizes.h"
#include "../constants/Directions.h"

char** readLevel(std::string name, sf::Vector2i& enter);
DIRECTION** readPaths(std::string name);
int** readWaves(std::string name, int& waves_count);

#endif //CPHW_TD_READER_H
