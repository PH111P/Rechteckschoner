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

void rectangle::construct(int ccnt,int depth) {
  if(depth == 0)
    return;
  
  this->children.clear();
  std::vector<float> splitPoses;
  for(int i = 1; i < ccnt; ++i)
    splitPoses.push_back(rand() *1.0f / RAND_MAX);
  
  std::sort(splitPoses.begin(), splitPoses.end());
  
  bool hsplit = rand() % 2; //split horizontally?
  
  int px = this->posx, py = this->posy;
  int wd = hsplit ? this->width - (ccnt + 1) * rectangle::DistanceBetweenRectangles : 
      this->width - 2 * rectangle::DistanceBetweenRectangles;
  int hg = !hsplit ? this->height - (ccnt + 1) * rectangle::DistanceBetweenRectangles : 
      this->height - 2 * rectangle::DistanceBetweenRectangles;
      
  for(int i = 0; i < ccnt; ++i){
    this->children.add(
  }
}
void rectangle::draw( bitmap* res ) const {
  
}
  
int rectangle::writeTmp(FILE* tmp, int height, int width) {
  fprintf(tmp,"%lf %lf %lf %lf %lu ", this->getX() * 1.0 / width, this->getY() * 1.0 / height,
	  this->getWidth() * 1.0 / width, this->getHeight() * 1.0 / height, this->children.size());
  for(auto i : this->children)
    i->writeTmp(tmp, height, width);
  return 0;
}
static rectangle rectangle::readTmp(FILE* tmp,int width, int height, int maxChildren, int& regenTreePos) {
  double px,py, wd,hg;
  size_t ccnt;
  fscanf(tmp,"%lf %lf %lf %lf %lu",&px,&py, %wd,&hg, &ccnt);
  
  rectangle ret((int)(px * width),(int)(py * height),(int)(wd * width), (int)(hg * height));
  for(auto i = 0; i< ccnt; ++i){
    rectangle child = rectangle::readTmp(tmp, width,height, maxChildren- 1, --regenTreePos);
    ret.children.add(
  }
}