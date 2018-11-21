/*
  Studio Bakemono, 2018
*/

#pragma once

#include "State.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class Game{
public:
  const uint16_t WINDOW_WIDTH = 600;
  const uint16_t WINDOW_HEIGHT = 600;
  const uint16_t FRAME_RATE = 60;

public:
  
  sf::RenderWindow window;
  sf::Font font;
  sf::Texture atlas;
  
  Game();
  ~Game();
  void run();
  std::shared_ptr<State> get_state();

private:
  std::shared_ptr<State> state;
  void to_state(std::shared_ptr<State>);

};
