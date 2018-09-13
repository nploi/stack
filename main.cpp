
#include <iostream>
#include "src/game.h"
#include <clocale>

int main() {
    util::clear();
    Game::init();
    Game::menu();
    return 0;
}