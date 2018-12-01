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

class Game;

class GameOverState : public State {
public:

  sf::Text message;

  sf::Texture backgroundTex;
  sf::Sprite background;

  sf::RectangleShape breathFader;
  sf::Color breathAlpha = sf::Color(0,0,0,220);
  sf::Clock breathClock;
  float breathSpeedModifier = 0.3f;
  bool exited=false;

  const int minBreath = 120;
  const int maxBreath = 220;
  const float stateDuration = 5.0f;
  
public:

  GameOverState(std::string text);
  ~GameOverState();

  void updateBreath(sf::Time timePassed);
  
  virtual void onEnter(Game &game);

  virtual void onEvent(sf::Event event);
  
  virtual std::shared_ptr<State> update(sf::RenderWindow& window);

  virtual void render(sf::RenderWindow& window);
  
};
