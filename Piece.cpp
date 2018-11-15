/*
  Studio Bakemono, 2018
*/

#include "Piece.hpp"
#include "Board.hpp"

#include <iostream>

Piece::Piece() {

  rect.setFillColor(sf::Color::Blue);  
  rect.setSize(this->size);
  rect.setPosition(this->position); 
  collider.top = this->position.y;
  collider.left = this->position.x;
  collider.width = this->size.x;
  collider.height = this->size.y;  
}


Piece::~Piece() {
}

void Piece::onEvent(sf::Event event, Board &board) {
  if ( event.type == sf::Event::MouseButtonPressed
    && event.mouseButton.button == sf::Mouse::Button::Left) {
    if ( beingMoved ) {
      for ( int i = 0; i < board.sectors.size(); i++ ) {
        for ( int r = 0; r < board.sectors[i].size(); r++ ) {
          if ( board.sectors[i][r].contains(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y)) ) {
            sf::FloatRect snapRect = board.sectors[i][r];

            this->position.x = snapRect.left;
            this->position.y = snapRect.top;

            this->rect.setPosition(this->position);

            collider.top = this->position.y;
            collider.left = this->position.x;
            collider.width = this->size.x;
            collider.height = this->size.y;  

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

void Piece::render(sf::RenderWindow& window) {
  window.draw(rect);
  
}
