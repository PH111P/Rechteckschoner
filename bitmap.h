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

typedef unsigned char u8;
struct pixel{
public:
  u8 red;
  u8 green;
  u8 blue;
};

#define SCALE(x, mx) (((x) < 0) ? 0 : ((int)(256.0*((double)(x)/(double)(mx)))))

struct bitmap{
private:
  std::vector<std::vector<pixel>> pixels;
  size_t width;
  size_t height;
public:
  bitmap(size_t width, size_t height);
  
  pixel& operator()(size_t x, size_t y);
  pixel operator()(size_t x, size_t y) const;
  
  int writeToFile(const char* path) const;
};

