#include <iostream>
#include "game.hpp"
#include "monte_carlo.hpp"

int main() {

    Game board(4);

    MonteCarloNode* node = new MonteCarloNode(std::nullopt, board);
    //node->performSimulation().printBoard();

    for (int i = 0; i < 10; i++) {
        auto selectedNode = node->performSelection();
        selectedNode->performExpansion();
        
        selectedNode->getGame().printBoard();
        selectedNode->performSimulation().printBoard();
    }

/* Basic game
    Game board(3);
    board.printBoard();
    std::cout << '\n';
    
    board.makeMove({{0,0}, Token::Shade});
    board.printBoard();
    std::cout << '\n';

    board.makeMove({{1,0}, Token::Origin});
    board.printBoard();
    std::cout << '\n';

    board.makeMove({{0,1}, Token::Shade});
    board.printBoard();
    std::cout << '\n';

    board.makeMove({{2,2}, Token::Origin});
    board.printBoard();
*/

    return 0;
}