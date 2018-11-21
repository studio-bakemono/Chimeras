/*
  Studio Bakemono, 2018
*/
#pragma once


#include <SFML/Graphics.hpp>
#include <memory>

#include "State.hpp"

class Game;

class TransitionState : public State {
public:
  std::shared_ptr<State> previousState = nullptr;
  std::shared_ptr<State> transitionTo = nullptr;

  sf::Clock timer;
  
public:


  TransitionState(std::shared_ptr<State> transitionState);
  ~TransitionState();
  
  void onEnter(Game& game);
  void onEvent(sf::Event event);
  std::shared_ptr<State> update(sf::RenderWindow& window);
  void render(sf::RenderWindow& window);  

  
};
