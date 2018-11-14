/*
  Studio Bakemono, 2018
*/

#pragma once

#include "State.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
// Forward declaration, gets included in MenuState.cpp to avoid circular inclusion
class Game;
struct MenuItem;
class MenuState : public State {
public:

  sf::Text hello;
  std::vector<MenuItem> menuitems;
  sf::Font font;

  
public:

  MenuState(sf::Font font);
  ~MenuState();
  
  void onEnter(Game* game);

  void onEvent();
  
  State* update(sf::RenderWindow& window);

  void render(sf::RenderWindow& window);


  
};

//MenuItem struct for each button
struct MenuItem{
  std::string name;
  sf::RectangleShape rect;
  State* menState;
    
};
