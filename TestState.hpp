/*
  Studio Bakemono, 2018
*/

#pragma once

#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "TestRectangle.hpp"
#include "Board.hpp"

// Forward delcaration to avoid circular headers

class Game;

class TestState : public State {
public:
  
  sf::Font font;
  sf::Text greeting;

  Board board;
  TestRectangle rectangle;
  
public:

  TestState(sf::Font font);
  ~TestState();
  
  void onEnter(Game* game);
  void onEvent();
  State* update(sf::RenderWindow& window);
  void render(sf::RenderWindow& window);
    
};


