//
// Copyright (c) 2014 Philip Wellnitz
//

//
// This file is part of "Rechteckschoner".
//
// "Rechteckschoner" is distributed to be useful, but need not
// to be. Further it is distributed WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or 
// FITNESS FOR A PARTICULAR PURPOSE.
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//

#pragma once
#include <vector>
#include <cstdio>

struct bitmap;

class rectangle {
private:
  int posx,		//x position of the top-left corner
      posy,		//y position of the top-left corner
      width,		//rectangle's width
      height;		//rectangle's height
  
  int numChildren;	//number of max enclosed rectangles
  
public:
  std::vector<rectangle> children;
  static int DistanceBetweenRectangles;
  
  int getX () const;
  int getY () const;
  int getWidth () const;
  int getHeight () const;
  
  rectangle() {}
  rectangle(int posX, int posY, int rectWidth, int rectHeight, int maxChildren)
    : posx(posX), posy(posY), width(rectWidth), height(rectHeight), numChildren(maxChildren) { }
  
  void construct(int children,int depth);
  void draw( bitmap* res ) const;
  
  int writeTmp(FILE* tmp);
  static rectangle readTmp(FILE* tmp,int width, int height,int maxChildren, int& regenTreePos);
};