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

#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

#include "rectangle.h"
#include "bitmap.h"

///////////////////////////////////////////////////////////////////////////////
//
// Rectangle
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Rectangle - PUBLIC functions
///////////////////////////////////////////////////////////////////////////////

//
// Construct the rectangle tree.
//
void rectangle::construct( int p_children, int p_depth ) {
  this->m_children.clear(  );
  this->m_isNew = true;
  if ( p_depth == 0 )
    return;
  
  std::vector<float> splitPoses;
  for ( int i = 1; i < p_children; ++i )
    splitPoses.push_back( rand(  ) * 1.0f / RAND_MAX ); 
  splitPoses.push_back( 1 ); 
  
  std::sort( splitPoses.begin(  ), splitPoses.end(  ) );
  
  for ( int i = 0; i < p_children; ++i ) {
    rectangle c1( rand(  ) % 2 );
    c1.construct( p_children, p_depth - 1 );
    this->m_children.push_back( std::pair<float, rectangle>( splitPoses[i], c1 ) );
  }
}

//
// Draw the rectangle tree to the p_result bitmap
//
int rectangle::draw( bitmap* p_result, size_t p_positionX, size_t p_positionY, size_t p_width, size_t p_height, size_t p_between ) {
  if ( !p_height || !p_width )
    return 0;
  int ret = 0;
  
  auto children = this->m_children.size(  );
  
  int mx = this->isNew(  ) ? 255 : 160;
  if ( !highlight )
    mx = 230;
  
  u8 r = m_children.empty(  ) ? mx : u8( this->m_children[ color[ 0 ] % children].first * mx );
  u8 g = m_children.empty(  ) ? mx : u8( this->m_children[ color[ 1 ] % children].first * mx );
  u8 b = m_children.empty(  ) ? mx : u8( this->m_children[ color[ 2 ] % children].first * mx );
  
  for ( size_t x = p_positionX; x < p_positionX + p_width; ++x )
    ( *p_result )( x, p_positionY ) = ( *p_result )( x, p_positionY + 1 ) 
		= ( *p_result )( x, p_positionY + p_height - 2 ) 
		= ( *p_result )( x, p_positionY + p_height - 1 )
		= pixel( r, g, b );
  for ( size_t y = p_positionY; y < p_positionY + p_height; ++y )
    ( *p_result )( p_positionX, y ) = ( *p_result )( p_positionX + 1, y )
		= ( *p_result )( p_positionX + p_width - 1, y )
		= ( *p_result )( p_positionX + p_width - 2, y )
		= pixel( r, g, b );

  int actualWidth = this->m_horizontal ? p_width - ( this->m_children.size(  ) + 1 ) * p_between : 
      p_width - 2 * p_between;
  int actualHeight = !this->m_horizontal ? p_height - ( this->m_children.size(  ) + 1 ) * p_between : 
      p_height - 2 * p_between;
      
  if ( actualWidth <= 0 || actualHeight <= 0 ) {
    actualWidth = !this->m_horizontal ? p_width - ( this->m_children.size(  ) + 1 ) * p_between : 
      p_width - 2 * p_between;
    actualHeight = this->m_horizontal ? p_height - ( this->m_children.size(  ) + 1 ) * p_between : 
      p_height - 2 * p_between;
      
    if ( actualWidth <= 0 || actualHeight <= 0 )
      return 0;
    this->m_horizontal = !this->m_horizontal;
  }
  
  if ( this->m_horizontal )
    p_positionY += p_between;
  else
    p_positionX += p_between;
  
  for ( auto i : this->m_children ) 
    if ( this->m_horizontal ) {
      p_positionX += p_between;
      ret += i.second.draw( p_result, p_positionX, p_positionY, size_t( i.first * actualWidth ), size_t( actualHeight ), p_between );
      p_positionX += size_t( i.first * actualWidth );
      actualWidth -= size_t( i.first * actualWidth );
    } else {
      p_positionY += p_between;
      ret += i.second.draw( p_result, p_positionX, p_positionY, size_t( actualWidth ), size_t( i.first * actualHeight ), p_between );
      p_positionY += size_t( i.first * actualHeight );
      actualHeight -= size_t( i.first * actualHeight );
    }
  
  return ret;
}
  
//
// Write the rectangle tree into a temporary file, preorder
//
int rectangle::writeTmp( FILE* p_tmp ) {
  std::fprintf( p_tmp, "%hhu %lu ", this->isHorizontal(  ), this->m_children.size(  ) );
  for ( size_t i = 0; i < this->m_children.size(  ); ++i )
    std::fprintf( p_tmp, "%f ", this->m_children[i].first );
  std::fprintf( p_tmp, "\n" );
  
  int ret = 0;
  for ( auto i : this->m_children )
    ret += i.second.writeTmp( p_tmp );
  return ret;
}

//
// Read a rectangle tree from a temporary file
//
rectangle readTmp( FILE* p_tmp, int p_oldChildren, int p_children, int p_depth, int p_recreateDepth, int p_recreatePosition ) {  
  u8 horizontal; 
  size_t children;
  
  // Read whether the act. rectangle aligns its children horizontally, and how much children there are
  std::fscanf( p_tmp, "%hhu %lu", &horizontal, &children );
  rectangle ret( horizontal );
  
  std::vector<float> splitPoses;
  splitPoses.assign( children, 0 );
  for ( size_t i = 0; i < children; ++i )
    std::fscanf( p_tmp, "%f", &splitPoses[i] );
  
  for ( size_t i = 0; i < children; ++i ) {
    rectangle c = readTmp( p_tmp, p_oldChildren, p_children, p_depth - 1, p_recreateDepth - 1, p_recreatePosition );
    
    if ( p_recreateDepth == 0 && ( p_recreatePosition % children ) == i ) {
      ++p_recreateDepth;
      ++p_recreatePosition;
      c.construct( p_children, p_depth - 1 );
    }
    ret.m_children.push_back( std::pair<float, rectangle>( splitPoses[i], c ) );    
  }
  return ret;
}
