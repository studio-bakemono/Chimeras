#include <SFML/Graphics.hpp>
#include "Piece.hpp"


#include <vector>

struct Pieces{
  std::vector<Piece> playerPieces{
    {Basepiece::PAWN, sf::Vector2i(1, 2)},
    {Basepiece::PAWN, sf::Vector2i(2, 2)},
    {Basepiece::PAWN, sf::Vector2i(3, 2)},
    {Basepiece::PAWN, sf::Vector2i(4, 2)},
    {Basepiece::PAWN, sf::Vector2i(5, 2)},
    {Basepiece::PAWN, sf::Vector2i(6, 2)},
    {Basepiece::PAWN, sf::Vector2i(7, 2)},
    {Basepiece::PAWN, sf::Vector2i(8, 2)},

    {Basepiece::ROOK, sf::Vector2i(1, 1)},
    {Basepiece::KNIGHT, sf::Vector2i(2, 1)},
    {Basepiece::BISHOP, sf::Vector2i(3, 1)},
    {Basepiece::QUEEN, sf::Vector2i(4, 1)},
    {Basepiece::KING, sf::Vector2i(5, 1)},
    {Basepiece::BISHOP, sf::Vector2i(6, 1)},
    {Basepiece::KNIGHT, sf::Vector2i(7, 1)},
    {Basepiece::ROOK, sf::Vector2i(8, 1)},    
  };

  std::vector<Piece> enemyPieces{
    {Basepiece::PAWN, sf::Vector2i(1, 7)},
    {Basepiece::PAWN, sf::Vector2i(2, 7)},
    {Basepiece::PAWN, sf::Vector2i(3, 7)},
    {Basepiece::PAWN, sf::Vector2i(4, 7)},
    {Basepiece::PAWN, sf::Vector2i(5, 7)},
    {Basepiece::PAWN, sf::Vector2i(6, 7)},
    {Basepiece::PAWN, sf::Vector2i(7, 7)},
    {Basepiece::PAWN, sf::Vector2i(8, 7)},

    {Basepiece::ROOK, sf::Vector2i(1, 8)},
    {Basepiece::KNIGHT, sf::Vector2i(2, 8)},
    {Basepiece::BISHOP, sf::Vector2i(3, 8)},
    {Basepiece::QUEEN, sf::Vector2i(4, 8)},
    {Basepiece::KING, sf::Vector2i(5, 8)},
    {Basepiece::BISHOP, sf::Vector2i(6, 8)},
    {Basepiece::KNIGHT, sf::Vector2i(7, 8)},
    {Basepiece::ROOK, sf::Vector2i(8, 8)},    
  };

};
