/*
  Studio Bakemono, 2018
*/
#include "Board.hpp"
#include "Game.hpp"

#include <iostream>

Board::Board() {
  
}

Board::Board(Game* game, int boardSize, float boardWidth, float boardHeight) {
  
  gridLines.setPrimitiveType(sf::Lines);
  gridLines.resize(boardSize*2);

  if ( boardWidth < boardHeight ) {
    sectorSize = boardWidth/(float)boardSize;
  }
  else {
    sectorSize = boardHeight/(float)boardSize;
  }
    
  for (int i = 0; i <= boardSize; i++) {
    gridLines.append( sf::Vector2f(position.x, position.y+sectorSize*i) );
    gridLines.append( sf::Vector2f(position.x+boardWidth, position.y+sectorSize*i) );
  }

  for (int i = 0; i <= boardSize; i++) {
    gridLines.append( sf::Vector2f(position.x+sectorSize*i, position.y) );
    gridLines.append( sf::Vector2f(position.x+sectorSize*i, position.y+boardHeight) );
  }  

  
}

Board::Board(Game* game, sf::Vector2f position,
	     int boardSize, float boardWidth, float boardHeight ) {


  game->WINDOW_WIDTH;
  
  this->position = position;
  
  gridLines.setPrimitiveType(sf::Lines);
  gridLines.resize(boardSize*2);

  
  if ( boardWidth < boardHeight )
    sectorSize = boardWidth/(float)boardSize;
  else 
    sectorSize = boardHeight/(float)boardSize;
  
    
  for (int i = 0; i <= boardSize; i++) {
    gridLines.append( sf::Vector2f(position.x, position.y+sectorSize*i) );
    gridLines.append( sf::Vector2f(position.x+boardWidth, position.y+sectorSize*i) );
  }

  for (int i = 0; i <= boardSize; i++) {
    gridLines.append( sf::Vector2f(position.x+sectorSize*i, position.y) );
    gridLines.append( sf::Vector2f(position.x+sectorSize*i, position.y+boardHeight) );
  }  

}

Board::~Board() {

}

void Board::update(sf::RenderWindow& window) {

}

void Board::render(sf::RenderWindow& window) {

  window.draw(gridLines);
  
}
