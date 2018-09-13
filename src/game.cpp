#include "game.h"

void Game::menu() {
    util::clear();
    printBlocks(15);
    cout << Color::color(Color::Code::FG_LIGHT_YELLOW);
    util::gotoxy(55, 11);
    cout << "1. Play new game";
    util::gotoxy(55, 12);
    cout << "2. Exit";  
    util::gotoxy(55, 13);
    cout << "=> ";

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
        cout << "Open file faild.";
        exit(1);
    }
    outputFile << bestScore;
    outputFile.close();
}

int Game::getBestScore() {
	int score;
	std::ifstream inputfile;
	inputfile.open(FILE_NAME, ios::in);
	if (inputfile.fail()) {
		std::ofstream create(FILE_NAME);
		cout << "Create file " << FILE_NAME;
		score = 0;
		create.close();
	}
	else {
		inputfile >> score;
	}
	inputfile.close();
	return score;
}

void Game::init() {
	bestScore = getBestScore();
    score = 0;
    indexColor = util::random(0, 12);
    Block defaultBlock(SIZE, colors[indexColor]);
    defaultBlock.move(15, 15);
    arrBlock.clear();
    insertBlock(defaultBlock);
    printBlocks(15);
    stop = false;
    speed = 30;
    gameOver = false;
    exitAndSave = false;
}

void Game::printBlocks(int top) {
	util::clear();
	for (int i = arrBlock.size() - 1; i >= 0; --i) {
        arrBlock[i].move(arrBlock[i].getX(), ++top);
        arrBlock[i].display();
        if(!gameOver && top > 15) {
            break;
        }
    }

    util::gotoxy(0, top + 1);
    for (int i = 0; i < SIZE_OF_TABLE; i++) {
		cout << BLOCK;
	}

    util::gotoxy(55, 5);
    cout << "* SPACE:\tstop block\n";
    util::gotoxy(55, 6);
    cout << "* ESC:\texit\n";

#ifdef _WIN32
	util::gotoxy(55, 7);
	cout << "|==================|\n";
	util::gotoxy(55, 8);
	cout << "|YOUR SCORE:       |\n";
	util::gotoxy(55, 9);
    cout << "|BEST SCORE:       |\n";
	util::gotoxy(55, 10);
	cout << "|==================|\n";
#else
	util::gotoxy(55, 7);
	cout << "╔══════════════════╗\n";
	util::gotoxy(55, 8);
	cout << "║YOUR SCORE:       ║\n";
    util::gotoxy(55, 9);
	cout << "║BEST SCORE:       ║\n";
	util::gotoxy(55, 10);
	cout << "╚══════════════════╝\n";
#endif // _WIN32

    util::gotoxy(70, 8);
    cout << Color::color(Color::Code::FG_WHITE);
    cout << score << endl;
    util::gotoxy(70, 9);
    cout << Color::color(Color::Code::FG_WHITE);
    cout << bestScore << endl;
}

void Game::getInput() {

    do {
        char c;
        util::getchar(c);
        switch (c) {
            case 32:
                stop = true;
                break;
            case 27:
               exitAndSave = true;
               return;
        }
    } while (!gameOver);
}

void Game::logic() {
    int top = 15, topTemp = 15;
    int size = SIZE;
    int color = indexColor;
    color++;
    while (true) {
        bool odd = arrBlock.size() % 2 == 0;
        Block block(size, colors[color]);

        while (!stop && odd && !exitAndSave) {
            goRight(block, top);
            goLeft(block, top);
        }
        while (!stop && !odd && !exitAndSave) {
            goLeft(block, top);
            goRight(block, top);
        }

        if(exitAndSave) {
            save();
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
	Game::init();
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
    for (int i = 0; i + block.getSize() <= SIZE_OF_TABLE && !stop && !exitAndSave; ++i) {
		util::sleep(speed);
        block.move(i, top);
        block.display();
#ifdef _WIN32
		util::remove(i - 1, top);
#else
		util::remove(i, top);
#endif // _WIN32 

    }
}

void Game::goLeft(Block &block, int top) {
    // Move block to left
    for (int i = SIZE_OF_TABLE - block.getSize(); i >= 0 && !stop && !exitAndSave; --i) {
        util::sleep(speed);
        block.move(i, top);
        block.display();
#ifdef _WIN32
        util::remove(i + block.getSize(), top);
#else
        util::remove(i + block.getSize() - 1, top);
#endif // _WIN32
    }
}
