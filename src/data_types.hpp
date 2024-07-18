#include <vector>

struct Position {
    std::uint32_t row;
    std::uint32_t col;
};

enum class Token {
    Shade,
    Origin,
    None
};

struct Move {
    Position position;
    Token token;
};
