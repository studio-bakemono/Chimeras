/*
  Studio Bakemono, 2018
*/

#include "Piece.hpp"
#include "Board.hpp"

#include <iostream>
#include <cstdio>


Piece::Piece() {

  
  rect.setSize(this->size);
  rect.setPosition(this->position); 

  // Test knight code
  moveset.diagonal = true;
  moveset.offsets.push_back(sf::Vector2i(1,2));

  
}


Piece::~Piece() {
  snapRect = nullptr;
  originRect = nullptr;
}



void Piece::consumeMoveset(Moveset moves, bool XORMode) {
  if (!XORMode) {
    this->moveset = this->moveset || moves;
  }
}



sf::FloatRect& Piece::getOriginRect(sf::RenderWindow& window, Board& board) {
  for ( int i = 0; i < board.sectors.size(); i++ ) {
    for ( int r = 0; r < board.sectors[i].size(); r++ ) {
      
      if ( board.sectors[r][i].contains((sf::Vector2f)sf::Mouse::getPosition(window)) ) {
	originRectSector = sf::Vector2i(i-1, r-1);
	return board.sectors[r][i];
      }
    }
  }
}



void Piece::Piece::snapToOrigin(sf::RenderWindow& window, Board& board) {
  if (originRect)
    position = sf::Vector2f(originRect->left, originRect->top);
}

void Piece::snapToSector(sf::Vector2i sector, Board& board) {
  position = sf::Vector2f( board.sectors[sector.y-1][sector.x-1].left, board.sectors[sector.y-1][sector.x-1].top );
}

void Piece::snapToGrid(sf::RenderWindow& window, Board& board) {
  for ( int i = 0; i < board.sectors.size(); i++ ) {
    for ( int r = 0; r < board.sectors[i].size(); r++ ) {
      
      if ( board.sectors[r][i].contains((sf::Vector2f)sf::Mouse::getPosition(window))
	   && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) ) {

	snapRect = &board.sectors[r][i];
	snapRectSector =
	  sf::Vector2i( i+1, r+1 );
      }
    }
  }

  if (collider.contains((sf::Vector2f)sf::Mouse::getPosition(window))
      && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
    
    beingMoved = true;
    if (!originRect)
      originRect = &getOriginRect(window, board);
    
  }
  else if ( beingMoved && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

    if (snapRect) {
      if (originRect) {
	foundValidMove = false;

	std::cout << "DEBUG: snapRect pos["<<snapRect->left<<","<<snapRect->top<<"]"<< std::endl;
	std::cout << "DEBUG: snapRect Sector ["<<snapRectSector.x<<","<<snapRectSector.y<<"]"<< std::endl;

	// Check infinite directional bools 
	
	if (moveset.horizontal) {
	  if (sectorPosition.y == snapRectSector.y) {
	    std::cout << "horizontal\n";
	    this->position.x = snapRect->left;
	    this->position.y = snapRect->top;
	    foundValidMove = true;
	    sectorPosition = snapRectSector;
	  }
	}
	else if (moveset.vertical) {
	  if (sectorPosition.x == snapRectSector.x) {
	    std::cout << "vertical\n";
	    this->position.x = snapRect->left;
	    this->position.y = snapRect->top;
	    foundValidMove = true;
	    sectorPosition = snapRectSector;
	  }
	}
	else if (moveset.diagonal) {
	  if (sectorPosition.x != snapRectSector.x &&
	      sectorPosition.y != snapRectSector.y) {

	    std::cout << "diagonal\n";
	    this->position.x = snapRect->left;
	    this->position.y = snapRect->top;
	    foundValidMove = true;
	    sectorPosition = snapRectSector;
	  }
	}

	// Check offsets for valid moves
	for (auto m : moveset.offsets) {
	  
	  if ( snapRectSector == sectorPosition+m ) {
	    this->position.x = snapRect->left;
	    this->position.y = snapRect->top;
	    foundValidMove = true;
	    sectorPosition += m;
	    break;
	  }
	  else {
	    std::cout << "SectorPosition: ";
	    std::cout << sectorPosition.x<<","<<sectorPosition.y << "\n"; 
	  }	  
	}
      }
     
      // If we couldn't find a valid move, snap piece back to origin 
      if (!foundValidMove)
	snapToOrigin(window, board);

      
    }
    beingMoved = false;
    originRect = nullptr;
  }
  
  if (beingMoved && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) ) {
    this->position = (sf::Vector2f)sf::Mouse::getPosition(window) - size/2.f;
  }
  

  /*
    NOTE: The movement MUST be separated as above in order to work correctly.
    Toy with it at your own risk.
  */
  
}



void Piece::onEnter(Board& board) {
  snapToSector(sectorPosition, board);
}

void Piece::update(sf::RenderWindow& window, Board& board) {

  
  this->rect.setPosition(this->position);
  
  this->collider.top = this->position.y;
  this->collider.left = this->position.x;
  this->collider.width = this->size.x;
  this->collider.height = this->size.y;

  snapToGrid(window, board);
  
}

void Piece::render(sf::RenderWindow& window) {
  window.draw(rect);
  
}
