/*
  Studio Bakemono, 2018
*/

#include "Piece.hpp"
#include "Board.hpp"

#include <iostream>
#include <cstdio>
#include <cmath>


Piece::Piece() {

  rect.setFillColor(sf::Color::Blue);  
  rect.setSize(size);
  // Test knight code
  moveset.horizontal = false;
  moveset.vertical = false;
  moveset.diagonal = true;
  moveset.offsets.push_back(sf::Vector2i(1,2));

  collider.width = size.x;
  collider.height = size.y;

  distributePosition();
}


Piece::~Piece() {
}

void Piece::consumeMoveset(Moveset moves, bool XORMode) {
  if (!XORMode) {
    this->moveset = this->moveset || moves;
  }
}


void Piece::snapToSector(sf::Vector2i sector, Board& board) {
  position = sf::Vector2f( board.sectors[sector.y-1][sector.x-1].left, board.sectors[sector.y-1][sector.x-1].top );
}

bool Piece::validateMove(Board &board, sf::Vector2i pos){

	// Check infinite directional bools 
	
	if (moveset.horizontal) {
	  if (sectorPosition.y == pos.y) {
	    std::cout << "horizontal\n";
	    return true;
	  }
	}
	else if (moveset.vertical) {
	  if (sectorPosition.x == pos.x) {
	    std::cout << "vertical\n";
	    return true;
	  }
	}
	else if (moveset.diagonal) {
	  if (abs(sectorPosition.x - pos.x) ==
	      abs(sectorPosition.y - pos.y)) {

	    std::cout << "diagonal\n";
	    return true;
	  }
	}
	// Check offsets for valid moves
            for (auto m : moveset.offsets) {  
              if ( pos == sectorPosition+m ) {
                return true;
              }
            }
  return false;
}

void Piece::onEvent(sf::Event event, Board &board) {
  if ( beingMoved
    && event.type == (dragndrop ? sf::Event::MouseButtonReleased : sf::Event::MouseButtonPressed)
    && event.mouseButton.button == sf::Mouse::Button::Left) {
    for ( int i = 0; i < board.sectors.size(); i++ ) {
      for ( int r = 0; r < board.sectors[i].size(); r++ ) {
        if ( board.sectors[r][i].contains(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y)) ) {
          if(validateMove(board, sf::Vector2i(i+1, r+1))){
            sf::FloatRect snapRect = board.sectors[r][i];
            sectorPosition=sf::Vector2i(i+1, r+1);
            position.x = snapRect.left;
            position.y = snapRect.top;
            distributePosition();
          }else if (dragndrop){
            position = origin;
            distributePosition();
          }
          rect.setFillColor(sf::Color::Blue);
          board.resetColor();
          beingMoved=false;

          return;
        }
      }
    }
  }
  if ((!beingMoved)
    && event.type == sf::Event::MouseButtonPressed
    && event.mouseButton.button == sf::Mouse::Button::Left
    && collider.contains( sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y)) ) {
    // Pick piece up
    beingMoved=true;
    rect.setFillColor(sf::Color::Green);
    origin=position;
    board.colorWith(this);
  }
}



void Piece::onEnter(Board& board) {
  snapToSector(sectorPosition, board);
}

void Piece::update(sf::RenderWindow& window, Board& board) {
}

void Piece::render(sf::RenderWindow& window) {
  if(dragndrop&&beingMoved){
    position=(sf::Vector2f)sf::Mouse::getPosition(window)-size/2.0f;
    distributePosition();
  }
  window.draw(rect);
}

void Piece::distributePosition(){
  rect.setPosition(position); 
  collider.top = position.y;
  collider.left = position.x;
}
