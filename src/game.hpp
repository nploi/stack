#ifndef STACK_GAME_H
#define STACK_GAME_H

#include "block.hpp"
#include "drawer.hpp"

using namespace std;

#define SIZE_OF_TABLE 50
#define SIZE_BLOCK 20
#define FILE_NAME ".score.txt"
#define MID 15
#define SPACE 32
#define ESC 27

static int speed;
static bool stop;
static bool started;
static vector<Block> arrBlock;
static bool gameOver;
static int indexColor;
static bool returnMenu;
static long bestScore;
static long score;
static long counter;

class Game {
public:
    static void menu();
    static void save();
    static int getBestScore();
    static bool isContinue();
    static void getInput();
    static void init();
    static void printBlocks(int top);
    static void start();
    static void logic();
    static void goLeft(Block &block, int top);
    static void goRight(Block &block, int top);
    static bool removeExcess(Block &block);
    static bool insertBlock(Block &block);
};

#endif //STACK_GAME_H
