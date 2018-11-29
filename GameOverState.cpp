/*
  Studio Bakemono, 2018
*/

#include "GameOverState.hpp"

#include "State.hpp"
#include "Game.hpp"
#include "TransitionState.hpp"
#include "MenuState.hpp"

#include <cmath>
#include <cstdint>


GameOverState::GameOverState(std::string text) {
  message.setString(text);
}


GameOverState::~GameOverState() {

}


void GameOverState::updateBreath(sf::Time timePassed) {

  uint8_t alpha = (uint8_t)(
    minBreath +
     (1.0+sin(timePassed.asSeconds()*breathSpeedModifier*M_PI))
      *(maxBreath-minBreath)/2.0
  );
  breathAlpha.a = alpha;
  breathFader.setFillColor(breathAlpha);
}
void GameOverState::onEnter(Game &game) {

  //Set up the win message
  message.setFont(game.font);
  message.setCharacterSize(40);
  message.setPosition(sf::Vector2f(
    game.window.getSize().x/2 - message.getLocalBounds().width /2 - 10,
		game.window.getSize().y/2 - message.getLocalBounds().height/2
  ));
  
  // Load main menu
  //if ( !

  
  backgroundTex.loadFromFile("assets/main_menu.png");
  background.setTexture(backgroundTex);

  sf::Vector2f backgroundScale = sf::Vector2f(game.WINDOW_WIDTH/background.getLocalBounds().width,
					      game.WINDOW_HEIGHT/background.getLocalBounds().height);

  
  
  background.scale(backgroundScale );
//std::cout << "Error Loading main_menu.png!" << std::endl;


  breathClock.restart();
  
  breathFader.setPosition(0,0);
  breathFader.setSize(sf::Vector2f(game.WINDOW_WIDTH, game.WINDOW_HEIGHT));
  

}


void GameOverState::onEvent(sf::Event event) {
}


std::shared_ptr<State> GameOverState::update(sf::RenderWindow& window) {

  auto elapsed = breathClock.getElapsedTime();
  updateBreath(elapsed);
  
  if ( !exited && elapsed.asSeconds() > stateDuration ){
    exited=true;
    return std::make_shared<TransitionState>(std::make_shared<MenuState>());
  }
  
  return nullptr;
}

void GameOverState::render(sf::RenderWindow& window) {

  window.draw(background);

  window.draw(breathFader);
  
  window.draw(message);
  
}





