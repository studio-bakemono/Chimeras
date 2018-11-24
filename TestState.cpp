/*
  Studio Bakemono, 2018
*/

#include "TestState.hpp"
#include "Game.hpp"

//#include "Board.hpp"

#include <iostream>

TestState::TestState() {
}

TestState::~TestState() {
}

void TestState::onEnter(Game &game) {

  greeting.setString("TestState");
  greeting.setFont(game.font);
  greeting.setCharacterSize(20);
  greeting.setPosition(0,0);

  float boardWidth, boardHeight;

  boardWidth = 0.75f * (float)game.WINDOW_WIDTH;
  boardHeight = 0.75f * (float)game.WINDOW_HEIGHT;

  
  auto position = sf::Vector2f( ((float)game.WINDOW_WIDTH)/2.f -boardWidth/2.f,
				((float)game.WINDOW_HEIGHT)/2.f -boardHeight/2.f);
  
  
  board = Board(game, position, 8, boardWidth, boardHeight);
}

void TestState::onEvent(sf::Event event) {
  board.onEvent(event);
}

std::shared_ptr<State> TestState::update(sf::RenderWindow& window) {

  board.update(window);

  for(auto &piece : board.pieces) {
    if(piece)
      piece->update(window, board);
  }
  
  return nullptr;
}

void TestState::render(sf::RenderWindow& window) {

  window.draw(greeting);

  board.render(window);
  for(auto &piece : board.pieces) {
    if(piece)
      piece->render(window, clock.getElapsedTime().asMilliseconds());
  }
}
