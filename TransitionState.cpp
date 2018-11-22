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
  fader.setSize(sf::Vector2f(game.WINDOW_WIDTH,
			     game.WINDOW_HEIGHT));

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
    
    if (alpha.a < 255 && alpha.a!=255) {

      if (alpha.a+fadeSpeed <= 255)
	alpha.a+=fadeSpeed;
      else
	alpha.a = 255;
      
    }

    fader.setFillColor(alpha);

    return nullptr;
  }
}

void TransitionState::render(sf::RenderWindow& window) {

  if (previousState)
    previousState->render(window);

  window.draw(fader);
}
