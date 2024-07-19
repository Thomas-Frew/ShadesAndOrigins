#ifndef MCST_HPP
#define MCST_HPP

#include <vector>
#include <unordered_set>
#include <cmath>
#include <optional>
#include <random>
#include <ctime>

#include "game.hpp"


class MonteCarloNode {
public:
    MonteCarloNode(uint32_t totalVisits, uint32_t totalWins, std::optional<Move> move, Game game): totalVisits(totalVisits), totalWins(totalWins), move(move), game(game) {}
    MonteCarloNode(std::optional<Move> move, Game game): MonteCarloNode(1,1,move,game) {}

    bool isLeaf() {
        return this->children.size() == 0;
    }

    void addChild(MonteCarloNode* child) {
        this->children.push_back(child);
    }

    Game getGame() {
        return game;
    }


    MonteCarloNode* performSelection() {
        if (!this->isLeaf()) return getBestChild()->performSelection();
        return this;
    }

    void performSearchIteration() {
        MonteCarloNode* selectedNode = this->performSelection();
        std::optional<MonteCarloNode*> expandedNode = selectedNode->performExpansion();
        if (expandedNode.has_value()) expandedNode.value()->performSimulation();
    }

    std::optional<MonteCarloNode*> performExpansion() {
        std::optional<Position> childPosition = getFirstUnusedPosition();

        if (!childPosition.has_value()) return std::nullopt;

        Game childGame = this->game;
        Move childMove = Move{childPosition.value(), childGame.getCurrentToken()};
        childGame.makeMove(childMove);

        MonteCarloNode* childNode = new MonteCarloNode(childMove, childGame);
        this->children.push_back(childNode);

        exhaustedPositions.insert(childPosition.value());
        return childNode;
    }

    Game performSimulation() {
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

        return simulatedGame;
    }

private:
    std::optional<Move> move;
    std::vector<MonteCarloNode*> children;

    Game game;
    std::unordered_set<Position,positionHash> exhaustedPositions;

    uint32_t totalVisits;
    uint32_t totalWins;

    double_t getChildUtility(MonteCarloNode* child) {
        double_t exploration = static_cast<double_t>(child->totalWins)/child->totalVisits;
        double_t exploitation = std::sqrt(2.0) * std::sqrt(std::log(static_cast<double>(this->totalVisits))/child->totalVisits);

        return exploration + exploitation;
    }
    
    MonteCarloNode* getBestChild() {
        MonteCarloNode* bestChild = nullptr;
        double_t bestUtility = 0;

        for (auto child : children) {
        
            double_t utility = getChildUtility(child);

            if (utility > bestUtility) {
                bestChild = child;
                bestUtility = utility;
            }
        }

        return bestChild;
    }

    
    std::optional<Position> getFirstUnusedPosition() {

        std::vector<Position> positions = this->game.getEmptyPositions();

        for (auto position : positions) {
            if (exhaustedPositions.contains(position)) continue;
            return position;
        }

        return std::nullopt;

    }

};

#endif