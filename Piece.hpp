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

  Moveset moveset;
  
  sf::RectangleShape rect;
  sf::FloatRect collider;
  
  bool beingMoved = false;
  sf::FloatRect* snapRect = nullptr;
  
public:
  Piece();
  ~Piece();

  void consumeMoveset(Moveset moves, bool XORMode);

  void snapToGrid(sf::RenderWindow& window, Board& board);
  
  void update(sf::RenderWindow& window, Board& board);
  void render(sf::RenderWindow& window);
  
  

};
