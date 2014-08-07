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
  this->isnew = true;
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
int rectangle::draw( bitmap* res,size_t posx, size_t posy,size_t width, size_t height, size_t between) {
//   printf("Drawing a rectangle to %lu [%lu], %lu [%lu]\n",posx,posy,width,height);
  if(!height || !width)
    return 0;
  int ret = 0;
  
  auto ccnt = this->children.size();
  
  int mx = this->isNew() ? 255 : 128;
  
  u8 r = children.empty() ? mx : u8(this->children[0].first * mx);
  u8 g = children.empty() ? mx : u8(this->children[1 % ccnt].first * mx);
  u8 b = children.empty() ? mx : u8(this->children[2 % ccnt].first * mx);
  
  for(size_t x = posx; x < posx + width; ++x)
    (*res)(x,posy) = (*res)(x, posy + 1) 
		= (*res)(x, posy + height - 2) 
		= (*res)(x, posy + height - 1)
		= pixel(r,g,b);
  for(size_t y = posy; y < posy + height; ++y)
    (*res)(posx,y) = (*res)(posx + 1, y)
		= (*res)(posx + width - 1, y)
		= (*res)(posx + width - 2, y)
		= pixel(r,g,b);

  int wd = this->horizontal ? width - (this->children.size() + 1) * between : 
      width - 2 * between;
  int hg = !this->horizontal ? height - (this->children.size() + 1) * between : 
      height - 2 * between;
  if(wd <= 0 || hg <= 0) {
    wd = !this->horizontal ? width - (this->children.size() + 1) * between : 
      width - 2 * between;
    hg = this->horizontal ? height - (this->children.size() + 1) * between : 
      height - 2 * between;
      
    if(wd <= 0 || hg <= 0)
      return 0;
    this->horizontal = !this->horizontal;
  }
  if(this->horizontal)
    posy += between;
  else
    posx += between;
  for(auto i : this->children) 
    if(this->horizontal) {
      posx += between;
      ret += i.second.draw(res,posx,posy,size_t(i.first * wd), size_t(hg), between);
      posx += size_t( i.first * wd);
      wd -= size_t( i.first * wd);
    }
    else {
      posy += between;
      ret += i.second.draw(res,posx,posy, size_t(wd), size_t(i.first * hg), between);
      posy += size_t( i.first * hg);
      hg -= size_t(i.first * hg);
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
rectangle readTmp(FILE* tmp, int maxChildren, int nMaxChildren, int depth, int ndepth, int npos) {  
  u8 b; 
  size_t ccnt;
  fscanf(tmp,"%hhu %lu",&b,&ccnt);
  rectangle ret(b);
  std::vector<float> splitPoses;
  splitPoses.assign(ccnt,0);
  for(size_t i = 0; i< ccnt;++i)
    fscanf(tmp, "%f", &splitPoses[i]);
  for(size_t i = 0; i< ccnt; ++i){
    rectangle c = readTmp(tmp, maxChildren, nMaxChildren, depth-1, ndepth - 1, npos);
    if(ndepth == 0 && (npos % ccnt) == i){
      ++ndepth;
      ++npos;
      c.construct(nMaxChildren, depth - 1);
    }
    ret.children.push_back(std::pair<float,rectangle>(splitPoses[i], c));    
  }
  return ret;
}