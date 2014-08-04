//
// Copyright (c) 2014 Philip Wellnitz;
// Using code from Cosmin Luta, Copyright (c) 2006 Cosmin Luta;
// Using libpng.
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
#include <cstring>
#include <cstdlib>

#include <iostream>
#include <string>

#include "optparse.h"

#include "bitmap.h"
#include "rectangle.h"


int width, height, maxDepth, distBetweenRectangles, children;
std::string outputPath;
std::string tmpPath;

int main(int argc, char* argv[]) {
  Options o;
  o.addOption("-?","--help", "show this help and exit", OPT_HELP, NULL);
  o.addOption("-v","--version", "(ignored)", OPT_NONE, NULL);
  o.addOption("-h","--height",
	      "specify the height (in px) of the output (required)",
	      OPT_REQUIRED | OPT_NEEDARG, NULL);
  o.addOption("-w","--width",
	      "specify the width (in px) of the output (required)",
	      OPT_REQUIRED | OPT_NEEDARG, NULL);
  o.addOption("-d","--depth",
	      "specify the maximum recursion depth (default: infiniy)",
	      OPT_NEEDARG, NULL);
  o.addOption("-b","--between",
	      "specify the distace between rectangles (default: 10px)",
	      OPT_NEEDARG, NULL);
  o.addOption("-c","--children",
	      "specify the max number of children a rectangle may have in the tree (default: 2)",
	      OPT_NEEDARG, NULL);
  o.addOption("-o","--output",
	      "path to the (input) output folder (default: ./)",
	      OPT_NEEDARG, NULL);
  o.addOption("-t","--tmp",
	      "name of a previously generated temporary file (default: none, create a new one)",
	      OPT_NEEDARG, NULL);
  Parser p;
  
  int result = p.parse(argc, argv, o);
  
  if( result == E_OK ) {
    
  }
  else{
    fprintf(stderr, "You failed to specify correct command line args...\n");

  }
  //TODO:do stuff
  return 0;
}