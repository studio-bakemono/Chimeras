/*
  Studio Bakemono, 2018
*/

#pragma once

#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "Board.hpp"
#include "Piece.hpp"

// Forward delcaration to avoid circular headers

class Game;

class TestState : public State {
public:
  
  sf::Font font;
  sf::Text greeting;

  Board board;
  Piece testPiece;
  
  
public:

  TestState(sf::Font font);
  ~TestState();
  
  void onEnter(Game* game);
  void onEvent(sf::Event event);
  State* update(sf::RenderWindow& window);
  void render(sf::RenderWindow& window);
    
};


