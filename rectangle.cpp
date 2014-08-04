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

#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>


#include "rectangle.h"

int rectangle::getX() const { return this->posx; }
int rectangle::getY() const { return this->posy; }
int rectangle::getWidth() const { return this->width; }
int rectangle::getHeight() const { return this->height; }

void rectangle::construct(int depth) {
  if(depth == 0)
    return;
  
  int ccnt = this->children.size();
  std::vector<float> splitPoses;
  for(int i = 1; i < ccnt; ++i)
    splitPoses.push_back(rand() *1.0f / RAND_MAX);
  
  std::sort(splitPoses.begin(), splitPoses.end());
  
  
}
void rectangle::draw( bitmap* res ) const {
  
}
  
int rectangle::writeTmp(FILE* tmp) {
  fprintf(tmp,"%d %d %d %d %lu ", this->getX(), this->getY(),
	  this->getWidth(), this->getHeight(), this->children.size());
  for(auto i : this->children)
    i->writeTmp(tmp);
  return 0;
}
int rectangle::readTmp(FILE* tmp, int regenTreePos) {
  return -1;
}