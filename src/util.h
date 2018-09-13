#ifndef STACK_UTIL_H
#define STACK_UTIL_H

#include <iostream>
#include <time.h>       /* time */
#include <stdlib.h>     /* srand, rand */
#include <string>
#include <iomanip>
#include <limits>
#include <chrono>
#include <vector>
#include <thread>
#include <fstream>

#ifdef _WIN32
    #include <windows.h>
	#include <conio.h>
#else
    #include <unistd.h>
    #include <unistd.h>
    #include <termios.h>
#endif


namespace util {
    void gotoxy(int x, int y);
    void getchar(char &c);
    int random(int a, int b);
    void sleep(int miliseconds);
	void clear();
	void remove(int x, int y);
};

#endif //STACK_UTIL_H
