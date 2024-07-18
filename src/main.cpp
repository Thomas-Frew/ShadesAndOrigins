#include <iostream>

#include "game.hpp"

int main() {

    GameBoard board(4);

    std::cout << board.makeMove(0,0,Token::Shade) << '\n';
    std::cout << board.makeMove(1,0,Token::Shade) << '\n';
    std::cout << board.makeMove(2,0,Token::Shade) << '\n';
    std::cout << board.makeMove(3,0,Token::Shade) << '\n';
    std::cout << board.makeMove(3,0,Token::Origin) << '\n';

    return 0;
}