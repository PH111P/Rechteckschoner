//
// Copyright ( c ) 2014 Philip Wellnitz;
// Using code from Cosmin Luta, Copyright ( c ) 2006 Cosmin Luta;
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
// a copy of this software and associated documentation files ( the
// "Software" ), to deal in the Software without restriction, including
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
char* loutputPath = NULL;
bool highlight;

u8 color[ 3 ];

rectangle root;

int main( int p_argc, char* p_argv[] ) {
  Options o;
  o.addOption( "", "--help", "show this help and exit", OPT_HELP, NULL );
  o.addOption( "-v", "--version", "( ignored )", OPT_NONE, NULL );
  o.addOption( "-r", "--read", "don't change any rectangle", OPT_NONE, NULL );
  o.addOption( "-i", "--highlight", "highlight changed rectangles", OPT_NONE, NULL );
  o.addOption( "-h", "", 
	      "specify the height ( in px ) of the output ( required )", 
	      OPT_REQUIRED | OPT_NEEDARG, []( const String& str ){
		height = std::strtol( str.c_str(  ), NULL, 10 );
		return height > 0;		
	      } );
  o.addOption( "-w", "", 
	      "specify the width ( in px ) of the output ( required )", 
	      OPT_REQUIRED | OPT_NEEDARG, []( const String& str ){
		width = std::strtol( str.c_str(  ), NULL, 10 );
		return width > 0;		
	      } );
  o.addOption( "-d", "", 
	      "specify the maximum recursion depth", "10", 
	      OPT_NEEDARG, []( const String& str ){
		maxDepth = std::strtol( str.c_str(  ), NULL, 10 );
		return maxDepth > 0;		
	      } );
   o.addOption( "-b", "", 
	      "specify the distace between rectangles", "10", 
	      OPT_NEEDARG, []( const String& str ){
		distBetweenRectangles = std::strtol( str.c_str(  ), NULL, 10 );
		return distBetweenRectangles > 0;		
	      } ); 
   o.addOption( "-e", "", 
	      "specify the red component modifier", "0", 
	      OPT_NEEDARG, []( const String& str ){
		color[ 0 ] = (u8)std::strtol( str.c_str(  ), NULL, 10 );
		return true;		
	      } ); 
   o.addOption( "-g", "", 
	      "specify the green component modifier", "1", 
	      OPT_NEEDARG, []( const String& str ){
		color[ 1 ] = (u8)std::strtol( str.c_str(  ), NULL, 10 );
		return true;		
	      } ); 
   o.addOption( "-b", "", 
	      "specify the blue component modifier", "2", 
	      OPT_NEEDARG, []( const String& str ){
		color[ 2 ] = (u8)std::strtol( str.c_str(  ), NULL, 10 );
		return true;		
	      } ); 
   o.addOption( "-c", "", 
	      "specify the max number of children a rectangle may have in the tree", "2", 
	      OPT_NEEDARG, []( const String& str ){
		children = std::strtol( str.c_str(  ), NULL, 10 );
		return children > 0;		
	      } );
  o.addOption( "-o", "", 
	      "path to the ( input ) output folder", "./", 
	      OPT_NEEDARG, []( const String& str ){
		outputPath = new char[str.length(  ) + 2];
		std::strcpy( outputPath, str.c_str(  ) );
		return true;
	      } );
  o.addOption( "-l", "", 
	      "path to the output folder for copies of the generated png and tmp files", 
	      OPT_NEEDARG, []( const String& str ){
		loutputPath = new char[str.length(  ) + 2];
		std::strcpy( loutputPath, str.c_str(  ) );
		return true;
	      } );
  o.addOption( "-t", "", 
	      "name of a previously generated temporary file ( default: none, create a new one )", 
	      OPT_NEEDARG, []( const String& str ) {
		tmpFile = std::fopen( str.c_str(  ), "r" );
		return !!tmpFile;
	      } );
  
  Parser p;
  int result = p.parse( p_argc, p_argv, o );
  
  srand( time( 0 ) );
  
  if ( result == E_OK ) {
    highlight = o.isSet( "-i" );
    bool read = o.isSet( "-r" );
    
    if ( tmpFile ) {
      size_t oc;
      std::fscanf( tmpFile, "%*u %*u %lu %*u\n", &oc );
      
      int ndepth = read ? -1 : ( rand(  ) % ( maxDepth - 3 ) );
      int pos = read ? -1 : ( rand(  ) % std::max( oc, children ) );
      root = readTmp( tmpFile, oc, children, maxDepth, ndepth, pos ); 
      std::fclose( tmpFile );
    } else {
      root = rectangle( rand(  ) % 2 );
      root.construct( children, maxDepth );
    }
    
    std::string output( outputPath );
    std::string logOutput = "NONE";
    if(loutputPath)
      logOutput = std::string(loutputPath);
    
    FILE* tmpWrtFile = std::fopen( ( output + ".tmp" ).c_str(  ), "w" );
    FILE* logWrtFile = NULL;
    if(loutputPath)
      logWrtFile = std::fopen( ( logOutput + ".tmp" ).c_str(  ), "w" );
    
    if ( tmpWrtFile ) {
      std::fprintf( tmpWrtFile, "%lu %lu %lu %lu \n", width, height, children, distBetweenRectangles );
      root.writeTmp( tmpWrtFile );
      std::fclose( tmpWrtFile );
    } else {
      std::fprintf( stderr, "Failed to open %s for writing the tmp file.\n", ( output + ".tmp" ).c_str(  ) );  
      return -1;
    }
    bitmap btm( width, height );
    
    if ( root.draw( &btm, 0lu, 0lu, width, height, distBetweenRectangles ) || btm.writeToFile( ( output + "rechteckschoner.png" ).c_str(  ) ) ) {
      std::fprintf( stderr, "Failed to create/ write .png file.\n" );  
      return -1;
    }
    
    
    if ( logWrtFile ) {
      std::fprintf( logWrtFile, "%lu %lu %lu %lu \n", width, height, children, distBetweenRectangles );
      root.writeTmp( logWrtFile );
      std::fclose( logWrtFile );
      btm.writeToFile( ( logOutput + "rechteckschoner.png" ).c_str(  ) );
    }
    
    return 0;
  } else {
    if ( !( result & E_EXIT ) )
      std::fprintf( stderr, "You failed to specify correct command line args...\n" );
    else
      return 0;
    //Print command line arg possibilities here   
    if ( result & E_OPT_MISSING )
      std::fprintf( stderr, "---- MISSING REQUIRED OPTION ----\n" ); 
    if ( result & E_OPT_UNKNOWN )
      std::fprintf( stderr, "---- UNKNOWN OPTION SPECIFIED ----\n" );    
    if ( result & E_ERROR )
      std::fprintf( stderr, "---- GENERIC ERROR ----\n" );
    if ( result & E_ARG_EXPECTED )
      std::fprintf( stderr, "---- ARGUMENT EXPECTED ----\n" );
    if ( result & E_ARG_INVALID )
      std::fprintf( stderr, "---- ARGUMENT NOT VALID ----\n" );
    o.generateHelp(  );
    return 1;
  }
}
