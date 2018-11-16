/*
  Studio Bakemono, 2018
*/

#pragma once

#include <SFML/Graphics.hpp>

#include "Moveset.hpp"

class Board;

class Piece {
public:
  sf::Vector2f position = sf::Vector2f(20,20);
  sf::Vector2f size = sf::Vector2f(64, 64);

  sf::Vector2i sectorPosition = sf::Vector2i(4, 1);
  
  Moveset moveset;
  
  sf::RectangleShape rect;
  sf::FloatRect collider;
  
  bool beingMoved = false;
  sf::FloatRect* snapRect = nullptr;
  sf::Vector2i snapRectSector;

  bool foundValidMove;
  
  
  sf::FloatRect* originRect = nullptr;
  sf::Vector2i originRectSector = sf::Vector2i(0, 0);
  
public:
  Piece();
  ~Piece();

  void consumeMoveset(Moveset moves, bool XORMode);

  sf::FloatRect& getOriginRect(sf::RenderWindow& window, Board& board);

  void snapToSector(sf::Vector2i sector, Board& board);
  void snapToOrigin(sf::RenderWindow& window, Board& board);
  void snapToGrid(sf::RenderWindow& window, Board& board);

  void onEnter(Board& board);
  void update(sf::RenderWindow& window, Board& board);
  void onEvent(sf::Event event, Board& board);
  void render(sf::RenderWindow& window);
  void distributePosition();  
  

};
