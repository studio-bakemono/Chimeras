/*
  Studio Bakemono, 2018
*/

#include "TestState.hpp"
#include "Game.hpp"


TestState::TestState(sf::Font font) {

  this->font = font;
  
}

TestState::~TestState() {

}

void TestState::onEnter(Game* game) {

  greeting.setString("TestState");
  greeting.setFont(font);
  greeting.setCharacterSize(20);
  greeting.setPosition(0,0);


  board = Board(8, 600, 600);
  
  
}

void TestState::onEvent() {

}

State* TestState::update(sf::RenderWindow& window) {


  
  
  
  return nullptr;
}

void TestState::render(sf::RenderWindow& window) {

  window.draw(greeting);

  board.render(window);
  rectangle.render(window);  
}
