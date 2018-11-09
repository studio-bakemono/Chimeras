/*
  Studio Bakemono, 2018
*/

#pragma once

#include <SFML/Graphics.hpp>


class Board {

public:

  sf::VertexArray gridLines;
  int boardSize = 8;
  int boardWidth, boardHeight;
  int sectorSize;
  
  sf::Vector2f position = sf::Vector2f(100, 100);
  

public:
  Board();
  Board(int boardSize, int boardWidth, int boardHeight );
  Board(sf::Vector2f position, int boardSize, int boardWidth, int boardHeight );
  ~Board();
  
  void update(sf::RenderWindow& window);
  void render(sf::RenderWindow& window);
  
  
};
