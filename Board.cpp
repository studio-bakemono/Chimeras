/*
  Studio Bakemono, 2018
*/
#include "Board.hpp"
#include "Game.hpp"
#include "Piece.hpp"

#include <iostream>
#include <cassert>

Board::Board() {
  
}

int const QUAD[8][2] = {
  {0, 0}, {1, 0},
  {0, 1}, {1, 1},
  {0, 0}, {0, 1},
  {1, 0}, {1, 1},
};


Board::Board(Game &game, sf::Vector2f position,
	     int boardSize, float boardWidth, float boardHeight ) {


  this->position = position;
  this->boardSize = boardSize;
  
  gridLines.setPrimitiveType(sf::Lines);
  gridLines.resize(boardSize*2);

  
  if ( boardWidth < boardHeight ) 
    sectorSize = boardWidth/(float)boardSize;
  else 
    sectorSize = boardHeight/(float)boardSize;
  
    
  for (int i = 0; i < sizeof(QUAD)/sizeof(QUAD[0]); i++) {
    gridLines.append( sf::Vector2f(position.x+QUAD[i][0]*boardWidth, position.y+QUAD[i][1]*boardHeight) );
  }
  
  sectors.resize(boardSize);
  for (int i = 0; i < sectors.size(); i++) {
    sectors[i].resize(boardSize);
  }
  
  

  debugSectors.resize(boardSize);
  for (int i = 0; i < debugSectors.size(); i++) {
    debugSectors[i].resize(boardSize);
  }
  
  
  for (int i = 0; i < boardSize; i++) {
    for (int r = 0; r < boardSize; r++) {

      sectors[i][r].left = position.x+sectorSize*r;
      sectors[i][r].top = position.y+sectorSize*i;
      sectors[i][r].width = sectorSize;
      sectors[i][r].height = sectorSize;

      
      
      debugSectors[i][r].setPosition(sf::Vector2f( position.x +sectorSize*r,
					   position.y+sectorSize*i ));
      
      debugSectors[i][r].setSize(sf::Vector2f(sectorSize, sectorSize));
      
    }
   }

  //#### Add pieces to board
  //TODO: Extend board to higher sizes
  Basepiece const CHESS_ORDER[8] = {
    Basepiece::ROOK,
    Basepiece::KNIGHT,
    Basepiece::BISHOP,
    Basepiece::KING,
    Basepiece::QUEEN,
    Basepiece::KNIGHT,
    Basepiece::CIRCLE,
    Basepiece::ROOK,
  };
  assert(boardSize<=sizeof(CHESS_ORDER)/sizeof(CHESS_ORDER[0]));
  pieces.reserve(boardSize*boardSize);
  for(int y=0; y < boardSize; y++){
    for(int x=0; x < boardSize; x++){
      bool player;
      if(y < 2){
        player=false;
      }else if(boardSize-y-1 < 2){
        player=true;
      }else{
        pieces.push_back(nullptr);
        continue;
      }
      pieces.push_back(new Piece(game, *this,
        (y%(boardSize-1)) ? Basepiece::PAWN : CHESS_ORDER[player?x:(boardSize-x-1)],
        sf::Vector2i(x+1, y+1), player));
    }
  }
  //resetColor();  
  colorTurnMovables();
}

Board::~Board() {

}

void Board::colorWith(sf::Vector2i from, Piece &piece) {
  // Draw the chessboard checkered pattern
  sf::Color colors[] = {
    sf::Color::White,
    sf::Color::Black,
    sf::Color(55,255,55),
    sf::Color(0,100,0),
  };
  for (int y = 0; y < boardSize; y++) {
    for (int x = 0; x < boardSize; x++) {
      debugSectors[y][x].setFillColor(colors[(x%2^y%2)+2*(piece.validateMove(*this, sf::Vector2i(x-from.x, y-from.y), from))]);
    }
  }
}

void Board::colorTurnMovables() {
  // Draw the chessboard checkered pattern
  sf::Color colors[] = {
    sf::Color::White,
    sf::Color::Black,
    sf::Color(255,55,55),
    sf::Color(100,0,0),
  };
  for (int x = 0; x < boardSize; x++) {
    for (int y = 0; y < boardSize; y++) {
      auto piece = pieces[x+y*boardSize];
      debugSectors[y][x].setFillColor(colors[(x%2^y%2)+2*(piece&&(playerTurn==piece->player))]);
    }
  }
}


