#include "block.h"

Block::Block(int size, int color) {
    this->size = size;
    this->color = color;
}

void Block::removeRight(int num) {
    this->size -= num;
}

void Block::removeLeft(int num) {
    this->size -= num;
    this->x += num;
}

void Block::remove() {
    this->size = 0;
}

void Block::destroy() {
    util::gotoxy(x, y);
    cout << Color::color(Color::Code::RESET);
    for (int i = 0; i <= this->size; ++i) {
        cout << ' ';
    }
}

void Block::move(int x, int y) {
    this->x = x;
    this->y = y;
}

void Block::display() {
    util::gotoxy(x, y);
    cout << Color::color(this->color);
    for (int i = 0; i < this->size; ++i) {
        cout << BLOCK;
    }
    cout << endl;
}

Block::Block(const Block &block) {
    this->x = block.x;
    this->y = block.y;
    this->color = block.color;
    this->size = block.size;
}

int Block::getX() {
    return this->x;
}

int Block::getY() {
    return this->y;
}

int Block::getSize() {
    return this->size;
}
