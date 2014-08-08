//
// Copyright ( c ) 2014 Philip Wellnitz
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

#pragma once
#include <vector>

typedef unsigned char u8;

/**
 * @brief Struct to store the RGB values of a pixel.
 */
struct pixel{
public:
  u8 m_red;	///< R value
  u8 m_green;	///< G value
  u8 m_blue;	///< B value
  pixel( u8 p_red, u8 p_green, u8 p_blue )
    : m_red( p_red ), m_green( p_green ), m_blue( p_blue ) { }
};

#define SCALE( x, mx ) ( ( ( x ) < 0 ) ? 0 : ( ( int )( 256.0*( ( double )( x )/( double )( mx ) ) ) ) )

/**
 * @brief Struct to hold a bitmap.
 */
struct bitmap{
private:
  std::vector<std::vector<pixel>> m_pixels;	///< The raw data
public:
  size_t m_width;				///< The image width
  size_t m_height;				///< The image height
  bitmap( size_t p_width, size_t p_height );
  
  pixel& operator(  )( size_t p_x, size_t p_y );
  pixel operator(  )( size_t p_x, size_t p_y ) const;
  
  /**
   * @param p_path String containing the path to the file to write the file to
   * @return Non-zero if an error occured.
   */
  int writeToFile( const char* p_path ) const;
};

