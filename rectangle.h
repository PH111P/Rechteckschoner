#pragma once
#include <vector>

struct bitmap;

class rectangle {
private:
  int posx,		//x position of the top-left corner
      posy,		//y position of the top-left corner
      width,		//rectangle's width
      height;		//rectangle's height
  
  int numChildren;	//number of max enclosed rectangles
  
  std::vector<rectangle*> children;
public:
  static int DistanceBetweenRectangles = 10;
  
  int getX () const;
  int getY () const;
  int getWidth () const;
  int getHeight () const;
  
  rectangle(int posX, int posY, int rectWidth, int rectHeight, int maxChildren)
    : posx(posX), posy(posY), width(rectWidth), height(rectHeight), numChildren(maxChildren) { }
  
  void construct();
  void draw( bitmap* res ) const;
};