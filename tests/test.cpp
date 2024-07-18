#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include "../src/game.hpp"
#include "../src/monte_carlo.cpp"

// Dummy variables
const Game dummyGame(4);

// Game Win Tests
TEST_CASE( "Connect 4 Row" )
{
    Game board(4);

    REQUIRE( board.makeMove({{0,0},Token::Origin}) == Token::None );
    REQUIRE( board.makeMove({{0,1},Token::Origin}) == Token::None );
    REQUIRE( board.makeMove({{0,2},Token::Origin}) == Token::None );
    REQUIRE( board.makeMove({{0,3},Token::Origin}) == Token::Origin );

}

TEST_CASE( "Connect 4 Col" )
{
    Game board(4);

    REQUIRE( board.makeMove({{0,0},Token::Shade}) == Token::None );
    REQUIRE( board.makeMove({{1,0},Token::Shade}) == Token::None );
    REQUIRE( board.makeMove({{2,0},Token::Shade}) == Token::None );
    REQUIRE( board.makeMove({{3,0},Token::Shade}) == Token::Shade );

}

TEST_CASE( "Connect 4 Diag Top-Left" )
{
    Game board(4);

    REQUIRE( board.makeMove({{0,0},Token::Origin}) == Token::None );
    REQUIRE( board.makeMove({{1,1},Token::Origin}) == Token::None );
    REQUIRE( board.makeMove({{2,2},Token::Origin}) == Token::None );
    REQUIRE( board.makeMove({{3,3},Token::Origin}) == Token::Origin );

}

TEST_CASE( "Connect 4 Diag Top-Right" )
{
    Game board(4);

    REQUIRE( board.makeMove({{0,3},Token::Shade}) == Token::None );
    REQUIRE( board.makeMove({{1,2},Token::Shade}) == Token::None );
    REQUIRE( board.makeMove({{2,1},Token::Shade}) == Token::None );
    REQUIRE( board.makeMove({{3,0},Token::Shade}) == Token::Shade );

}

// MTCS Tests
TEST_CASE( "Select Only Child" )
{
    MonteCarloNode* parent = new MonteCarloNode(1,1,dummyGame);
    MonteCarloNode* child = new MonteCarloNode(1,1,dummyGame);
    parent->addChild(child);

    REQUIRE( parent->getBestChild() == child );
}

TEST_CASE( "Select Superior Child" )
{
    MonteCarloNode* parent = new MonteCarloNode(1,1,dummyGame);
    MonteCarloNode* child1 = new MonteCarloNode(1,0,dummyGame);
    MonteCarloNode* child2 = new MonteCarloNode(1,1,dummyGame);

    parent->addChild(child1);
    parent->addChild(child2);

    REQUIRE( parent->getBestChild() == child2 );
}

TEST_CASE( "Select Far Superior Child" )
{
    MonteCarloNode* parent = new MonteCarloNode(20,20,dummyGame);
    MonteCarloNode* child1 = new MonteCarloNode(10,10,dummyGame);
    MonteCarloNode* child2 = new MonteCarloNode(10,7,dummyGame);

    parent->addChild(child1);
    parent->addChild(child2);

    REQUIRE( parent->getBestChild() == child1 );
}