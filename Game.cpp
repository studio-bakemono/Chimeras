/*
  Studio Bakemono, 2018
*/

#include "Game.hpp"

#include "State.hpp"
#include "MenuState.hpp"

#include <cassert>
#include <iostream>


Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chimeras",
		      // No resize button on our window
		      sf::Style::Close,
		      // (feature we're not using, feature we're not using, AntiAliasing level 8, more optional args are unset..)
		      sf::ContextSettings(0, 0, 8)){
  window.setFramerateLimit(FRAME_RATE);
  if(!atlas.loadFromFile("assets/atlas.png")) {
    std::cerr << "Error loading texture atlas" << std::endl;
  }
  atlas.setSmooth(false);
  if(!font.loadFromFile("assets/RockSalt-Regular.ttf")) {
    std::cerr << "Error loading font" << std::endl;
  }
  state = std::make_shared<MenuState>();
  state->onEnter(*this);
}

Game::~Game() {

}

std::shared_ptr<State> Game::get_state(){
  return state;
}

void Game::to_state(std::shared_ptr<State> newstate){
  if(newstate!=state){
    //state->onLeave(window);
    newstate->onEnter(*this);
    state = newstate;
  }
}

void Game::run(){
  while ( window.isOpen() ) {
    sf::Event event;
    while (window.pollEvent(event)) {
	    if (event.type == sf::Event::Closed) {

        // if the window gets closed
        window.close();
        return;

      } else {
        state->onEvent(event);
      }
    }

    // Update
    std::shared_ptr<State> next = state->update(window);
    if(next){
      to_state(next);
      continue;
    }

    // Render
    window.clear();

    state->render(window);
              
    window.display();
  }
}
