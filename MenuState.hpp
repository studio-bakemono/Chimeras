/*
  Studio Bakemono, 2018
*/

#pragma once

#include "State.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
// Forward declaration, gets included in MenuState.cpp to avoid circular inclusion
class Game;
struct MenuItem;
const int MenuLength = 2;
class MenuState : public State {
public:

  sf::Text hello;
  std::vector<MenuItem> menuitems;
  sf::Font font;
  int selected = 0;
  
public:

  MenuState(sf::Font font);
  ~MenuState();
  
  void onEnter(Game* game);

  void onEvent(sf::Event event);
  
  State* update(sf::RenderWindow& window);

  void render(sf::RenderWindow& window);


  
};

//MenuItem struct for each button
struct MenuItem{
  std::string name;
  sf::RectangleShape rect;
  State* menState;
    
};
