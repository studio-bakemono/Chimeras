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
  
  std::vector<sf::Vector2i> offsets;


  Moveset operator||(const Moveset& m ) {
    Moveset ret;

    // Just ORs the flags
    ret.horizontal = (this->horizontal || m.horizontal);
    ret.vertical = (this->vertical || m.vertical);
    ret.diagonal = (this->diagonal || m.diagonal);

    
    // Load off left side's offsets into return 
    for (auto a : this->offsets) {
      ret.offsets.push_back(a);
    }

    // If right side has an offet ret doesn't push it back to ret's offsets
    for (auto a : ret.offsets) {
      for ( auto b : m.offsets ) {
	if ( a != b )
	  ret.offsets.push_back(b);
      }
    }
    return ret;
  }

  
};
