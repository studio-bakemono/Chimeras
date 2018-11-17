/*
  Studio Bakemono, 2018
*/
#include "Board.hpp"
#include "Game.hpp"
#include "Piece.hpp"

#include <iostream>

Board::Board() {
  
}

Board::Board(Game &game, int boardSize, float boardWidth, float boardHeight) {
  
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

Board::Board(Game &game, sf::Vector2f position,
	     int boardSize, float boardWidth, float boardHeight ) {


  this->position = position;
  this->boardSize = boardSize;
  
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


  
  sectors.resize(boardSize);
  for (int i = 0; i < sectors.size(); i++) {
    sectors[i].resize(boardSize);
  }
  
  

  debugSectors.resize(boardSize);
  for (int i = 0; i < debugSectors.size(); i++) {
    debugSectors[i].resize(boardSize);
  }
  
  
  for (int i = 0; i < boardSize; i++) {
    for (int r = 0; r < boardSize; r++) {

      sectors[i][r].left = position.x+sectorSize*r;
      sectors[i][r].top = position.y+sectorSize*i;
      sectors[i][r].width = sectorSize;
      sectors[i][r].height = sectorSize;

      
      
      debugSectors[i][r].setPosition(sf::Vector2f( position.x +sectorSize*r,
					   position.y+sectorSize*i ));
      
      debugSectors[i][r].setSize(sf::Vector2f(sectorSize, sectorSize));
      
    }
   }
   resetColor();  
  
}

Board::~Board() {

}

void Board::colorWith(Piece *piece) {
  // Draw the chessboard checkered pattern
  sf::Color colors[] = {
    sf::Color::White,
    sf::Color::Black,
    sf::Color(55,255,55),
    sf::Color(0,100,0),
  };
  for (int i = 0; i < boardSize; i++) {
    for (int r = 0; r < boardSize; r++) {
      debugSectors[r][i].setFillColor(colors[(r%2^i%2)+2*(piece->validateMove(*this, sf::Vector2i(i+1,r+1)))]);
    }
  }
}

void Board::resetColor() {
  // Draw the chessboard checkered pattern
  for (int i = 0; i < boardSize; i++) {
    for (int r = 0; r < boardSize; r++) {
      if ( (r%2^i%2)==0)
        debugSectors[r][i].setFillColor(sf::Color::White);
      else
        debugSectors[r][i].setFillColor(sf::Color::Black);
    }
  }
}

void Board::update(sf::RenderWindow& window) {

  for (int i = 0; i < boardSize; i++) {
    for (int r = 0; r < boardSize; r++) {

      if (sectors[r][i].contains(sf::Mouse::getPosition(window).x,
				 sf::Mouse::getPosition(window).y )) {

	/*
	std::cout << "Mouse is in sector [" << r+1 << "," << i+1 << "]" <<
	  "at posiiton: " << sf::Mouse::getPosition(window).x << " "
		  << sf::Mouse::getPosition(window).y << std::endl;
	*/
      }
    }
  }
  
  
}

void Board::render(sf::RenderWindow& window) {

  for ( int s = 0; s < debugSectors.size(); s++ ) {
    for (int r = 0; r < debugSectors[s].size(); r++ ) {
      window.draw(debugSectors[r][s]);
    }
  }

  window.draw(gridLines);
  
}
