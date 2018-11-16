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

void Piece::onEvent(sf::Event event, Board &board) {
  if ( event.type == sf::Event::MouseButtonPressed
    && event.mouseButton.button == sf::Mouse::Button::Left) {
    if ( beingMoved ) {
      for ( int i = 0; i < board.sectors.size(); i++ ) {
        for ( int r = 0; r < board.sectors[i].size(); r++ ) {
          if ( board.sectors[r][i].contains(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y)) ) {
            for (auto m : moveset.offsets) {  
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
              if ( sf::Vector2i(i,r) == sectorPosition+m ) {
                sf::FloatRect snapRect = board.sectors[r][i];

                position.x = snapRect.left;
                position.y = snapRect.top;
                distributePosition();

                sectorPosition += m;
                break;
              } else {
                std::cout << "SectorPosition: ";
                std::cout << sectorPosition.x<<","<<sectorPosition.y << "\n"; 
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

}

void Piece::render(sf::RenderWindow& window) {
  window.draw(rect);
  
}

void Piece::distributePosition(){
  rect.setPosition(position); 
  collider.top = position.y;
  collider.left = position.x;
}
