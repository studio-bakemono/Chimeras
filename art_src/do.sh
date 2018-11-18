#!/bin/sh
clang++ atlas.cpp -o atlas `GraphicsMagick++-config --cppflags --cxxflags --ldflags --libs`&&
./atlas&&
rm atlas
