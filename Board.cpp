/*
  Studio Bakemono, 2018
*/
#include "Board.hpp"


#include <iostream>

Board::Board() {
  
}

Board::Board(int boardSize, int boardWidth, int boardHeight) {
  
  gridLines.setPrimitiveType(sf::Lines);
  gridLines.resize(boardSize*2);

  
  if ( boardWidth < boardHeight )
    sectorSize = boardWidth/boardSize;
  else 
    sectorSize = boardHeight/boardSize;
  
    
  for (int i = 0; i <= boardSize; i++) {
    gridLines.append( sf::Vector2f(position.x, position.y+sectorSize*i) );
    gridLines.append( sf::Vector2f(position.x+boardWidth, position.y+sectorSize*i) );
    std::cout << i << std::endl;
  }

  for (int i = 0; i <= boardSize; i++) {
    gridLines.append( sf::Vector2f(position.x+sectorSize*i, position.y) );
    gridLines.append( sf::Vector2f(position.x+sectorSize*i, position.y+boardHeight) );
    std::cout << i << std::endl;
  }  

  
}

Board::Board(sf::Vector2f position, int boardSize, int boardWidth, int boardHeight ) {

  this->position = position;
  /*
    std::cout << position.x << std::endl << position.y << std::endl;
    Board(boardSize, boardWidth, boardHeight);
  */


  gridLines.setPrimitiveType(sf::Lines);
  gridLines.resize(boardSize*2);

  
  if ( boardWidth < boardHeight )
    sectorSize = boardWidth/boardSize;
  else 
    sectorSize = boardHeight/boardSize;
  
    
  for (int i = 0; i <= boardSize; i++) {
    gridLines.append( sf::Vector2f(position.x, position.y+sectorSize*i) );
    gridLines.append( sf::Vector2f(position.x+boardWidth, position.y+sectorSize*i) );
    std::cout << i << std::endl;
  }

  for (int i = 0; i <= boardSize; i++) {
    gridLines.append( sf::Vector2f(position.x+sectorSize*i, position.y) );
    gridLines.append( sf::Vector2f(position.x+sectorSize*i, position.y+boardHeight) );
    std::cout << i << std::endl;
  }  

  
}

Board::~Board() {

}

void Board::update(sf::RenderWindow& window) {

}

void Board::render(sf::RenderWindow& window) {

  window.draw(gridLines);
  
}
