/*
  Studio Bakemono, 2018
*/
#pragma once


#include <SFML/Graphics.hpp>

#include "State.hpp"

class Game;

class TransitionState : public State {
public:
  State* previousState = nullptr;
  State* transitionTo = nullptr;

  sf::Clock timer;
  
public:


  TransitionState(State* previousState, State* transitionState);
  ~TransitionState();
  
  void onEnter(Game& game);
  void onEvent(sf::Event event);
  State* update(sf::RenderWindow& window);
  void render(sf::RenderWindow& window);  

  
};
