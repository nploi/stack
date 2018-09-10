
#include <iostream>
#include "game.h"

bool r(Block &block, Block &block1) {
//    int size = arrBlock.size();
//
//    if(size <= 1) {
//        return false;
//    }
//    util::gotoxy(30, 25);
//    cout << size;

    int start1 = block.getX();
    int end1 = start1 + block.getSize();
    int start2 = block1.getX();
    int end2 = start2 + block1.getSize();

    if (end1 <= start2) {
        return true;
    }

    if (start1 >= end2) {
        return true;
    }

    int num = start2 - start1;
    if(num > 0) {
        block.removeLeft(num);
    }

    num = end1 - end2;
    if(num > 0) {
        block.removeRight(num);
    }
    return false;
}

int main() {
    system("clear");
    Game game;
    game.start();
//    Block block(20, BLOCK2, 33);
//    Block block2(20, BLOCK1, 35);
//    block.move(25, 25);
//    block.display();
//    block2.move(5, 24);
//    block2.display();
//    block.destroy();
//    block2.destroy();
//    r(block2, block);
//    usleep(300000);
//    block.display();
//    block2.display();
//    cout <<endl <<endl <<endl;
    return 0;
}

