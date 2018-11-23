/*
  Studio Bakemono, 2018
*/
#pragma once


#include <SFML/Graphics.hpp>

class Moveset {
public:

  bool horizontal;
  bool vertical;
  bool diagonal;
  bool circular;
  
  std::vector<sf::Vector2i> offsets;


  Moveset operator||(const Moveset& m ) {
    Moveset ret;

    // Just ORs the flags
    ret.horizontal = (this->horizontal || m.horizontal);
    ret.vertical = (this->vertical || m.vertical);
    ret.diagonal = (this->diagonal || m.diagonal);
    ret.circular = (this->circular || m.circular);

    
    // Load off left side's offsets into return 
    for (auto a : this->offsets) {
      ret.offsets.push_back(a);
    }

    // If right side has an offet ret doesn't push it back to ret's offsets
    for (auto a : ret.offsets) {
      //ugly bool because goto's are frowned upon
      bool push = true;
      for ( auto b : m.offsets ) {
	if ( a == b ){
          push=false;
          break;
        }
      }
      if(push)
        ret.offsets.push_back(a);
    }
    return ret;
  }

  Moveset operator^(const Moveset& m ) {
    Moveset ret;

    // Just XOR the flags
    ret.horizontal = (this->horizontal ^ m.horizontal);
    ret.vertical = (this->vertical ^ m.vertical);
    ret.diagonal = (this->diagonal ^ m.diagonal);
    ret.circular = (this->circular ^ m.circular);

    
    // If right side has an offet ret doesn't push it back to ret's offsets
    for (auto a : ret.offsets) {
      for ( auto b : m.offsets ) {
      	if ( a == b )
          goto continueOuterLoop;
      }
      ret.offsets.push_back(a);
      continueOuterLoop:
      continue;
    }
    return ret;
  }

  
};
