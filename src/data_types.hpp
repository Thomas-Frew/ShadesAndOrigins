#include <vector>

struct Position {

    Position(): row(0), col(0) {}
    Position(std::uint32_t row, std::uint32_t col): row(row), col(col) {}

    std::uint32_t row;
    std::uint32_t col;

    bool operator==(const Position &other) const{
        return (row == other.row) && (col == other.col);
    }
};

struct positionHash {
public:
	size_t operator()(const Position position) const 
    {
		return std::hash<std::uint32_t>()(position.row) ^ std::hash<std::uint32_t>()(position.col);
	}
};

enum class Token {
    Shade,
    Origin,
    None
};

Token invertToken(Token token) {
    if (token == Token::Shade) return Token::Origin;
    if (token == Token::Origin) return Token::Shade;
    return Token::None;
}

std::int32_t tokenToEval(Token token) {
    if (token == Token::Shade) return 1;
    if (token == Token::Origin) return -1;
    return 0;
}

char tokenToChar(Token token) {
    switch (token) {
        case Token::Shade:
            return 'S';

        case Token::Origin:
            return 'O';

        case Token::None:
            return '.';
    }
}

struct Move {
    Position position;
    Token token;
};
