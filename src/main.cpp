#include "../include/level/Level.h"
#include "../include/file/Reader.h"

int main(int, char const**) {
    char** map = readLevel("assets/Levels/01/map");
    Level* level = new Level("Level 1", map);
    level->start();
    delete level;
    return EXIT_SUCCESS;
}