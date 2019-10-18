#ifndef COLOR_H
#define COLOR_H

#include <ostream>

namespace Color {
    enum Code {
        RESET = 0,
        BOLD = 1,
        BG_BLUE = 44,
        BG_DEFAULT = 49,
        BG_GREEN = 42,
        BG_RED = 41,
        FG_BLACK = 30,
        FG_BLUE = 34,
        FG_CYAN = 36,
        FG_DARK_GRAY = 90,
        FG_DEFAULT = 39,
        FG_GREEN = 32,
        FG_LIGHT_BLUE = 94,
        FG_LIGHT_CYAN = 96,
        FG_LIGHT_GRAY = 37,
        FG_LIGHT_GREEN = 92,
        FG_LIGHT_MAGENTA = 95,
        FG_LIGHT_RED = 91,
        FG_LIGHT_YELLOW = 93,
        FG_MAGENTA = 35,
        FG_RED = 31,
        FG_WHITE = 97,
        FG_YELLOW = 33,
    };

    class color {
        int code;
    public:
        color(double pCode) : code(pCode) {}
        friend std::ostream &operator<<(std::ostream &os, const color &mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}

static int colors[] = {31, 91, 32, 92, 33, 93, 34, 94, 35, 95, 36, 96, 37, 97, 0};
static Color::color bold(Color::Code::BOLD);
static Color::color fg_default(Color::Code::FG_DEFAULT);
static Color::color reset(Color::Code::RESET);

#endif