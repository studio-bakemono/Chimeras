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
  float sectorSize;

  
  sf::Vector2f position = sf::Vector2f(100, 100);
  
  std::vector<std::vector<sf::FloatRect>> sectors;
  std::vector<std::vector<sf::RectangleShape>> debugSectors;

  std::vector<Piece*> pieces;
  int playerCount=2;
  int playerTurn=0;
  bool dragndrop=true;
  int pieceBeingMoved=0;
  
  
public:
  Board();
  Board(Game &game, sf::Vector2f position,
	int boardSize, float boardWidth, float boardHeight );

  ~Board();

  void colorWith(sf::Vector2i from, Piece &piece);
  void colorTurnMovables();
  void resetColor();
  void update(sf::RenderWindow& window);
  void onEvent(sf::Event event);
  void render(sf::RenderWindow& window);
  
  
};
