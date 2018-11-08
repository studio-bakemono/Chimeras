/*
  Studio Bakemono, 2018
*/

#include "MenuState.hpp"


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

  hello.setString("Hello, Sailor!");
  hello.setFont(font);
  hello.setCharacterSize(20);
 
  hello.setPosition( sf::Vector2f(250,300) );
  
  
}


void MenuState::onEvent() {

}


State* MenuState::update(sf::RenderWindow& window) {


  return nullptr;
  
}

void MenuState::render(sf::RenderWindow& window) {

  window.draw(hello);
  
}



