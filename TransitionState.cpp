/*
  Studio Bakemono, 2018
*/

#include "TransitionState.hpp"
#include "Game.hpp"

#include <iostream>

TransitionState::TransitionState(State* previousState, State* transitionState) {
  isTransition = true;
  
  transitionTo = transitionState;
  this->previousState = previousState;
}

TransitionState::~TransitionState() {
  transitionTo = nullptr;
}


void TransitionState::onEnter(Game& game) {

  timer.restart();
  std::cout << "Are we calling onEnter?" << std::endl;
  
}

void TransitionState::onEvent(sf::Event event) {

}

State* TransitionState::update(sf::RenderWindow& window) {

  if (timer.getElapsedTime().asSeconds() >= 3.f) {
    std::cout << "transitioning to new State!" << std::endl;
    return transitionTo;
  }
  else {
    std::cout << "Tester" << std::endl;
    return nullptr;
  }
}

void TransitionState::render(sf::RenderWindow& window) {

  if (previousState)
    previousState->render(window);
  
}
