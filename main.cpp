
#include <iostream>
#include "src/game.h"
#include <clocale>

int main() {
	util::clear();
	Game::start();

#ifdef _WIN32
	system("pause");
#endif // _WIN32
    return 0;
}