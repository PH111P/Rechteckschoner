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

void rectangle::construct(int ccnt,int depth) {
  this->children.clear();
  if(depth == 0)
    return;
  
  std::vector<float> splitPoses;
  splitPoses.push_back(0);
  for(int i = 1; i < ccnt; ++i)
    splitPoses.push_back(rand() *1.0f / RAND_MAX);  
  std::sort(splitPoses.begin(), splitPoses.end());
  
  for(int i = 0; i < ccnt; ++i){
    rectangle c1(rand() %2);
    c1.construct(ccnt,depth - 1);
    this->children.push_back(std::pair<float, rectangle>(splitPoses[i],c1));
  }
}
int rectangle::draw( bitmap* res,int posx, int posy,int width, int height, int between) const {
//   std::vector<float> splitPoses;
//   for(int i = 1; i < ccnt; ++i)
//     splitPoses.push_back(rand() *1.0f / RAND_MAX);  
//   std::sort(splitPoses.begin(), splitPoses.end());
//   
//   int px = this->posx, py = this->posy;
//   int wd = hsplit ? this->width - (ccnt + 1) * rectangle::DistanceBetweenRectangles : 
//       this->width - 2 * rectangle::DistanceBetweenRectangles;
//   int hg = !hsplit ? this->height - (ccnt + 1) * rectangle::DistanceBetweenRectangles : 
//       this->height - 2 * rectangle::DistanceBetweenRectangles;
//       
  return 1;
}
  
int rectangle::writeTmp(FILE* tmp) {
  fprintf(tmp,"%i %lu", this->isHorizontal(), this->children.size());
  for(auto i = 0; i < this->children.size(); ++i)
    fprintf(tmp, "%f ", this->children[i].first);
  for(auto i : this->children)
    i.second.writeTmp(tmp);
  return 0;
}
rectangle readTmp(FILE* tmp, int maxChildren, int nMaxChildren, int depth, int& regenTreePos) {
  bool b; 
  size_t ccnt;
  fscanf(tmp,"%i %lu",&b,&ccnt);
  rectangle ret(b);
  std::vector<float> splitPoses;
  splitPoses.assign(ccnt,0);
  for(int i = 0; i< ccnt;++i)
    fscanf(tmp, "%f", &splitPoses[i]);
  for(int i = 0; i< ccnt; ++i){
    rectangle c = readTmp(tmp, maxChildren, nMaxChildren, depth-1, --regenTreePos);
    if(regenTreePos == 0) {
      c.construct(nMaxChildren, depth - 1);      
      regenTreePos = -1;
    }
    ret.children.push_back(std::pair<float,rectangle>(splitPoses[i], c));    
  }
  return ret;
}