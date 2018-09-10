#include "game.h"

void Game::menu() {
//    do {7
//        cout << ""
//    } while (true);
}
void Game::runLR() {
    int top = 19, topTemp = 19;
    int indexColor = util::random(0, 16);
    int size = 20;
    Block space(1, " ", Color::Code::RESET);
    Block blockTop = arrBlock[0];

    while (true) {
        bool odd = top % 2 == 0;
        Block block(size, (odd ? BLOCK1 : BLOCK2), colors[indexColor]);

        // Move block to right
        for (int i = 0; i <= SIZE_OF_TABLE && !stop; ++i) {
            usleep(speed);

            block.move(i, top);
            block.display();
            if(i > 0) {
                space.move(i - 1, top);
                space.display();
            }
        }

        // Move block to left
        for (int i = SIZE_OF_TABLE; i >= 0 && !stop; --i) {
            usleep(speed);

            block.move(i, top);
            block.display();
            space.move(i + block.getSize() + 1, top);
            space.display();
        }

        if(stop) {
            block.destroy();
            gameOver = insertBlock(block);
            if(gameOver) {
                block.display();
                cout << "GAME OVER!!";
                return;
            }

            if(top == 10) {
                topTemp--;
            } else {
                top--;
                topTemp = top;
            }
            printBlocks(topTemp++);
            indexColor--;
            if(indexColor < 0) {
                indexColor = 16;
            }

            stop = false;
            size = arrBlock[arrBlock.size() - 1].getSize();
        }
    }
}

void Game::getInput() {

    do {
        util::gotoxy(30, 30);
        char c;
        util::getchar(c);
        if(gameOver) {
            return;
        }
        switch (c) {
            case ' ':
                stop = true;
                break;
            case 'e':
                return;
        }
    } while (true);
}

void Game::init() {
    Block defaultBlock(20, BLOCK2, colors[16]);
    defaultBlock.move(15, 20);
    defaultBlock.display();
    insertBlock(defaultBlock);
    stop = false;
    pauseTemp = false;
    speed = 35000;
    gameOver = false;
}

void Game::printBlocks(int top) {
    system("clear");
    for (int i = arrBlock.size() - 1; i >= 0; --i) {
        arrBlock[i].move(arrBlock[i].getX(), ++top);
        arrBlock[i].display();
    }
}

void Game::start() {
    init();
    thread thread1(&runLR);
    thread thread2(&getInput);
    thread1.join();
    thread2.join();
}


bool Game::removeExcess(Block &block) {
    int size = arrBlock.size();

    if(size == 0) {
        return false;
    }

    int start1 = block.getX();
    int end1 = start1 + block.getSize();
    int start2 = arrBlock[size - 1].getX();
    int end2 = start2 + arrBlock[size - 1].getSize();

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

bool Game::insertBlock(Block &block) {
    bool result = removeExcess(block);
    if(!result) {
        arrBlock.push_back(block);
    }
    return result;
}
