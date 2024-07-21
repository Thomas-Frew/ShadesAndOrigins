#ifndef MCST_HPP
#define MCST_HPP

#include <vector>
#include <unordered_set>
#include <cmath>
#include <optional>
#include <random>
#include <ctime>
#include <queue>
#include <utility>
#include <limits>

#include "game.hpp"


class MonteCarloNode {
public:

    MonteCarloNode(Game game, std::optional<Move> move, std::optional<MonteCarloNode*> parent): MonteCarloNode(game,move,parent,1,0) {}
    MonteCarloNode(Game game, std::optional<Move> move, std::optional<MonteCarloNode*> parent, uint32_t totalVisits, uint32_t totalWins): totalVisits(totalVisits), totalWins(totalWins), move(move), game(game), parent(parent), unexploredPositions(this->game.getEmptyPositions()) {}

    // Display functions
    void printSearchTree() {

        std::uint32_t currID = 0;
        std::queue<std::pair<std::uint32_t, MonteCarloNode*>> nodeQueue;

        nodeQueue.push({currID, this});

        while (nodeQueue.size()) {

            std::uint32_t parentID = nodeQueue.front().first;
            MonteCarloNode* currNode = nodeQueue.front().second; 

            nodeQueue.pop();

            std::cout << "Board: " << currID << " Parent: " << parentID << '\n';
            std::cout << "Visits: " << currNode->totalVisits << " Wins: " << currNode->totalWins << " ";
            if (currNode->parent.has_value()) std::cout << "Utility: " << currNode->parent.value()->getChildUtility(currNode) << " ";
            std::cout << "Win Ratio: " << currNode->getWinRatio() << " ";
            std::cout << "Evaluation: " << tokenToEval(currNode->game.identity) << '\n';
            std::cout << currNode << '\n';
            currNode->game.printBoard(); 

            for (auto child : currNode->getChildren()) {
                nodeQueue.push({currID, child});
            }
            currID++;

        }

    }

    // Monte Carlo Search
    bool performSearchIteration() {
        
        // Selection
        MonteCarloNode* bestNode = this->performSelection();
        std::cout << bestNode << '\n';

        // Expansion
        std::optional<MonteCarloNode*> newChild = bestNode->performExpansion();
        if (!newChild.has_value()) return false;

        // Simulation
        Token winningToken = newChild.value()->performSimulation();
        std::int32_t evaluation = tokenToEval(winningToken);

        // Backpropogation
        newChild.value()->performBackpropogation(evaluation);
        
        return true;
    }

    MonteCarloNode* performSelection() {
        MonteCarloNode* currNode = this;

        while (!currNode->isLeaf()) {
            if (currNode->isUnresolved()) {
                return currNode;
            } else {
                currNode = currNode->getBestChild().value();
            }
        }
        
        return currNode;

    }

    std::optional<MonteCarloNode*> performExpansion() {
        std::optional<Position> childPosition = popFirstUnusedPosition();

        if (!childPosition.has_value()) return std::nullopt;

        Game childGame = this->game;
        Move childMove = Move{childPosition.value(), childGame.getCurrentToken()};
        childGame.makeMove(childMove);

        MonteCarloNode* childNode = new MonteCarloNode(childGame, childMove, std::optional<MonteCarloNode*>(this));
        this->children.push_back(childNode);

        return childNode;
    }

    Token performSimulation() {
        auto simulatedGame = this->game;
        
        std::srand(std::time(0));

        // While the game has no winner and there are moves to be made...
        while (simulatedGame.getEmptyPositions().size() > 0 && simulatedGame.identity == Token::None) {
            // Invert control
            Token currentToken = simulatedGame.getCurrentToken();

            // Choose a random position
            std::vector<Position> positions = simulatedGame.getEmptyPositions();
            std::uint32_t randomIndex = std::rand() % positions.size();
            Position randomPosition = positions[randomIndex];

            // Execute random move
            Move randomMove = {randomPosition, currentToken};
            simulatedGame.makeMove(randomMove);
        }

        return simulatedGame.identity;
    }

    void performBackpropogation(std::int32_t evaluation) {
        MonteCarloNode* currNode = this;

        for (;;) {
            currNode->totalVisits++;
            currNode->totalWins += evaluation;

            if (!currNode->parent.has_value()) break;
            currNode = currNode->parent.value();
        }
    }

    // Properties
    bool isLeaf() {
        for (auto child : children) {
            if (child->game.identity == Token::None) return false;
        }
        return true;
    }

    bool isUnresolved() {
        return this->unexploredPositions.size() > 0;
    }

    void addChild(MonteCarloNode* child) {
        this->children.push_back(child);
    }

    Game getGame() {
        return this->game;
    }

    std::vector<MonteCarloNode*> getChildren() {
        return this->children;
    }

private:
    std::optional<Move> move;
    std::optional<MonteCarloNode*> parent;
    std::vector<MonteCarloNode*> children;

    Game game;
    std::vector<Position> unexploredPositions;

    uint32_t totalVisits;
    int32_t totalWins;

    double_t getChildUtility(MonteCarloNode* child) {
        double_t exploitation= static_cast<double_t>(child->totalWins)/child->totalVisits;
        double_t exploration  = std::sqrt(2.0) * std::sqrt(std::log(static_cast<double_t>(this->totalVisits))/child->totalVisits);

        return exploration + exploitation;
    }

    double_t getWinRatio() {
        double_t exploitation = static_cast<double_t>(this->totalWins)/static_cast<double_t>(this->totalVisits);
        return exploitation;
    }
    
    std::optional<MonteCarloNode*> getBestChild() {

        std::optional<MonteCarloNode*> bestChild = std::nullopt;
        double_t bestUtility = (this->game.getCurrentToken() == Token::Shade) ? std::numeric_limits<double>::min() : std::numeric_limits<double>::max();

        for (auto child : children) {
    
            double_t utility = getChildUtility(child);
            Token identity = child->game.identity;

            if (identity == Token::None && this->game.getCurrentToken() == Token::Shade && utility >= bestUtility || this->game.getCurrentToken() == Token::Origin && utility <= bestUtility) {
                bestChild = child;
                bestUtility = utility;
            }

        }

        return bestChild;
    }

    std::optional<Position> popFirstUnusedPosition() {

        if (this->unexploredPositions.size() == 0) return std::nullopt;

        Position position = unexploredPositions.back();
        unexploredPositions.pop_back();

        return position;
    }
};

#endif