/*
  Studio Bakemono, 2018

  Composes images into an atlas
*/
#include <Magick++.h>
#include <iostream>
#include <cassert>

#include "../config.hpp"
#include "../Basepiece.hpp"

using namespace std;
using namespace Magick;

int main( int /*argc*/, char ** argv)
{
  InitializeMagick(*argv);
  Image atlas;
  try {
    // Read in the background, so that missing sprites have a unique error texture
    atlas.read("err_tex.png");
atlas.crop( Geometry( ATLAS_SIZE, ATLAS_SIZE, 0, 0 ) );
    // s & l : small and large
    int animal = 0;
    int const ATLAS_SPRITEW = ATLAS_SIZE / SPRITE_SIZE;

    // For drawing holes
//    atlas.fillColor("rgba(0,0,0,100)");
    atlas.fillColor("magenta");
    for(int l = 0; l < Basepiece::LEN; l++){
      for(int s = 0; s <= l; s++){
        int t_animal = combine_basepieces((Basepiece)s, (Basepiece)l);
        if (t_animal != animal){
          cout << "Animal numbering mismatch! Expected: " << animal << " Calculated: " << t_animal << endl;
        }
        Image in;
        try {
          // Read in the animal
          std::string animal_filename = basepiece_to_string((Basepiece)l)+basepiece_to_string((Basepiece)s)+".png";
          cout<<"Reading animal #"<<animal<<" from \""<<animal_filename<<"\".. ";
          in.read(animal_filename);
          int off = animal * SPRITES_PER_ANIMAL;
          for(int face=0;face<2;face++){
            for(int frame=0;frame<2;frame++){
              Image sprite = in;
              sprite.crop( Geometry( SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE*face, SPRITE_SIZE*frame ) );
              int x = (off % ATLAS_SPRITEW) * SPRITE_SIZE;
              int y = (off / ATLAS_SPRITEW) * SPRITE_SIZE;
              atlas.draw( DrawableRectangle(x, y, x+SPRITE_SIZE, y+SPRITE_SIZE) );
              atlas.composite( sprite, x, y, OverCompositeOp );
              off++;
            }
          }
          cout << "Success!" << endl;
        }catch(Exception &error){
          cout << "Failed! Exception: " << error.what() << endl;
        }
        animal++;
      }
    }
    atlas.transparent("magenta");
    atlas.write("../assets/atlas.png");
  }catch(Exception &error){
    cerr << "Caught fatal exception: " << error.what() << endl;
    return 1;
  }
  return 0;
}
