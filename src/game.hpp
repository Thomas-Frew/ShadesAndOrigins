#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>

#include <cassert>
#include <cstdint>

#include <vector>
#include <optional>
#include "data_types.hpp"

// A single unit in an array of units
class GameSquare {
public:
    GameSquare(): identity(Token::None) {}
    GameSquare(Token identity): identity(identity) {}

    Token identity;
};

class GameBoard {
public:
    GameBoard(uint32_t length): state(length, std::vector<GameSquare>(length)) {}
    std::vector<std::vector<GameSquare>> state;

    std::vector<GameSquare>& operator[](std::size_t idx) {
        return state[idx];
    }
};

class Game : public GameSquare {
public:
    Game(std::uint32_t length): length(length), board(GameBoard(length)), currentToken(Token::Shade) {}

    Token makeMove(Move move) {
        assert(move.position.row >= 0 && move.position.row < length && move.position.col >= 0 && move.position.col < length); // Guarantee valid position for move

        this->board[move.position.row][move.position.col] = GameSquare(move.token);
        this->identity = checkForLines(move.position);

        this->invertCurrentToken();
        return this->identity;
    }

    std::vector<Position> getEmptyPositions() {
        std::vector<Position> emptyPositions;
        for (std::uint32_t row = 0; row < this->length; row++) {
            for (std::uint32_t col = 0; col < this->length; col++) {
                if (board[row][col].identity == Token::None) emptyPositions.push_back({row, col});
            }
        }
        return emptyPositions;
    }

    Token getCurrentToken() {
        return currentToken;
    }

    void invertCurrentToken() {
        currentToken = invertToken(currentToken);
    }

    void printBoard() {
        for (std::uint32_t row = 0; row < this->length; row++) {
            for (std::uint32_t col = 0; col < this->length; col++) {
                std::cout << tokenToChar(board[row][col].identity) << ' ';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }

private:
    std::uint32_t length;
    GameBoard board;

    Token currentToken;

    // Line Checkers
    Token checkForLines(Position position) {
        Token identity;
        
        identity = checkRow(position); // Row check
        if (identity != Token::None) return identity;

        identity = checkCol(position); // Col check
        if (identity != Token::None) return identity;

        identity = checkDiagLeft(position); // Diagonal check
        if (identity != Token::None) return identity;

        identity = checkDiagRight(position); // Diagonal check
        if (identity != Token::None) return identity;

        return Token::None;
    }

    Token checkRow(Position position) {
        for (std::uint32_t col = 0; col < this->length; col++) {
            if (board[position.row][col].identity != board[position.row][0].identity) return Token::None;
        }
        return board[position.row][0].identity;
    }

    Token checkCol(Position position) {
        for (std::uint32_t row = 0; row < this->length; row++) {
            if (board[row][position.col].identity != board[0][position.col].identity) return Token::None;
        }
        return board[0][position.col].identity;        
    }

    Token checkDiagLeft(Position position) {
        if (position.row != position.col) return Token::None;
        for (std::uint32_t index = 0; index < this->length; index++) {
            if (board[index][index].identity != board[0][0].identity) return Token::None;
        }
        return board[0][0].identity; 
    }

    Token checkDiagRight(Position position) {
        if (position.row != this->length-position.col-1) return Token::None;
        for (std::uint32_t index = 0; index < this->length; index++) {
            if (board[index][this->length-index-1].identity != board[0][this->length-1].identity) return Token::None;
        }
        return board[0][this->length-1].identity; 
    }

};

#endif