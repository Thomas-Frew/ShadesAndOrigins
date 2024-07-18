#ifndef MCST_HPP
#define MCST_HPP

#include <vector>
#include <unordered_set>
#include <cmath>
#include <optional>

#include "game.hpp"

class MonteCarloNode {
public:
    MonteCarloNode(uint32_t totalVisits, uint32_t totalWins, Game game): totalVisits(totalVisits), totalWins(totalWins), game(game) {}

    bool isLeaf() {
        return this->children.size() == 0;
    }

    void addChild(MonteCarloNode* child) {
        this->children.push_back(child);
    }

    std::optional<MonteCarloNode*> getBestChild() {
        std::optional<MonteCarloNode*> bestChild = std::nullopt;
        double_t bestUtility = 0;

        if (isLeaf()) return std::nullopt;

        for (auto child : children) {
            double_t utility = getChildUtility(child) ;
            if (utility > bestUtility) {
                bestChild = child;
                bestUtility = utility;
            }
        }

        return bestChild;
    }

private:
    Move move;
    Game game;
    std::vector<MonteCarloNode*> children;

    uint32_t totalVisits;
    uint32_t totalWins;

    double_t getChildUtility(MonteCarloNode* child) {
        double_t exploration = static_cast<double_t>(child->totalWins)/child->totalVisits;
        double_t exploitation = std::sqrt(2.0) * std::sqrt(std::log(static_cast<double>(this->totalVisits))/child->totalVisits);

        return exploration + exploitation;
    }
    
    MonteCarloNode* performSelection() {
        std::optional<MonteCarloNode*> bestChild = this->getBestChild();
        return bestChild.value_or(this);
    }

    void performExpansion() {
        this->game.getFirstEmptyPosition();
        // TODO
    }

};

class MonteCarloTree {


private:
    MonteCarloNode* root;

    MonteCarloNode* performSelection() {
        root->performSelection();        
    }

};

#endif