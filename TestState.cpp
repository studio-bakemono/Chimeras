/*
  Studio Bakemono, 2018
*/

#include "TestState.hpp"
#include "GameOverState.hpp"
#include "TransitionState.hpp"
#include "Game.hpp"

//#include "Board.hpp"

#include <iostream>

TestState::TestState() {
}

TestState::~TestState() {
}

void TestState::onEnter(Game& game) {

  // greeting.setString("TestState");
  // greeting.setFont(game.font);
  // greeting.setCharacterSize(20);
  // greeting.setPosition(0,0);


  // Determine render width and height of board inside window
  // One Variable since the board is a square
  float boardDimensions;

  // boardWidth = game.boardScale * (float)game.WINDOW_WIDTH/2;
  boardDimensions = game.boardScale * (float)game.WINDOW_HEIGHT;

  std::cout << "boardDimensions: " << boardDimensions << std::endl;
  

  // Set position relative to boardScale 
  auto position = sf::Vector2f( ((float)game.WINDOW_WIDTH)/8,
				((float)game.WINDOW_HEIGHT)/2.f -boardDimensions/2.f);
  
  
  board = Board(game, position, 8, boardDimensions, boardDimensions);
}

void TestState::onEvent(sf::Event event) {
  board.onEvent(event);
}

std::shared_ptr<State> TestState::update(sf::RenderWindow& window) {

  board.update(window);
  switch (board.won_player){
    case -1:
    case -3:
      break;
    case -2:{
      auto tie = std::make_shared<TransitionState>(std::make_shared<GameOverState>("Tie! You're all losers!"));
      board.won_player=-3;
      return tie;
    }
    default:{
      auto go = std::make_shared<TransitionState>(std::make_shared<GameOverState>("Player "+std::to_string(board.won_player)+" Won!"));
      board.won_player=-3;
      return go;
    }
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