void Board::resetColor() {
  // Draw the chessboard checkered pattern
  for (int i = 0; i < boardSize; i++) {
    for (int r = 0; r < boardSize; r++) {
      if ( (r%2^i%2)==0)
        debugSectors[r][i].setFillColor(sf::Color::White);
      else
        debugSectors[r][i].setFillColor(sf::Color::Black);
    }
  }
}

void Board::update(sf::RenderWindow& window) {
  for(auto &piece : pieces) {
    if(piece)
      piece->update(window, *this);
  }
}

void Board::onEvent(sf::Event event){
  //Quick exit, for when transitioning from this state to gameOver
  if(won_player!=-1)
    return;
  
  //We immediately assume the event is a mouse position,
  // and if it isn't, we simply won't use the garbage values we just computed.

  // sectorPosition is the cell we are moving to
  sf::Vector2i sectorPosition;
  //Are we Out Of Bounds?
  bool oob;
  {
    //rel is the relative position of the mouse, and is irrelevant outside of this block
    sf::Vector2f rel (
      (event.mouseButton.x-position.x)/sectorSize,
      (event.mouseButton.y-position.y)/sectorSize
    );
    sectorPosition = sf::Vector2i(rel.x, rel.y);
    oob = (
      rel.x < 0 || rel.y < 0 // Rel and not sectorPos, because of rounding issues
      || sectorPosition.x >= boardSize
      || sectorPosition.y >= boardSize
    );
  }

  if ( pieceBeingMoved
    && event.type == (dragndrop ? sf::Event::MouseButtonReleased : sf::Event::MouseButtonPressed)
    && event.mouseButton.button == sf::Mouse::Button::Left
  ){
    pieceBeingMoved--;
    auto piece = pieces[pieceBeingMoved];
    piece->beingMoved=false;
    //dropPiece(*this, sectorPosition, sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y));
    sf::Vector2i pos (
      (pieceBeingMoved%boardSize),
      (pieceBeingMoved/boardSize)
    );
    if( !oob && piece->validateMove(*this, sectorPosition-pos, pos)){
      pieces[pieceBeingMoved]=nullptr;
      auto sectorIndex = sectorPosition.x+sectorPosition.y*boardSize;
      auto prey = pieces[sectorIndex];
      pieces[sectorIndex] = piece;
      if (prey){
        piece->consumePiece(*prey);
        delete prey;
        //Check for game over!
        checkGameOver();
      }
      sf::FloatRect snapRect = sectors[sectorPosition.y][sectorPosition.x];
      piece->position.x = snapRect.left;
      piece->position.y = snapRect.top;
      piece->distributePosition();
      playerTurn = (playerTurn+1)%playerCount;
    }else{
      piece->position = piece->origin;
    }
    pieceBeingMoved=0;
    piece->calculateTexCoord(0);
    colorTurnMovables();
  }else if ((!pieceBeingMoved) && (!oob)
    && event.type == sf::Event::MouseButtonPressed
    && event.mouseButton.button == sf::Mouse::Button::Left
  ){
    //pieceBeingMoved is offset by one most of the time, to let 0 be null
    pieceBeingMoved=1+sectorPosition.x+sectorPosition.y*boardSize;
    auto piece = pieces[pieceBeingMoved-1];
    if(piece && piece->player == playerTurn){
      // Pick piece up
      piece->beingMoved=true;
      piece->calculateTexCoord(0);
      piece->origin=piece->position;
      colorWith(sectorPosition, *piece);
    }else{
      //oops! theres no piece here.
      // 0 indicates no moving piece
      pieceBeingMoved=0;
    }
  }
}

void Board::checkGameOver(){
  std::vector<bool> pHasKing;
  pHasKing.resize(playerCount, false);
  for (int y = 0; y < boardSize; y++) {
    for (int x = 0; x < boardSize; x++) {
      auto piece = pieces[x+y*boardSize];
      if (piece && !pHasKing[piece->player]){
        pHasKing[piece->player] = piece->basepiece == Basepiece::KING;
      }
    }
  }
  int kingCount=0;
  for( int p = 0; p<playerCount; p++){
    if (pHasKing[p]){
      //temporary, they havn't won _yet_
      won_player = p;
      kingCount++;
    }
  }
  switch(kingCount){
    case 0:
      //TIE!?
      won_player=-2;
      break;
    case 1:
      //Somebody won!
      //We already set won_player to them..
      break;
    default:
      //Game must go on..
      won_player=-1;
      break;
  }
}

void Board::render(sf::RenderWindow& window) {

  for ( int s = 0; s < debugSectors.size(); s++ ) {
    for (int r = 0; r < debugSectors[s].size(); r++ ) {
      window.draw(debugSectors[r][s]);
    }
  }

  window.draw(gridLines);
  
}
