/*
  Studio Bakemono, 2018
*/

#include "TestState.hpp"
#include "Game.hpp"

//#include "Board.hpp"

#include <iostream>

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

  float boardWidth, boardHeight;

  boardWidth = (3* game->WINDOW_WIDTH)/4.f;
  boardHeight = (3* game->WINDOW_HEIGHT)/4.f;

  
  auto position = sf::Vector2f( game->WINDOW_WIDTH/2.f -boardWidth/2.f,
				game->WINDOW_HEIGHT/2.f -boardHeight/2.f);
  
  
  board = Board(game, position, 8, boardWidth, boardHeight);
  

  testPiece.position = position;
  //testPiece.rect.setPosition(position);
  testPiece.rect.setSize(sf::Vector2f(board.sectorSize, board.sectorSize));
  testPiece.size = sf::Vector2f(board.sectorSize, board.sectorSize);
  testPiece.rect.setFillColor(sf::Color::Blue);
  
}

void TestState::onEvent(sf::Event event) {

}

State* TestState::update(sf::RenderWindow& window) {

  board.update(window);
  testPiece.update(window, board);
  

  
  
  return nullptr;
}

void TestState::render(sf::RenderWindow& window) {

  window.draw(greeting);

  board.render(window);
  testPiece.render(window);
  
}
