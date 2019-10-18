#ifndef STACK_BLOCK_H
#define STACK_BLOCK_H

#include "util.hpp"
#include "color.hpp"

#ifdef _WIN32
#define BLOCK char(219)
#else
#define BLOCK "█"
#endif // _WIN32

using namespace std;

class Block {
  public:
    Block(int size, int color);
    Block(const Block &block);
    ~Block() {}
    void removeLeft(int num);
    void removeRight(int num);
    void addLeft(int num);
    void addRight(int num);
    void display();
    void move(int x, int y);
    void destroy();
    int getX();
    int getY();
    int getSize();
    int getColor();

  private:
    int x;
    int y;
    int size;
    int color;
};

#endif //STACK_BLOCK_H
