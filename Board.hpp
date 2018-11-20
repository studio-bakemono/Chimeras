/*
  Studio Bakemono, 2018
*/

#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

// Forward declarations to avoid circular inclusions
class Game;
class Piece;

class Board {

public:

  sf::VertexArray gridLines;
  int boardSize = 8;
  int boardWidth, boardHeight;
  float sectorSize;

  
  sf::Vector2f position = sf::Vector2f(100, 100);
  
  std::vector<std::vector<sf::FloatRect>> sectors;
  std::vector<std::vector<sf::RectangleShape>> debugSectors;

  
  
public:
  Board();
  Board(Game &game, sf::Vector2f position,
	int boardSize, float boardWidth, float boardHeight );

  ~Board();

  void colorWith(Piece &piece);
  void resetColor();
  void update(sf::RenderWindow& window);
  void render(sf::RenderWindow& window);
  
  
};
