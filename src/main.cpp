#include "../include/ui/Menu.h"

int main(int, char const**) {
    srand(static_cast<unsigned int>(time(0)));
    Menu menu;
    menu.start();
    return EXIT_SUCCESS;
}