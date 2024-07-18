#include <cassert>
#include <cstdint>
#include <cmath>

#include <vector>

#include "token.hpp"

// A single unit in an array of units
class GameSquare {
public:
    GameSquare(): identity(Token::None) {}
    GameSquare(Token identity): identity(identity) {}

    Token identity;
};

class GameBoard : public GameSquare {
public:
    GameBoard(std::uint32_t length) {
        this->length = length;
        elements.resize(this->length, std::vector<GameSquare>(this->length));
    }

    Token makeMove(std::uint32_t row, std::uint32_t col, Token move) {
        assert(row >= 0 && row < length && col >= 0 && col < length); // Guarantee valid position for move

        elements[row][col] = GameSquare(move);
        return checkForLines(row, col);
    }

private:
    std::uint32_t length;
    std::vector<std::vector<GameSquare>> elements;

    Token checkForLines(std::uint32_t row, std::uint32_t col) {
        Token identity;
        
        identity = checkRow(row); // Row check
        if (identity != Token::None) return identity;

        identity = checkCol(col); // Col check
        if (identity != Token::None) return identity;

        identity = checkDiagLeft(row, col); // Diagonal check
        if (identity != Token::None) return identity;

        identity = checkDiagRight(row, col); // Diagonal check
        if (identity != Token::None) return identity;

        return Token::None;
    }

    // Row, column and diagonal line checkers
    Token checkRow(std::uint32_t row) {
        for (std::uint32_t col = 0; col < this->length; col++) {
            if (elements[row][col].identity != elements[row][0].identity) return Token::None;
        }
        return elements[row][0].identity;
    }

    Token checkCol(std::uint32_t col) {
        for (std::uint32_t row = 0; row < this->length; row++) {
            if (elements[row][col].identity != elements[0][col].identity) return Token::None;
        }
        return elements[0][col].identity;        
    }

    Token checkDiagLeft(std::uint32_t row, std::uint32_t col) {
        if (row != col) return Token::None;
        for (std::uint32_t index = 0; index < this->length; index++) {
            if (elements[index][index].identity != elements[0][0].identity) return Token::None;
        }
        return elements[0][0].identity; 
    }

    Token checkDiagRight(std::uint32_t row, std::uint32_t col) {
        if (row != this->length-col-1) return Token::None;
        for (std::uint32_t index = 0; index < this->length; index++) {
            if (elements[index][this->length-index-1].identity != elements[0][this->length-1].identity) return Token::None;
        }
        return elements[0][this->length-1].identity; 
    }

};