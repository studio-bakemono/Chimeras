/*
  Studio Bakemono, 2018
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "State.hpp"
#include "Board.hpp"
#include "Piece.hpp"

class Game;

class TestState : public State {
public:
  
  sf::Text greeting;
  sf::Clock clock;

  Board board;

public:

  TestState();
  ~TestState();
  
  void onEnter(Game &game);
  void onEvent(sf::Event event);
  std::shared_ptr<State> update(sf::RenderWindow& window);
  void render(sf::RenderWindow& window);
    
};


