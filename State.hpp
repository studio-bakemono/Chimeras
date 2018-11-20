/*
  Studio Bakemono, 2018
*/

#pragma once

#include <SFML/Graphics.hpp>

class Game;

struct State {
  bool isTransition = false;
  virtual ~State() = 0;
  virtual void onEnter(Game &game) = 0;
  virtual void onEvent(sf::Event event) = 0;
  virtual State *update(sf::RenderWindow& window) = 0;
  virtual void render(sf::RenderWindow& window) = 0;
};
