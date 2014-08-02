#pragma once
#include <vector>

class rectangle {
private:
  int posx,		//x position of the top-left corner
      posy,		//y position of the top-left corner
      width,		//rectangle's width
      height;		//rectangle's height
  
  std::vector<rectangle*> children;
public:
  static int DistanceBetweenRectangles = 10;
  
  int getX ();
  int getY ();
  int getWidth ();
  int getHeight ();
  
  rectangle(int posX, int posY, int rectWidth, int rectHeight)
    : posx(posX), posy(posY), width(rectWidth), height(rectHeight) { }
  
  void construct();
  void draw( ... );
};