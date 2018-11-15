/*
  Studio Bakemono, 2018
*/

#pragma once

#include <SFML/Graphics.hpp>

class Board;

class Piece {
public:
  sf::Vector2f position = sf::Vector2f(20,20);
  sf::Vector2f size = sf::Vector2f(64, 64);
  
  sf::RectangleShape rect;
  sf::FloatRect collider;
  
  bool beingMoved = false;
  
public:
  Piece();
  ~Piece();

  void onEvent(sf::Event event, Board& board);
  void render(sf::RenderWindow& window);
  
  

};
