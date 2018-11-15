/*
  Studio Bakemono, 2018
*/

#include "Piece.hpp"
#include "Board.hpp"

#include <iostream>
#include <cstdio>


Piece::Piece() {

  rect.setFillColor(sf::Color::Blue);  
  rect.setSize(size);
  // Test knight code
  moveset.offsets.push_back(sf::Vector2i(1,2));

  collider.width = size.x;
  collider.height = size.y;

  distributePosition();
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


void Piece::snapToSector(sf::Vector2i sector, Board& board) {
  position = sf::Vector2f( board.sectors[sector.y-1][sector.x-1].left, board.sectors[sector.y-1][sector.x-1].top );
}

<<<<<<< HEAD
=======
/*
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

void Piece::snapToGrid(sf::RenderWindow& window, Board& board) {
  for ( int i = 0; i < board.sectors.size(); i++ ) {
    for ( int r = 0; r < board.sectors[i].size(); r++ ) {
      
      if ( board.sectors[r][i].contains((sf::Vector2f)sf::Mouse::getPosition(window))
	   && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) ) {

	snapRect = &board.sectors[r][i];
	snapRectSector =
	  sf::Vector2i( i+1, r+1 );
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

      }
     
      // If we couldn't find an offset to match 
      if (!foundValidMove)
	snapToOrigin(window, board);

      
    }
    beingMoved = false;
    originRect = nullptr;
  }
  
  if (beingMoved && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) ) {
    this->position = (sf::Vector2f)sf::Mouse::getPosition(window) - size/2.f;
  }
  

}
*/

>>>>>>> De-jank piece movement
void Piece::onEvent(sf::Event event, Board &board) {
  if ( event.type == sf::Event::MouseButtonPressed
    && event.mouseButton.button == sf::Mouse::Button::Left) {
    if ( beingMoved ) {
      for ( int i = 0; i < board.sectors.size(); i++ ) {
        for ( int r = 0; r < board.sectors[i].size(); r++ ) {
          if ( board.sectors[r][i].contains(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y)) ) {
            for (auto m : moveset.offsets) {  
<<<<<<< HEAD
              if ( sf::Vector2i(i+1, r+1) == sectorPosition+m ) {
                sf::FloatRect snapRect = board.sectors[r][i];

                position.x = snapRect.left;
                position.y = snapRect.top;
                distributePosition();

                sectorPosition += m;
                break;
              } else {
                std::cout << "SectorPosition: "
                  << sectorPosition.x<<", "<<sectorPosition.y << "\n"
                  << "2i: "
                  << i <<", "<< r << "\n"
                  << "m: "
                  << m.x <<", "<< m.y << std::endl;
=======
              if ( sf::Vector2i(i,r) == sectorPosition+m ) {
                sf::FloatRect snapRect = board.sectors[r][i];
                this->position.x = snapRect.left;
                this->position.y = snapRect.top;

                this->rect.setPosition(this->position);

                collider.top = this->position.y;
                collider.left = this->position.x;
                sectorPosition += m;
                break;
              } else {
                std::cout << "SectorPosition: ";
                std::cout << sectorPosition.x<<","<<sectorPosition.y << "\n"; 
>>>>>>> De-jank piece movement
              }
            }

            rect.setFillColor(sf::Color::Blue);
            beingMoved=false;

            return;
          }
        }
      }
    }else if ( collider.contains( sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y)) ) {
      // Pick piece up
      beingMoved=true;
      rect.setFillColor(sf::Color::Green);
    }
  }
}



void Piece::onEnter(Board& board) {
  snapToSector(sectorPosition, board);
}

void Piece::update(sf::RenderWindow& window, Board& board) {

  /*
  this->rect.setPosition(this->position);
  
  this->collider.top = this->position.y;
  this->collider.left = this->position.x;
  this->collider.width = this->size.x;
  this->collider.height = this->size.y;
*/
  //snapToGrid(window, board);
  
}

void Piece::render(sf::RenderWindow& window) {
  window.draw(rect);
  
}

void Piece::distributePosition(){
  rect.setPosition(position); 
  collider.top = position.y;
  collider.left = position.x;
}
