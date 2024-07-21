#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include "../src/game.hpp"
#include "../src/monte_carlo.hpp"

// Dummy variables
const Game dummyBoard(4);
const Move dummyMove{{0,0},Token::None};
const std::optional<MonteCarloNode*> dummyParent;

// Game Win Tests
TEST_CASE( "Connect 4 Row", "[4x4]" )
{
    Game board(4);

    REQUIRE( board.makeMove({{0,0},Token::Origin}) == Token::None );
    REQUIRE( board.makeMove({{0,1},Token::Origin}) == Token::None );
    REQUIRE( board.makeMove({{0,2},Token::Origin}) == Token::None );
    REQUIRE( board.makeMove({{0,3},Token::Origin}) == Token::Origin );

}

TEST_CASE( "Connect 4 Col", "[4x4]" )
{
    Game board(4);

    REQUIRE( board.makeMove({{0,0},Token::Shade}) == Token::None );
    REQUIRE( board.makeMove({{1,0},Token::Shade}) == Token::None );
    REQUIRE( board.makeMove({{2,0},Token::Shade}) == Token::None );
    REQUIRE( board.makeMove({{3,0},Token::Shade}) == Token::Shade );

}

TEST_CASE( "Connect 4 Diag Top-Left", "[4x4]" )
{
    Game board(4);

    REQUIRE( board.makeMove({{0,0},Token::Origin}) == Token::None );
    REQUIRE( board.makeMove({{1,1},Token::Origin}) == Token::None );
    REQUIRE( board.makeMove({{2,2},Token::Origin}) == Token::None );
    REQUIRE( board.makeMove({{3,3},Token::Origin}) == Token::Origin );

}

TEST_CASE( "Connect 4 Diag Top-Right", "4x4" )
{
    Game board(4);

    REQUIRE( board.makeMove({{0,3},Token::Shade}) == Token::None );
    REQUIRE( board.makeMove({{1,2},Token::Shade}) == Token::None );
    REQUIRE( board.makeMove({{2,1},Token::Shade}) == Token::None );
    REQUIRE( board.makeMove({{3,0},Token::Shade}) == Token::Shade );

}


TEST_CASE( "Connect 1", "[1x1]" )
{
    Game board(1);

    REQUIRE( board.makeMove({{0,0},Token::Shade}) == Token::Shade );

}


TEST_CASE( "Test Game", "[3x3]" )
{
    Game board(3);

    REQUIRE( board.makeMove({{0,0},Token::Shade}) == Token::None );
    REQUIRE( board.makeMove({{1,1},Token::Origin}) == Token::None );
    REQUIRE( board.makeMove({{0,1},Token::Shade}) == Token::None );
    REQUIRE( board.makeMove({{0,2},Token::Origin}) == Token::None );
    REQUIRE( board.makeMove({{1,0},Token::Shade}) == Token::None );
    REQUIRE( board.makeMove({{2,2},Token::Origin}) == Token::None );
    REQUIRE( board.makeMove({{2,0},Token::Shade}) == Token::Shade );

}

// MTCS: Selection
/*
TEST_CASE( "Select Only Child" )
{
    MonteCarloNode* parent = new MonteCarloNode(dummyBoard,dummyMove,dummyParent,1,1);
    MonteCarloNode* child = new MonteCarloNode(dummyBoard,dummyMove,dummyParent,1,1);
    parent->addChild(child);

    REQUIRE( parent->performSelection() == child );
}

TEST_CASE( "Select Superior Child" )
{
    MonteCarloNode* parent = new MonteCarloNode(dummyBoard,dummyMove,dummyParent,1,1);
    MonteCarloNode* child1 = new MonteCarloNode(dummyBoard,dummyMove,dummyParent,1,0);
    MonteCarloNode* child2 = new MonteCarloNode(dummyBoard,dummyMove,dummyParent,1,1);

    parent->addChild(child1);
    parent->addChild(child2);

    REQUIRE( parent->performSelection() == child2 );
}

TEST_CASE( "Select Far Superior Child" )
{
    MonteCarloNode* parent = new MonteCarloNode(dummyBoard,dummyMove,dummyParent,20,20);
    MonteCarloNode* child1 = new MonteCarloNode(dummyBoard,dummyMove,dummyParent,10,10);
    MonteCarloNode* child2 = new MonteCarloNode(dummyBoard,dummyMove,dummyParent,10,7);

    parent->addChild(child1);
    parent->addChild(child2);

    REQUIRE( parent->performSelection() == child1 );
}

// MTCS: Expansion
TEST_CASE( "Leaf by Default", "[4x4]" )
{
    Game board(4);
    MonteCarloNode* parent = new MonteCarloNode(board,dummyMove,dummyParent,1,1);

    REQUIRE( parent->isLeaf() == true );

}

TEST_CASE( "Non-Leaf when Expanded", "[4x4]" )
{
    Game board(4);
    MonteCarloNode* parent = new MonteCarloNode(board,dummyMove,dummyParent,1,1);

    parent->performExpansion();
    REQUIRE( parent->isLeaf() == false );

}

TEST_CASE( "Expansions Successful", "[4x4]" )
{
    Game board(4);
    MonteCarloNode* parent = new MonteCarloNode(board,dummyMove,dummyParent,1,1);    

    for (int i = 0; i < 3; i++) REQUIRE( parent->performExpansion() != std::nullopt );
}

TEST_CASE( "17 Expansions Fail", "[4x4]" )
{
    Game board(4);
    MonteCarloNode* parent = new MonteCarloNode(board,dummyMove,dummyParent,1,1);

    for (int i = 0; i < 16; i++) REQUIRE( parent->performExpansion() != std::nullopt );
    REQUIRE( parent->performExpansion() == std::nullopt );
}

TEST_CASE( "2 Expansions Fail", "[1x1]" )
{
    Game board(1);
    MonteCarloNode* parent = new MonteCarloNode(board,dummyMove,dummyParent,1,1);

    REQUIRE( parent->performExpansion() != std::nullopt );
    REQUIRE( parent->performExpansion() == std::nullopt );
}
*/
