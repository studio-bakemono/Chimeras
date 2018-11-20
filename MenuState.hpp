/*
  Studio Bakemono, 2018
*/

#pragma once

#include "State.hpp"
#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>
#include <cstdint>
#include <functional>

// Forward declaration, gets included in MenuState.cpp to avoid circular inclusion
class Game;

struct MenuItem;


class MenuState : public State {
public:

  sf::Text hello;

  const uint8_t MENU_LENGTH = 2;
  std::vector<MenuItem> menuItems;  
  int selected = 0;
  
public:

  MenuState();
  ~MenuState();
  
  void onEnter(Game &game);

  void onEvent(sf::Event event);
  
  State* update(sf::RenderWindow& window);

  void render(sf::RenderWindow& window);
  
};

//MenuItem struct for each button
struct MenuItem{
  std::string name;
  sf::Text displayText;
  sf::RectangleShape rect;
  std::function<State*(MenuState *)> menState;


  inline void updateDisplayText() {
    displayText.setString(name.c_str());
  }
  
  MenuItem() {}
  MenuItem(std::string name) {
    this->name = name;
    displayText.setString(name);
  }
  
};
