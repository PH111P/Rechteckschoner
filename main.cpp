//
// Copyright (c) 2014 Philip Wellnitz;
// Using code from Cosmin Luta, Copyright (c) 2006 Cosmin Luta;
// Using libpng.
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
#include <cstring>
#include <cstdlib>

#include <iostream>
#include <string>

#include "optparse.h"

#include "bitmap.h"
#include "rectangle.h"


size_t width, height, maxDepth,
distBetweenRectangles, children;
FILE* tmpFile;
char* outputPath = NULL;
bool highlight;

rectangle root;

int main(int argc, char* argv[]) {
  Options o;
  o.addOption("","--help", "show this help and exit", OPT_HELP, NULL);
  o.addOption("-v","--version", "(ignored)", OPT_NONE, NULL);
  o.addOption("-r","--read", "don't change any rectangle",OPT_NONE,NULL);
  o.addOption("-i","--highlight", "highlight changed rectangles",OPT_NONE,NULL);
  o.addOption("-h","",
	      "specify the height (in px) of the output (required)",
	      OPT_REQUIRED | OPT_NEEDARG, [](const String& str){
		height = strtol( str.c_str(), NULL, 10 );
		return height > 0;		
	      });
  o.addOption("-w","",
	      "specify the width (in px) of the output (required)",
	      OPT_REQUIRED | OPT_NEEDARG, [](const String& str){
		width = strtol( str.c_str(), NULL, 10 );
		return width > 0;		
	      });
  o.addOption("-d","",
	      "specify the maximum recursion depth", "10",
	      OPT_NEEDARG, [](const String& str){
		maxDepth = strtol( str.c_str(), NULL, 10 );
		return maxDepth > 0;		
	      });
  o.addOption("-b","",
	      "specify the distace between rectangles", "10",
	      OPT_NEEDARG, [](const String& str){
		distBetweenRectangles = strtol( str.c_str(), NULL, 10 );
		return distBetweenRectangles > 0;		
	      });
  o.addOption("-c","",
	      "specify the max number of children a rectangle may have in the tree","2",
	      OPT_NEEDARG, [](const String& str){
		children = strtol( str.c_str(), NULL, 10 );
		return children > 0;		
	      });
  o.addOption("-o","",
	      "path to the (input) output folder", "./",
	      OPT_NEEDARG, [](const String& str){
		outputPath = new char[str.length() + 2];
		strcpy(outputPath,str.c_str());
		return true;
	      });
  o.addOption("-t","",
	      "name of a previously generated temporary file (default: none, create a new one)",
	      OPT_NEEDARG, [](const String& str) {
		tmpFile = fopen(str.c_str(), "r");
		return !!tmpFile;
	      });
  
  Parser p;
  int result = p.parse(argc, argv, o);
  
  srand(time(0));
  
  if( result == E_OK ) {
    highlight = o.isSet("-i");
    bool read = o.isSet("-r");
    
    if(tmpFile) {
      size_t oc;
      fscanf(tmpFile,"%*u %*u %lu %*u\n", &oc);
      
      int ndepth = read ? -1 : (rand() % (maxDepth - 3));
      int pos = read ? -1 : (rand() % std::max(oc,children));
      root = readTmp(tmpFile,oc, children,maxDepth,ndepth,pos); 
      fclose(tmpFile);
    } else {
      root = rectangle(rand() % 2);
      root.construct(children, maxDepth);
    }
    std::string output(outputPath);
    FILE* tmpWrtFile = fopen((output + ".tmp").c_str(),"w");
    if(tmpWrtFile){
      fprintf(tmpWrtFile,"%lu %lu %lu %lu \n", width, height, children, distBetweenRectangles);
      root.writeTmp(tmpWrtFile);
      fclose(tmpWrtFile);
    }
    else {
      fprintf(stderr,"Failed to open %s for writing the tmp file.\n", (output + ".tmp").c_str());  
      return -1;
    }
    bitmap btm(width,height);
    
    if(root.draw(&btm, 0lu,0lu, width, height, distBetweenRectangles) || btm.writeToFile((output + "rechteckschoner.png").c_str())) {
      fprintf(stderr,"Failed to create/ write .png file.\n");  
      return -1;
    }
    return 0;
  }
  else{
    if(!( result & E_EXIT))
      fprintf(stderr, "You failed to specify correct command line args...\n");
    else
      return 0;
    //Print command line arg possibilities here   
    if ( result & E_OPT_MISSING )
      fprintf(stderr,"---- MISSING REQUIRED OPTION ----\n"); 
    if ( result & E_OPT_UNKNOWN )
      fprintf(stderr,"---- UNKNOWN OPTION SPECIFIED ----\n");    
    if ( result & E_ERROR )
      fprintf(stderr,"---- GENERIC ERROR ----\n");
    if ( result & E_ARG_EXPECTED )
      fprintf(stderr,"---- ARGUMENT EXPECTED ----\n");
    if ( result & E_ARG_INVALID )
      fprintf(stderr,"---- ARGUMENT NOT VALID ----\n");
    o.generateHelp();
    return -1;
  }
}