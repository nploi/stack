#include "game.h"

void Game::runLR() {
    int top = 15, topTemp = 15;
    int size = SIZE;
    int indexColor = util::random(0, 16);
    Block blockTop = arrBlock[0];
    while (true) {
        bool odd = arrBlock.size() % 2 == 0;
        Block block(size, (topTemp % 2 == 0 ? BLOCK1 : BLOCK2), colors[indexColor]);

        while (!stop && odd) {
            goRight(block, top);
            goLeft(block, top);
        }
        while (!stop && !odd) {
            goLeft(block, top);
            goRight(block, top);
        }

        if(stop) {
            block.destroy();
            gameOver = insertBlock(block);
            if(gameOver) {
                block.display();
                printBlocks(topTemp);
                return;
            }

            if(top == 7) {
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
        char c;
        util::getchar(c);
        if(gameOver) {
            return;
        }
        switch (c) {
            case ' ':
                stop = true;
                break;
//            case 'e':
//                return;
        }
    } while (true);
}

void Game::init() {
    Block defaultBlock(20, BLOCK2, colors[16]);
    defaultBlock.move(15, 15);
    insertBlock(defaultBlock);
    printBlocks(15);
    stop = false;
    speed = 40000;
    gameOver = false;
}

void Game::printBlocks(int top) {
    system("clear");
    for (int i = arrBlock.size() - 1; i >= 0; --i) {
        arrBlock[i].move(arrBlock[i].getX(), ++top);
        arrBlock[i].display();
        if(!gameOver && top > 15) {
            break;
        }
    }
    util::gotoxy(0, top + 1);
    cout << "███████████████████████████████████████████████████\n";
    util::gotoxy(59, 10);
    cout << "[PRESS SPACE]\n";
    util::gotoxy(55, 11);
    cout << "╔══════════════════╗\n";
    util::gotoxy(55, 12);
    cout << "║YOUR SCORE:       ║" << endl;
    util::gotoxy(55, 13);
    cout << "╚══════════════════╝\n";
    util::gotoxy(70, 12);
    cout << Color::color(Color::Code::FG_WHITE);
    cout << arrBlock.size() - 1 << endl;
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

void Game::goRight(Block &block, int top) {
    Block space(1, " ", Color::Code::RESET);

    // Move block to right
    for (int i = 0; i + block.getSize() <= SIZE_OF_TABLE && !stop; ++i) {
        usleep(speed);

        block.move(i, top);
        block.display();
        if(i > 1) {
            space.move(i - 1, top);
            space.display();
        }
    }
}

void Game::goLeft(Block &block, int top) {
    Block space(1, " ", Color::Code::RESET);
    // Move block to left
    for (int i = SIZE_OF_TABLE - block.getSize(); i >= 0 && !stop; --i) {
        usleep(speed);

        block.move(i, top);
        block.display();
        space.move(i + block.getSize(), top);
        space.display();
    }
}
