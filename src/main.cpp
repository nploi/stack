
#include <iostream>
#include "game.hpp"
#include <clocale>

int main() {
    try {
        Game::init();
        Game::menu();
    } catch(...) {
        exit(1);
    }
    return 0;
}