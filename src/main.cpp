#include <iostream>
#include "game.hpp"
#include "monte_carlo.hpp"

int main() {

    Game board(3);

    MonteCarloNode* node = new MonteCarloNode(board, std::nullopt, std::nullopt);
    for (int i = 0; i < 100000; i++) {
        node->performSearchIteration();
    }
    node->printSearchTree();
    

/* Early manual test
    auto selectedNode = node->performSelection();
    auto expandedNode = selectedNode->performExpansion();
    node = expandedNode.value();

    selectedNode = node->performSelection();
    expandedNode = selectedNode->performExpansion();
    node = expandedNode.value();

    selectedNode = node->performSelection();
    expandedNode = selectedNode->performExpansion();
    node = expandedNode.value();


    for (int i = 0; i < 10; i++) {
        auto selectedNode = node->performSelection();
        auto expandedNode = selectedNode->performExpansion();
    }

    for (auto child : node->getChildren()) {
        child->getGame().printBoard();
        child->performExpansion();
    }
*/

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