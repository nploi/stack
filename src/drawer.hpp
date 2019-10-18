#ifndef STACK_DRAWER_H
#define STACK_DRAWER_H

#include "util.hpp"
#include "color.hpp"

class Drawer {
public:
    static void menu(int x, int y);
    static void scores(int x, int y, long score, long bestScore);
    static void help(int x, int y);
};


#endif //STACK_DRAWER_H
