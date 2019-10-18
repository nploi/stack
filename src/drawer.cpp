#include "drawer.hpp"

void Drawer::menu(int x, int y) {
    std::cout << bold << fg_default;
    // Util::gotoxy(x + 8, y++);
    // std::cout << "MENU";
    Util::gotoxy(x, y++);
    std::cout << "+------------+";
    Util::gotoxy(x, y++);
    std::cout << "|1. New game |";
    Util::gotoxy(x, y++);
    std::cout << "|2. Exit     |";
    Util::gotoxy(x, y++);
    std::cout << "+------------+";
    Util::gotoxy(x, y++);
    std::cout << ">> ";
}

void Drawer::scores(int x, int y, long score, long bestScore) {
    std::cout << bold;
#ifdef _WIN32
    Util::gotoxy(x, y++);
	std::cout << char(201) << std::string(12, char(205)) << char(187);
	Util::gotoxy(x, y++);
	std::cout << char(186) << "SCORE:      " << char(186);
	Util::gotoxy(x, y++);
    std::cout << char(186) << "BEST:       " << char(186);
	Util::gotoxy(x, y++);
	std::cout << char(200) << std::string(12, char(205)) << char(188);
#else
    Util::gotoxy(x, y++);
    std::cout << "╔════════════╗\n";
    Util::gotoxy(x, y++);
    std::cout << "║SCORE:      ║\n";
    Util::gotoxy(x, y++);
    std::cout << "║BEST:       ║\n";
    Util::gotoxy(x, y++);
    std::cout << "╚════════════╝\n";
#endif // _WIN32

    Util::gotoxy(x + 7, y - 3);
    std::cout << fg_default;
    std::cout << score << std::endl;
    Util::gotoxy(x + 7, y - 2);
    std::cout << bestScore << std::endl;
    std::cout << reset;
}

void Drawer::help(int x, int y) {
    std::cout << bold;
    Util::gotoxy(x - 1, y++);
    std::cout << "「SPACE」 play";
    Util::gotoxy(x - 1, y++);
    std::cout << "「ESC」   exit";
}
