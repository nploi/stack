#ifndef STACK_UTIL_H
#define STACK_UTIL_H
#include <iostream>
#include <time.h>       /* time */
#include <stdlib.h>     /* srand, rand */

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <unistd.h>
    #include <termios.h>
#endif

namespace util {
    void gotoxy(int x, int y);
    void getchar(char &c);
    int random(int a, int b);
};

#endif //STACK_UTIL_H
