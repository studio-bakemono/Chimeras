/*
  Studio Bakemono, 2018
*/

#pragma once

#include <SFML/Graphics.hpp>

#include "Moveset.hpp"

class Game;
class Board;

class Piece {
public:
  sf::Vector2f position = sf::Vector2f(20,20);
  bool dragndrop = true;

  sf::Vector2i sectorPosition = sf::Vector2i(4, 1);
  
  Moveset moveset;
  
  sf::Sprite rect;
  sf::FloatRect collider;
  
  bool beingMoved = false;

  
  sf::Vector2f origin;

  void dropPiece(Board &board, sf::Vector2f mousepos);
  
public:
  Piece();
  ~Piece();

  void consumeMoveset(Moveset moves, bool XORMode);
  void snapToSector(sf::Vector2i sector, Board &board);
  bool validateMove(Board &board, sf::Vector2i pos);

  void onEnter(Game &game, Board &board);
  void update(sf::RenderWindow &window, Board &board);
  void onEvent(sf::Event event, Board &board);
  void render(sf::RenderWindow& window);
  void distributePosition();
  

};
