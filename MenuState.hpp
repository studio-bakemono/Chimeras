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
#include <memory>

// Forward declaration, gets included in MenuState.cpp to avoid circular inclusion
class Game;

struct MenuItem;


class MenuState : public State {
public:

  sf::Text hello;

  uint8_t MENU_LENGTH = 0;
  std::vector<MenuItem> menuItems;  
  int selected = 0;


  sf::Texture backgroundTex;
  sf::Sprite background;
  sf::RectangleShape breathFader;
  sf::Color breathAlpha = sf::Color(0,0,0,220);
  bool isIncreasing = true;
  sf::Clock breathClock;
  float breathSpeedModifier = 0.3f;
  
  const int minBreath = 120;
  const int maxBreath = 220;

  bool transitioning = false;

  
public:

  MenuState();
  ~MenuState();

  void updateBreath(sf::Time timePassed);
  
  virtual void onEnter(Game &game);

  virtual void onEvent(sf::Event event);
  
  virtual std::shared_ptr<State> update(sf::RenderWindow& window);

  virtual void render(sf::RenderWindow& window);
  
};

//MenuItem struct for each button
struct MenuItem{
  std::string name;
  sf::Text displayText;
  sf::RectangleShape rect;
  std::function<std::shared_ptr<State>(MenuState *)> menState;


  inline void updateDisplayText() {
    displayText.setString(name.c_str());
  }
  
  MenuItem() {}
  MenuItem(std::string name) {
    this->name = name;
    displayText.setString(name);
  }
  
};
