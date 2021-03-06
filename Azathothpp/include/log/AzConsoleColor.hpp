#pragma once
#include <ostream>

namespace Az {
    enum class ConsoleColor {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_YELLOW   = 33,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_YELLOW   = 43,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
    };

    inline std::ostream& operator<<(std::ostream& os, ConsoleColor color) {
            os << "\033[" << (int)color << "m";
            return os; 
    }
}