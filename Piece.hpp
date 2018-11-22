/*
  Studio Bakemono, 2018
*/

#pragma once

#include <SFML/Graphics.hpp>

#include "Moveset.hpp"
#include "Basepiece.hpp"

class Game;
class Board;

class Piece {
public:

  // Size and position; defaults are for debug
  sf::Vector2f position = sf::Vector2f(20,20);
  sf::Vector2f size = sf::Vector2f(64, 64); 
  bool dragndrop = true;

  sf::Vector2i sectorPosition = sf::Vector2i(4, 1);
  
  Moveset moveset;
  
  sf::Sprite rect;
  sf::FloatRect collider;
  
  bool beingMoved = false;

  
  sf::Vector2f origin;

  void dropPiece(Board &board, sf::Vector2f mousepos);

  int atlas_width;
  bool facing_front = true;
  int animal;
  Basepiece basepiece = Basepiece::PAWN;

public:
  Piece();
  ~Piece();

  void consumePiece(Piece other, bool XORMode);
    void consumeMoveset(Moveset moves, bool XORMode);
    void consumeBasepiece(Basepiece other);

  void snapToSector(sf::Vector2i sector, Board &board);
  bool validateMove(Board &board, sf::Vector2i pos);

  void distributePosition();
  void calculateTexCoord(int time);


  void onEnter(Game &game, Board &board);
  void update(sf::RenderWindow &window, Board &board);
  void onEvent(sf::Event event, Board &board);
  void render(sf::RenderWindow& window, int time);
  

};
