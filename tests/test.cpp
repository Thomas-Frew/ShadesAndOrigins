#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include "../src/game.hpp"

TEST_CASE( "Connect 4 Row" )
{
    GameBoard board(4);

    REQUIRE( board.makeMove(0,0,Token::Origin) == Token::None );
    REQUIRE( board.makeMove(0,1,Token::Origin) == Token::None );
    REQUIRE( board.makeMove(0,2,Token::Origin) == Token::None );
    REQUIRE( board.makeMove(0,3,Token::Origin) == Token::Origin );

}

TEST_CASE( "Connect 4 Col" )
{
    GameBoard board(4);

    REQUIRE( board.makeMove(0,0,Token::Shade) == Token::None );
    REQUIRE( board.makeMove(1,0,Token::Shade) == Token::None );
    REQUIRE( board.makeMove(2,0,Token::Shade) == Token::None );
    REQUIRE( board.makeMove(3,0,Token::Shade) == Token::Shade );

}

TEST_CASE( "Connect 4 Diag Top-Left" )
{
    GameBoard board(4);

    REQUIRE( board.makeMove(0,0,Token::Origin) == Token::None );
    REQUIRE( board.makeMove(1,1,Token::Origin) == Token::None );
    REQUIRE( board.makeMove(2,2,Token::Origin) == Token::None );
    REQUIRE( board.makeMove(3,3,Token::Origin) == Token::Origin );

}

TEST_CASE( "Connect 4 Diag Top-Right" )
{
    GameBoard board(4);

    REQUIRE( board.makeMove(0,3,Token::Shade) == Token::None );
    REQUIRE( board.makeMove(1,2,Token::Shade) == Token::None );
    REQUIRE( board.makeMove(2,1,Token::Shade) == Token::None );
    REQUIRE( board.makeMove(3,0,Token::Shade) == Token::Shade );

}