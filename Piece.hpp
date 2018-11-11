/*
  Studio Bakemono, 2018
*/

#pragma once

#include <SFML/Graphics.hpp>

class Board;

class Piece {
public:
  sf::Vector2f position;
  sf::Vector2f size;

  sf::RectangleShape rect(position, size);


public:

  Piece();
  ~Piece();


  
  void update(sf::RenderWindow& window, Board& board);
  void render(sf::RenderWindow& window);
  
  

};
