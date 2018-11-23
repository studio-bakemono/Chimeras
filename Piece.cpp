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


Piece::Piece(Game &game,  Board &board, Basepiece basepiece, sf::Vector2i sectorPosition, int player) :
  player(player),
  basepiece(basepiece) {
  facing_front = !player;
  consumeBasepiece(basepiece);
  switch (basepiece){
    case Basepiece::KING:
      moveset.offsets.push_back(sf::Vector2i( 1, 0));
      moveset.offsets.push_back(sf::Vector2i( 0, 1));
      moveset.offsets.push_back(sf::Vector2i(-1, 0));
      moveset.offsets.push_back(sf::Vector2i( 0,-1));
      break;
    case Basepiece::QUEEN:
      moveset.diagonal = true;
      moveset.horizontal = true;
      moveset.vertical = true;
      break;
    case Basepiece::PAWN:
      moveset.offsets.push_back(sf::Vector2i( 0, player ? -1 : 1));
      break;
    case Basepiece::ROOK:
      moveset.horizontal = true;
      moveset.vertical = true;
      break;
    case Basepiece::BISHOP:
      moveset.diagonal = true;
      break;
    case Basepiece::KNIGHT:
      moveset.offsets.push_back(sf::Vector2i( 1, 2));
      moveset.offsets.push_back(sf::Vector2i( 1,-2));
      moveset.offsets.push_back(sf::Vector2i(-1, 2));
      moveset.offsets.push_back(sf::Vector2i(-1,-2));

      moveset.offsets.push_back(sf::Vector2i( 2, 1));
      moveset.offsets.push_back(sf::Vector2i( 2,-1));
      moveset.offsets.push_back(sf::Vector2i(-2, 1));
      moveset.offsets.push_back(sf::Vector2i(-2,-1));
      break;
    case Basepiece::CIRCLE:
      moveset.circular = true;
      break;
  }

  rect.setTexture(game.atlas);
  atlas_width = game.atlas.getSize().x/SPRITE_SIZE;
  calculateTexCoord(0);
  rect.setScale(sf::Vector2f(1,1)*board.sectorSize/float(SPRITE_SIZE));

  // Get size from board
  size.x = board.sectorSize;
  size.y = board.sectorSize;

  // Apply sizes to rectangles
  collider.width = size.x;
  collider.height = size.y;

  
  snapToSector(sectorPosition, board);
  distributePosition();

}


Piece::~Piece() {
}

void Piece::consumePiece(Piece other) {
  consumeMoveset(other.moveset, other.player == player);
  consumeBasepiece(other.basepiece);
}


void Piece::consumeMoveset(Moveset moves, bool XORMode) {
  if (XORMode) {
    this->moveset = this->moveset ^ moves;
  }else{
    this->moveset = this->moveset || moves;
  }
}

void Piece::consumeBasepiece(Basepiece bp) {
  animal = combine_basepieces(basepiece, bp);
//  std::cout << "bp: " << bp << " us: " << basepiece << " animal: " << animal << std::endl;
  if (basepiece != Basepiece::KING) {
    basepiece = bp;
  }
}


void Piece::snapToSector(sf::Vector2i sector, Board& board) {
  position = sf::Vector2f( board.sectors[sector.y-1][sector.x-1].left, board.sectors[sector.y-1][sector.x-1].top );
}

bool Piece::validateMove(Board &board, sf::Vector2i sectorPosition, sf::Vector2i pos){
  // No stalling :3
  if (pos == sectorPosition){ 
    return false;
  }

  // Check infinite directional bools 	

  if (moveset.horizontal && sectorPosition.y == pos.y) {
    return true;
  }
  if (moveset.vertical && sectorPosition.x == pos.x) {
    return true;
  }
  if (moveset.diagonal &&
    abs(sectorPosition.x - pos.x) ==
    abs(sectorPosition.y - pos.y)) {
    return true;
  }
  if (moveset.circular){
    double const RAD = 3.0;
    double l = abs(sectorPosition.x - pos.x);
    double s = abs(sectorPosition.y - pos.y);
    if (l<s)
      std::swap(s,l);
    if(round(sqrt(RAD*RAD-s*s))==l){
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

void Piece::dropPiece(Board &board, sf::Vector2i &sectorPosition, sf::Vector2f mousepos)
{
  for ( int i = 0; i < board.sectors.size(); i++ ) {
    for ( int r = 0; r < board.sectors[i].size(); r++ ) {
      if ( board.sectors[r][i].contains(mousepos) ) {
        if(validateMove(board, sectorPosition, sf::Vector2i(i+1, r+1))){
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

void Piece::onEvent(sf::Vector2i &sectorPosition, sf::Event event, Board &board) {
  if ( beingMoved
       // Determine what control mode is being used, compare different events
    && event.type == (dragndrop ? sf::Event::MouseButtonReleased : sf::Event::MouseButtonPressed)
       // If mouse button is down
    && event.mouseButton.button == sf::Mouse::Button::Left) {
    beingMoved=false;
    calculateTexCoord(0);
    dropPiece(board, sectorPosition, sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y));
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
    board.colorWith(sectorPosition, *this);
  }
}



void Piece::update(sf::RenderWindow& window, Board& board) {
  if(dragndrop&&beingMoved)
    position = sf::Vector2f(sf::Mouse::getPosition(window))-size/2.f;
  
  distributePosition();
}


// TODO: Change time from int to sf::Time
void Piece::render(sf::RenderWindow& window, int time) {

  window.draw(rect);
  //TODO: Post Nov: Animate again (uses time param)
}

void Piece::calculateTexCoord(int time){
  int a = animal;
  a = a * 2 + (facing_front ? 0 : 1);
  a = a * 2 + (beingMoved ? 0 : 1);
//  std::cout<<"Sprite count: " << atlas_width*atlas_width << " Sprite id: " << a << std::endl;
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
