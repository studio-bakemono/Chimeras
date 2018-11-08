/*
  Studio Bakemono, 2018
*/

#pragma once

#include "State.hpp"
#include <SFML/Graphics.hpp>

class Game{
public:
  sf::RenderWindow window;
  sf::Font font;

  Game();
  void run();

private:
  State* state;
  void to_state(State*);

};
