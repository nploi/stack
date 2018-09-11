#include "util.h"

#ifdef _WIN32
    void util::gotoxy(int x, int y) {
        static HANDLE handle = NULL;
        if(!handle) {
            handle = GetStdHandle(STD_OUTPUT_HANDLE);
        }
        COORD coord = { x, y };
        SetConsoleCursorPosition(handle, coord);
    }
#else
char getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return (buf);
}
    void util::gotoxy(int x, int y) {
        printf("%c[%d;%df",0x1B,y,x);
    }
#endif


void util::getchar(char &c) {
#ifdef _WIN32
	c = _getch();
#else
    c = getch();
#endif
}

int util::random(int a, int b) {
    /* initialize random seed: */
    srand (time(NULL));
    /* generate secret number between 1 and 10: */
    return (rand() % b + a);
}

void util::sleep(int miliseconds)
{
#ifdef _WIN32
	Sleep(miliseconds);
#else
	usleep(miliseconds * 1000);
#endif // 

}

void util::clear()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif // _WIN32
}

void util::remove(int x, int y)
{
	gotoxy(x, y);
	std::cout << " ";
}

