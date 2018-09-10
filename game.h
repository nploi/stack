#ifndef STACK_GAME_H
#define STACK_GAME_H

#include "util.h"
#include <string>
#include "block.h"
#include "color.h"
#include <vector>
#include <thread>

using namespace std;

static int speed;
static bool stop;
static bool pauseTemp;
static vector<Block> arrBlock;
static int score;
static bool gameOver;

class Game {
public:
    static void menu();
    static void getInput();
    static void init();
    static void printBlocks(int top);
    static void start();
    static void runLR();
    static bool removeExcess(Block &block);
    static bool insertBlock(Block &block);
};

#endif //STACK_GAME_H
