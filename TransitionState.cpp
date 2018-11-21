/*
  Studio Bakemono, 2018
*/

#include "TransitionState.hpp"
#include "Game.hpp"

#include <iostream>

TransitionState::TransitionState(std::shared_ptr<State> transitionState) : transitionTo(transitionState){
}

TransitionState::~TransitionState() {
}


void TransitionState::onEnter(Game& game) {
  previousState = game.get_state();
  timer.restart();
  std::cout << "Are we calling onEnter?" << std::endl;
  
}

void TransitionState::onEvent(sf::Event event) {

}

std::shared_ptr<State> TransitionState::update(sf::RenderWindow& window) {

  if (timer.getElapsedTime().asSeconds() >= 3.f) {
    std::cout << " transitioning to new State!" << std::endl;
    return transitionTo;
  }
  else {
    std::cout<<"."<<std::flush;
    return nullptr;
  }
}

void TransitionState::render(sf::RenderWindow& window) {

  if (previousState)
    previousState->render(window);
  
}
