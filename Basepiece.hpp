#include <algorithm>
#include <string>
#include <iostream>

enum Basepiece{
  PAWN, // Penguin
  ROOK,  // Bear
  BISHOP, // Raccoon
  KNIGHT, // Fish
  QUEEN, // Cat
  KING, // Lion
  CIRCLE, //Circle
  LEN
};

/*
 This is almost a pairing function,
   except it maps a pair of integers to the same number when the order is reversed.
 See: https://en.wikipedia.org/wiki/Pairing_function
*/
inline int combine_basepieces(Basepiece one, Basepiece two){
    if ( one > two )
      std::swap(one, two);
    return one + two * (two + 1) / 2;
}

inline std::string basepiece_to_string(Basepiece piece){
  static std::string BASEPIECE_NAME[] = {
    "Pawn",
    "Rook",
    "Bishop",
    "Knight",
    "Queen",
    "King",
    "Circle",
  };
  return BASEPIECE_NAME[piece];
}

inline std::ostream& operator<<(std::ostream &strm, const Basepiece &bp) {
  return strm << basepiece_to_string(bp);
}


