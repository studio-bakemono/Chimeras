/*
  Studio Bakemono, 2018
*/

#pragma once

#include "State.hpp"
#include <SFML/Graphics.hpp>

class Game{
public:
  const uint16_t WINDOW_WIDTH = 600;
  const uint16_t WINDOW_HEIGHT = 600;
  const uint16_t FRAME_RATE = 60;

public:
  
  sf::RenderWindow window;
  sf::Font font;

  
  Game();
  ~Game();
  void run();

private:
  State* state;
  void to_state(State*);

};
