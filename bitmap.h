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
  
  pixel& operator()(int x, int y);
  pixel operator()(int x, int y) const;
  
  int writeToFile(const char* path) const;
};

