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

#pragma once
#include <vector>
#include <cstdio>

struct bitmap;

class rectangle {
private:
  bool horizontal; //Determines whether the rectangle's children are positioned
		    //horizontally next to each other
public:
  std::vector<std::pair<float,rectangle>> children;
  
  bool isHorizontal() { return horizontal; }
  
  rectangle() {}
  rectangle(bool hrz)
    : horizontal(hrz) { }
  
  void construct(int children,int depth);
  int draw( bitmap* res, int posx, int posy, int width, int height, int between ) const;
  
  int writeTmp(FILE* tmp);
};
rectangle readTmp(FILE* tmp, int oldChildren, int children, int depth, int& regenTreePos);
