/*
  Studio Bakemono, 2018
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Game;

struct State {
  virtual ~State() = 0;
  virtual void onEnter(Game &game) = 0;
  virtual void onEvent(sf::Event event) = 0;
  virtual std::shared_ptr<State> update(sf::RenderWindow& window) = 0;
  virtual void render(sf::RenderWindow& window) = 0;
};
