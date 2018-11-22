/*
  Studio Bakemono, 2018
*/

#include "Piece.hpp"
#include "Game.hpp"
#include "Board.hpp"
#include "config.hpp"

#include <iostream>
#include <cstdio>
#include <cmath>


Piece::Piece() {

  // Test knight code
  moveset.horizontal = false;
  moveset.vertical = false;
  moveset.diagonal = true;
  moveset.circular = true;
  moveset.offsets.push_back(sf::Vector2i(1,2));

  distributePosition();
}


Piece::~Piece() {
}

void Piece::consumePiece(Piece other, bool XORMode) {
  consumeMoveset(other.moveset, XORMode);
  consumeBasepiece(other.basepiece);
}


void Piece::consumeMoveset(Moveset moves, bool XORMode) {
  if (XORMode) {
    //TODO: XOR mode
    this->moveset = this->moveset || moves;
  }else{
    this->moveset = this->moveset || moves;
  }
}

void Piece::consumeBasepiece(Basepiece bp) {
  animal = combine_basepieces(basepiece, bp);
  if (basepiece != Basepiece::KING) {
    basepiece = bp;
  }
}


void Piece::snapToSector(sf::Vector2i sector, Board& board) {
  position = sf::Vector2f( board.sectors[sector.y-1][sector.x-1].left, board.sectors[sector.y-1][sector.x-1].top );
}

bool Piece::validateMove(Board &board, sf::Vector2i pos){

  // Check infinite directional bools 	

  if (moveset.horizontal) {
    if (sectorPosition.y == pos.y) {
      return true;
    }
  }
  if (moveset.vertical) {
    if (sectorPosition.x == pos.x) {
      return true;
    }
  }
  if (moveset.diagonal) {
    if (abs(sectorPosition.x - pos.x) ==
        abs(sectorPosition.y - pos.y)) {
      return true;
    }
  }
  if (moveset.circular){
    if (floor(sqrt(pow(sectorPosition.x - pos.x, 2.0) +pow(sectorPosition.y - pos.y, 2.0))) == 2)
    {
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

void Piece::dropPiece(Board &board, sf::Vector2f mousepos)
{
  for ( int i = 0; i < board.sectors.size(); i++ ) {
    for ( int r = 0; r < board.sectors[i].size(); r++ ) {
      if ( board.sectors[r][i].contains(mousepos) ) {
        if(validateMove(board, sf::Vector2i(i+1, r+1))){
          sf::FloatRect snapRect = board.sectors[r][i];
          sectorPosition=sf::Vector2i(i+1, r+1);
          position.x = snapRect.left;
          position.y = snapRect.top;
          distributePosition();
          return;
        }
      }
    }
  }
  if (dragndrop){
    position=origin;
    distributePosition();
  }
}

void Piece::onEvent(sf::Event event, Board &board) {
  if ( beingMoved
    && event.type == (dragndrop ? sf::Event::MouseButtonReleased : sf::Event::MouseButtonPressed)
    && event.mouseButton.button == sf::Mouse::Button::Left) {
    beingMoved=false;
    calculateTexCoord(0);
    dropPiece(board, sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y));
    board.resetColor();
  }
  if ((!beingMoved)
    && event.type == sf::Event::MouseButtonPressed
    && event.mouseButton.button == sf::Mouse::Button::Left
    && collider.contains( sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y)) ) {
    // Pick piece up
    beingMoved=true;
    calculateTexCoord(0);
    origin=position;
    board.colorWith(this);
  }
}



void Piece::onEnter(Game &game, Board &board) {
  rect.setTexture(game.atlas);
  atlas_width = game.atlas.getSize().x/SPRITE_SIZE;
  calculateTexCoord(0);
  rect.setScale(sf::Vector2f(1,1)*board.sectorSize/float(SPRITE_SIZE));
  collider.width = board.sectorSize;
  collider.height = board.sectorSize;

  snapToSector(sectorPosition, board);
  distributePosition();
}

void Piece::update(sf::RenderWindow& window, Board& board) {
}

void Piece::render(sf::RenderWindow& window, int time) {
  if(dragndrop&&beingMoved){
    position=(sf::Vector2f)sf::Mouse::getPosition(window);
    distributePosition();
  }
  window.draw(rect);
  //TODO: Post Nov: Animate again
}

void Piece::calculateTexCoord(int time){
  int a = animal;
  a = a * 2 + (facing_front ? 0 : 1);
  a = a * 2 + (beingMoved ? 0 : 1);
  rect.setTextureRect(sf::IntRect(
    SPRITE_SIZE * (a % atlas_width),
    SPRITE_SIZE * (a / atlas_width),
    SPRITE_SIZE, SPRITE_SIZE
  ));
}



void Piece::distributePosition(){
  rect.setPosition(position); 
  collider.top = position.y;
  collider.left = position.x;
}
