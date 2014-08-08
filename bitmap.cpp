//
// Copyright ( c ) 2014 Philip Wellnitz
// Using libpng
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
#include <cstdlib>

#include <png.h>

#include "bitmap.h"

///////////////////////////////////////////////////////////////////////////////
//
// Bitmap
//
///////////////////////////////////////////////////////////////////////////////

bitmap::bitmap( size_t p_width, size_t p_height ){
  this->m_width = p_width;
  this->m_height = p_height;
  this->m_pixels = std::vector<std::vector<pixel>>( p_width, std::vector<pixel>( p_height, {0, 0, 0} ) );
}

///////////////////////////////////////////////////////////////////////////////
// Bitmap - Operator overloadings
///////////////////////////////////////////////////////////////////////////////

pixel& bitmap::operator(  )( size_t p_x, size_t p_y ){
  if ( p_x < 0 || p_x >= this->m_width || p_y < 0 || p_y >= this->m_height ) {
    std::fprintf( stderr, "Index out of range while trying to get pixel at ( %lu|%lu )!\nReturning default pixel value instead.", p_x, p_y );
    static pixel defPixel = {0, 0, 0};
    return defPixel;
  }    
  return this->m_pixels[p_x][p_y];
}
pixel bitmap::operator(  )( size_t p_x, size_t p_y ) const {
  if ( p_x < 0 || p_x >= this->m_width || p_y < 0 || p_y >= this->m_height ) {
    std::fprintf( stderr, "Index out of range while trying to get pixel at ( %lu|%lu )!\nReturning default pixel value instead.", p_x, p_y );
    static pixel defPixel = {0, 0, 0};
    return defPixel;
  }    
  return this->m_pixels[p_x][p_y];
}
 
///////////////////////////////////////////////////////////////////////////////
// Bitmap - PUBLIC functions
///////////////////////////////////////////////////////////////////////////////

//
// Write bitmap to file
//
int bitmap::writeToFile( const char* p_path ) const {
   FILE* fd;
   png_structp pngPtr = NULL;
   png_infop infoPtr = NULL;
   size_t x, y;
   png_byte** rowPointers = NULL;
   
   int status = -1;
   
   int pixelSize = 3, depth = 8;
   
   fd = std::fopen( p_path, "wb" );
   if ( !fd ) {
     std::fprintf( stderr, "Could not open file %s for writing.\n", p_path );
     goto FOPEN_FAILED;
   }
   
   pngPtr = png_create_write_struct( PNG_LIBPNG_VER_STRING, NULL, NULL, NULL );
   if ( pngPtr == NULL ){
     std::fprintf( stderr, "Could not create png write struct.\n" );
     status = -2;
     goto PNG_CREATE_WRITE_STRUCT_FAILED;
   }
   
   infoPtr = png_create_info_struct( pngPtr );
   if ( pngPtr == NULL ){
     std::fprintf( stderr, "Could not create png info struct.\n" );
     status = -3;
     goto PNG_CREATE_INFO_STRUCT_FAILED;
   }
   
   if ( setjmp( png_jmpbuf( pngPtr ) ) ){
     std::fprintf( stderr, "Png failure\n" );
     
     status = -4;
     goto PNG_FAILURE;
   }
   
   //Set image attributes
   
   png_set_IHDR( pngPtr, 
		infoPtr, 
		this->m_width, 
		this->m_height, 
		depth, 
		PNG_COLOR_TYPE_RGB, 
		PNG_INTERLACE_NONE, 
		PNG_COMPRESSION_TYPE_DEFAULT, 
		PNG_FILTER_TYPE_DEFAULT );
   
   //Initialize rows of png
   
   rowPointers = ( png_byte** )png_malloc( pngPtr, this->m_height * sizeof( png_bytep ) );
   for ( y = 0; y< this->m_height; ++y ) {
     png_byte* row = ( png_byte* )png_malloc( pngPtr, this->m_width * pixelSize );
     rowPointers[y] = row;
     for ( x = 0; x < this->m_width; ++x ) {
       auto px = this->operator(  )( x, y );
       *row++ = px.m_red;
       *row++ = px.m_green;
       *row++ = px.m_blue;
     }
   }
   
   //Write data to fd
   
   png_init_io( pngPtr, fd );
   png_set_rows( pngPtr, infoPtr, rowPointers );
   png_write_png( pngPtr, infoPtr, PNG_TRANSFORM_IDENTITY, NULL );
   
   status = 0;
   
   for ( y = 0; y < this->m_height; ++y )
     png_free( pngPtr, rowPointers[y] );
   png_free( pngPtr, rowPointers );
   
PNG_FAILURE:
PNG_CREATE_INFO_STRUCT_FAILED:
   png_destroy_write_struct( &pngPtr, &infoPtr );
PNG_CREATE_WRITE_STRUCT_FAILED:
   fclose( fd );
FOPEN_FAILED:
   return status;
}