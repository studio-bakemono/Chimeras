/*
  Studio Bakemono, 2018
*/

#include "Piece.hpp"
#include "Board.hpp"

#include <iostream>

Piece::Piece() {

  
  rect.setSize(this->size);
  rect.setPosition(this->position); 


  // TEST CODE
  /*
  auto moves = { sf::Vector2i(0,1) };
  moveset.offsets = moves;
  */
  
  
}


Piece::~Piece() {
  snapRect = nullptr;
}



void Piece::consumeMoveset(Moveset moves, bool XORMode) {

  if (!XORMode) {
    this->moveset = this->moveset || moves;
  }
  
}


void Piece::snapToGrid(sf::RenderWindow& window, Board& board) {

  this->rect.setPosition(this->position);
  
  this->collider.top = this->position.y;
  this->collider.left = this->position.x;
  this->collider.width = this->size.x;
  this->collider.height = this->size.y;

  
  for ( int i = 0; i < board.sectors.size(); i++ ) {
    for ( int r = 0; r < board.sectors[i].size(); r++ ) {
      
      if ( board.sectors[i][r].contains((sf::Vector2f)sf::Mouse::getPosition(window))
	   && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) ) {

	snapRect = &board.sectors[i][r];
	
      }
    }
  }

  if (collider.contains((sf::Vector2f)sf::Mouse::getPosition(window))
      && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
	
    beingMoved = true;

  }
  else if ( beingMoved && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
	    ) {

    if (snapRect) {
      this->position.x = snapRect->left;
      this->position.y = snapRect->top;
      beingMoved = false;
    }  
  }
  
  if (beingMoved && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) ) {
    this->position = (sf::Vector2f)sf::Mouse::getPosition(window) - size/2.f;
  }
  

  /*
    NOTE: The movement MUST be separated as above in order to work correctly.
    Toy with it at your own risk.
  */
  
}

void Piece::update(sf::RenderWindow& window, Board& board) {


  
  snapToGrid(window, board);

  
  
  
}

void Piece::render(sf::RenderWindow& window) {
  window.draw(rect);
  
}
