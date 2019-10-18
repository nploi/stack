#include "game.hpp"

void Game::menu() {

    bestScore = getBestScore();
    printBlocks((score <= MID ? MID : 5));
    Drawer::menu(51, 8);
    char select;
    cin >> select;
    switch (select) {
      case '1':
        Game::init();
        Game::start();
        break;
      case '2':
        Game::save();
        break;
      default:
        Game::menu();
    }
}

void Game::save() {
    std::ofstream outputFile;
    outputFile.open(FILE_NAME, ios::out);
    if(outputFile.fail()) {
        cout << "Open file failed.";
        exit(1);
    }
    outputFile << bestScore;
    outputFile.close();
}

bool Game::isContinue() {
    return !stop && !returnMenu;
}

int Game::getBestScore() {
	int score;
	std::ifstream inputFile;
    inputFile.open(FILE_NAME, ios::in);
	if (inputFile.fail()) {
        cout << "Created new file.";
		std::ofstream create(FILE_NAME);
		score = 0;
		create.close();
	} else {
        inputFile >> score;
	}
    inputFile.close();
	return score;
}

void Game::init() {
    score = 0;
    indexColor = Util::random(0, 14);
    Block defaultBlock(SIZE_BLOCK, colors[indexColor]);
    defaultBlock.move(MID, MID);
    arrBlock.clear();
    insertBlock(defaultBlock);
    stop = false;
    speed = 40;
    gameOver = false;
    returnMenu = false;
    counter = 0;
    printBlocks(MID);
}

void Game::printBlocks(int top) {
	Util::clear();
	for (int i = arrBlock.size() - 1; i >= 0; --i) {
        arrBlock[i].move(arrBlock[i].getX(), ++top);
        arrBlock[i].display();
        if(!gameOver && top > MID) {
            break;
        }
    }

    Util::gotoxy(0, top + 1);
    for (int i = 0; i < SIZE_OF_TABLE; i++) {
		cout << '#';
	}
	if(!gameOver && started) {
        Drawer::help(51, 8);
    }
    Drawer::scores(51, 4, score, bestScore);
}

void Game::getInput() {

    do {
        char c;
        Util::getchar(c);
        switch (c) {
            case SPACE:
                stop = true;
                break;
            case ESC:
                returnMenu = true;
                return;
        }
    } while (!gameOver);
}

void Game::logic() {
    int top = MID, topTemp = MID;
    int size = SIZE_BLOCK;
    int color = indexColor;
    color++;
    while (true) {
        bool odd = arrBlock.size() % 2 == 0;
        Block block(size, colors[color]);

        while (odd && isContinue()) {
            goRight(block, top);
            goLeft(block, top);
        }
        while (!odd && isContinue()) {
            goLeft(block, top);
            goRight(block, top);
        }

        if(returnMenu) {
            menu();
            return;
        }

        if(stop) {
            block.destroy();
            gameOver = insertBlock(block);
            if(gameOver) {
                arrBlock.push_back(block);
                save();
                menu();
                return;
            }
            score++;
            if(score > bestScore) {
                bestScore = score;
            }

            if(top == 7) {
                topTemp--;
            } else {
                top--;
                topTemp = top;
            }
            printBlocks(topTemp++);
            color--;
            if(color < 0) {
                color = 14;
            }

            stop = false;
            size = arrBlock[arrBlock.size() - 1].getSize();
        }
    }
}

void Game::start() {
    Drawer::help(51, 8);
    started = true;
    thread thread1(&logic);
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
    if(block.getSize() < SIZE_BLOCK && block.getSize() == arrBlock[size - 1].getSize()) {
        counter++;
        if(counter >= 4) {
            int numLeft = 1, numRight = 1;
            if(SIZE_BLOCK - block.getSize() == 1) {
                if(score%2==0) {
                    numLeft = 0;
                } else {
                    numRight = 0;
                }
            }
            block.addLeft(numLeft);
            block.addRight(numRight);
        }
    } else {
        counter = 0;
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
    // Move block to right
    for (int i = 0; i + block.getSize() <= SIZE_OF_TABLE && isContinue(); ++i) {
		Util::sleep(speed);
        block.move(i, top);
        block.display();
#ifdef _WIN32
		Util::remove(i - 1, top);
#else
		Util::remove(i, top);
#endif // _WIN32 

    }
}

void Game::goLeft(Block &block, int top) {
    // Move block to left
    for (int i = SIZE_OF_TABLE - block.getSize(); i >= 0 && isContinue(); --i) {
        Util::sleep(speed);
        block.move(i, top);
        block.display();
#ifdef _WIN32
        Util::remove(i + block.getSize(), top);
#else
        Util::remove(i + block.getSize() - 1, top);
#endif // _WIN32
    }
}
