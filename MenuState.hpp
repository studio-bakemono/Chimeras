/*
  Studio Bakemono, 2018
*/

#pragma once

#include "State.hpp"

// Forward declaration, gets included in MenuState.cpp to avoid circular inclusion
class Game;

class MenuState : public State {
public:

  sf::Text hello;

  sf::Font font;

  
public:

  MenuState(sf::Font font);
  ~MenuState();
  
  void onEnter(Game* game);

  void onEvent();
  
  State* update(sf::RenderWindow& window);

  void render(sf::RenderWindow& window);


  
};
