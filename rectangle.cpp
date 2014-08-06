//
// Copyright (c) 2014 Philip Wellnitz
//

//
// This file is part of "Rechteckschoner".
//
// "Rechteckschoner" is distributed to be useful, but need not
// to be. Further, it is distributed WITHOUT ANY WARRANTY;
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
#include <queue>
#include <map>

#include "rectangle.h"
#include "bitmap.h"

void rectangle::construct(int ccnt,int depth) {
  this->children.clear();
  if(depth == 0)
    return;
  
  std::vector<float> splitPoses;
  for(int i = 1; i < ccnt; ++i)
    splitPoses.push_back(rand() *1.0f / RAND_MAX); 
  splitPoses.push_back(1); 
  std::sort(splitPoses.begin(), splitPoses.end());
  
  for(int i = 0; i < ccnt; ++i){
    rectangle c1(rand() %2);
    c1.construct(ccnt,depth - 1);
    this->children.push_back(std::pair<float, rectangle>(splitPoses[i],c1));
  }
}
int rectangle::draw( bitmap* res,size_t posx, size_t posy,size_t width, size_t height, size_t between) const {
  int ret = 0;
  for(size_t x = posx; x < posx + width; ++x)
    (*res)(x,posy) = (*res)(x, posy + 1) 
		= (*res)(x, posy + height - 2) 
		= (*res)(x, posy + height - 1)
		= pixel(128,128,128);
  for(size_t y = posy; y < posy + height; ++y)
    (*res)(posx,y) = (*res)(posx + 1, y)
		= (*res)(posx + width - 1, y)
		= (*res)(posx + width - 2, y)
		= pixel(128,128,128);

  size_t wd = this->horizontal ? width - (this->children.size() + 1) * between : 
      width - 2 * between;
  size_t hg = !this->horizontal ? height - (this->children.size() + 1) * between : 
      height - 2 * between;
  if(this->horizontal)
    posy += between;
  else
    posx += between;
  for(auto i : this->children) 
    if(this->horizontal) {
      posx += between;
      ret += i.second.draw(res,posx,posy,size_t(i.first * wd), hg, between);
      posx += size_t( i.first * wd);
    }
    else {
      posy += between;
      ret += i.second.draw(res,posx,posy, wd, size_t(i.first * hg), between);
      posy += size_t( i.first * hg);
    }
  
  return ret;
}
  
int rectangle::writeTmp(FILE* tmp) {
  fprintf(tmp,"%hhu %lu ", this->isHorizontal(), this->children.size());
  for(size_t i = 0; i < this->children.size(); ++i)
    fprintf(tmp, "%f ", this->children[i].first);
  fprintf(tmp,"\n");
  int ret = 0;
  for(auto i : this->children)
    ret += i.second.writeTmp(tmp);
  return ret;
}
rectangle readTmp(FILE* tmp, int maxChildren, int nMaxChildren, int depth, int& regenTreePos) {
  u8 b; 
  size_t ccnt;
  fscanf(tmp,"%hhu %lu",&b,&ccnt);
  rectangle ret(b);
  std::vector<float> splitPoses;
  splitPoses.assign(ccnt,0);
  for(size_t i = 0; i< ccnt;++i)
    fscanf(tmp, "%f", &splitPoses[i]);
  for(size_t i = 0; i< ccnt; ++i){
    rectangle c = readTmp(tmp, maxChildren, nMaxChildren, depth-1, --regenTreePos);
    if(regenTreePos == 0) {
      c.construct(nMaxChildren, depth - 1);      
      regenTreePos = -1;
    }
    ret.children.push_back(std::pair<float,rectangle>(splitPoses[i], c));    
  }
  return ret;
}