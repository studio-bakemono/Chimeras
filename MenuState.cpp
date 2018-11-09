/*
  Studio Bakemono, 2018
*/

#include "MenuState.hpp"

#include "State.hpp"
#include "Game.hpp"
#include "TestState.hpp"

MenuState::MenuState(sf::Font font) {
  //hello.setFont(font);
  //hello.setString("Hello, Sailor!");
  // hello.setCharacterSize(20);
  //hello.setFillColor(sf::Color::White);
  //hello.setFillColor(sf::Color::Red);

  this->font = font;

}


MenuState::~MenuState() {

}


void MenuState::onEnter(Game* game) {

  hello.setString("Chimeras");
  hello.setFont(font);
  hello.setCharacterSize(30);
 
  hello.setPosition(sf::Vector2f( game->window.getSize().x/2 - 10 - hello.getLocalBounds().width/2,
				  game->window.getSize().y/2 - hello.getLocalBounds().height/2 ));
  
  
}


void MenuState::onEvent() {

}


State* MenuState::update(sf::RenderWindow& window) {


  if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) )
    return new TestState(this->font);

  return nullptr;
  
}

void MenuState::render(sf::RenderWindow& window) {

  window.draw(hello);
  
}



