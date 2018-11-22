/*
  Studio Bakemono, 2018
*/

#pragma once

#include <array>

#include <SFML/Graphics.hpp>
#include <memory>

#include "State.hpp"
#include "Board.hpp"
#include "Piece.hpp"

// Forward delcaration to avoid circular headers

class Game;

class TestState : public State {
public:
  
  sf::Text greeting;
  sf::Clock clock;

  Board board;

  std::array<Piece, 2> playerPieces{
  Piece{Basepiece::PAWN, sf::Vector2i(1, 2)},
  Piece{Basepiece::PAWN, sf::Vector2i(2, 2)}
  };

  
public:

  TestState();
  ~TestState();
  
  void onEnter(Game &game);
  void onEvent(sf::Event event);
  std::shared_ptr<State> update(sf::RenderWindow& window);
  void render(sf::RenderWindow& window);
    
};


