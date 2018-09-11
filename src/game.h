#ifndef STACK_GAME_H
#define STACK_GAME_H

#include "util.h"
#include <string>
#include "block.h"
#include "color.h"
#include <vector>
#include <thread>

using namespace std;

#define SIZE_OF_TABLE 50
#define SIZE 20

static int speed;
static bool stop;
static vector<Block> arrBlock;
static bool gameOver;
static int indexColor;

class Game {
public:
    static void getInput();
    static void init();
    static void printBlocks(int top);
    static void start();
    static void runLR();
    static void goLeft(Block &block, int top);
    static void goRight(Block &block, int top);
    static bool removeExcess(Block &block);
    static bool insertBlock(Block &block);
};

#endif //STACK_GAME_H
