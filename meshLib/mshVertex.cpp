/** -*-c++-*-
 *  \class  mshVertex
 *  \file   mshVertex.cpp
 *  \author Kenneth R. Sewell III

 Copyright (C) 2006-2009 Kenneth R. Sewell III

 This file is part of meshLib.

 meshLib is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 meshLib is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with meshLib; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <meshLib/base.hpp>
#include <meshLib/mshVertex.hpp>
#include <memory.h>
#include <iostream>

using namespace ml;

mshVertex::mshVertex( unsigned int bpv )
  :bytesPerVertex( bpv ),
   data( NULL )
{
  // Allocate memory for vertex.
  data = new char[bpv];
  
  // Check that allocation was successful.
  if( NULL == data )
    {
      std::cerr << "Failed to allocate "
		<< bpv
		<< " bytes for vertex"
		<< std::endl;
      bytesPerVertex = 0;
    }
}

mshVertex::~mshVertex()
{
  if( NULL != data )
    {
      delete[] data;
    }
}

bool mshVertex::setData( const char *buffer )
{
  if( NULL == buffer )
    {
      std::cerr << "Source pointer is NULL" << std::endl;
      return false;
    }
  else if( NULL == data )
    {
      std::cerr << "Bytes per vertex needs set first." << std::endl;
      return false;
    }

  memcpy( data, buffer, bytesPerVertex );

  return true;
}

bool mshVertex::getData( char *buffer ) const
{
  if( NULL == buffer )
    {
      std::cerr << "Destination pointer is NULL" << std::endl;
      return false;
    }
  else if( NULL == data )
    {
      std::cerr << "Bytes per vertex needs set first." << std::endl;
      return false;
    }

  memcpy( buffer, data, bytesPerVertex );
  
  return true;
}

bool mshVertex::read( std::istream &file )
{
  if( 0 == bytesPerVertex )
    {
      std::cerr << "Bytes per vertex must be set before data can be read."
		<< std::endl;
      return false;
    }

  // Read all float values in one read.
  file.read( (char *)data, bytesPerVertex );

  return true;
}

void mshVertex::print() const
{
  float *x = reinterpret_cast<float *>( data );
  std::cout << " ( " << x[0] << ", ";
  std::cout << x[1] << ", ";
  std::cout << x[2] << " ) ";

  std::cout << " ( " << x[3] << ", ";
  std::cout << x[4] << ", ";
  std::cout << x[5] << " ) ";

  switch( bytesPerVertex )
    {
    case 32:
      // Tex coords 0
      std::cout << " ( " << x[6] << ", ";
      std::cout << x[7] << " ) ";
      break;

    case 36:
      {
	// ARGB Color
	unsigned char *y =
	  reinterpret_cast<unsigned char *>( data + ( sizeof( float ) * 6 ) );
	std::cout << " ( " << (unsigned int)(y[0]) << ", ";
	std::cout << (unsigned int)(y[1]) << " ";
	std::cout << (unsigned int)(y[2]) << " ";
	std::cout << (unsigned int)(y[3]) << ") ";
      }

      // Tex coords 1
      std::cout << " ( " << x[7] << ", ";
      std::cout << x[8] << " ) ";
      break;

    case 40:
      // Tex coords 1
      std::cout << " ( " << x[6] << ", ";
      std::cout << x[7] << " ) ";

      // Tex coords 2
      std::cout << " ( " << x[8] << ", ";
      std::cout << x[9] << " ) ";
      break;

    case 44:
      {
	// ARGB Color
	unsigned char *y =
	  reinterpret_cast<unsigned char *>( data + ( sizeof( float ) * 6 ) );
	std::cout << " ( " << (unsigned int)(y[0]) << ", ";
	std::cout << (unsigned int)(y[1]) << " ";
	std::cout << (unsigned int)(y[2]) << " ";
	std::cout << (unsigned int)(y[3]) << ") ";
      }

      // Tex coords 0
      std::cout << " ( " << x[7] << ", ";
      std::cout << x[8] << " ) ";

      // Tex coords 1
      std::cout << " ( " << x[9] << ", ";
      std::cout << x[10] << " ) ";
      break;

    case 48:
      // Tex coords 0
      std::cout << " ( " << x[6] << ", ";
      std::cout << x[7] << " ) ";

      // Tex coords 1
      std::cout << " ( " << x[8] << ", ";
      std::cout << x[9] << ", ";

      // Tex coords 2
      std::cout << " ( " << x[10] << ", ";
      std::cout << x[11] << " ) ";

      break;

    case 52:
      {
	// ARGB Color
	unsigned char *y =
	  reinterpret_cast<unsigned char *>( data + ( sizeof( float ) * 6 ) );
	std::cout << " ( " << (unsigned int)(y[0]) << ", ";
	std::cout << (unsigned int)(y[1]) << " ";
	std::cout << (unsigned int)(y[2]) << " ";
	std::cout << (unsigned int)(y[3]) << ") ";
      }

      // Tex coords 0
      std::cout << " ( " << x[6] << ", ";
      std::cout << x[7] << " ) ";

      // Tex coords 1
      std::cout << " ( " << x[8] << ", ";
      std::cout << x[9] << ", ";

      // Tex coords 2
      std::cout << " ( " << x[10] << ", ";
      std::cout << x[11] << " ) ";

      break;

    case 56:
      // Tex coords 0
      std::cout << " ( " << x[6] << ", ";
      std::cout << x[7] << " ) ";

      // Tex coords 1
      std::cout << " ( " << x[8] << ", ";
      std::cout << x[9] << " ) ";

      // Tex coords 2
      std::cout << " ( " << x[10] << ", ";
      std::cout << x[11] << " ) ";

      // Tex coords 3
      std::cout << " ( " << x[12] << ", ";
      std::cout << x[13] << " ) ";
      break;

    case 60:
      {
	// ARGB Color
	unsigned char *y =
	  reinterpret_cast<unsigned char *>( data + ( sizeof( float ) * 6 ) );
	std::cout << " ( " << (unsigned int)(y[0]) << ", ";
	std::cout << (unsigned int)(y[1]) << " ";
	std::cout << (unsigned int)(y[2]) << " ";
	std::cout << (unsigned int)(y[3]) << ") ";
      }

      // Tex coords 0
      std::cout << " ( " << x[7] << ", ";
      std::cout << x[8] << " ) ";

      // Tex coords 1
      std::cout << " ( " << x[9] << ", ";
      std::cout << x[10] << " ) ";

      // Tex coords 2
      std::cout << " ( " << x[11] << ", ";
      std::cout << x[12] << " ) ";

      // Tex coords 3
      std::cout << " ( " << x[13] << ", ";
      std::cout << x[14] << " ) ";

      break;

    case 64:
      // Tex coords 0
      std::cout << " ( " << x[6] << ", ";
      std::cout << x[7] << " ) ";

      // Tex coords 1
      std::cout << " ( " << x[8] << ", ";
      std::cout << x[9] << " ) ";

      // Tex coords 2
      std::cout << " ( " << x[10] << ", ";
      std::cout << x[11] << " ) ";

      // Tex coords 3
      std::cout << " ( " << x[12] << ", ";
      std::cout << x[13] << " ) ";

      // Tex coords 4
      std::cout << " ( " << x[14] << ", ";
      std::cout << x[15] << " ) ";
      break;

    case 68:
      {
	// ARGB Color
	unsigned char *y =
	  reinterpret_cast<unsigned char *>( data + ( sizeof( float ) * 6 ) );
	std::cout << " ( " << (unsigned int)(y[0]) << ", ";
	std::cout << (unsigned int)(y[1]) << " ";
	std::cout << (unsigned int)(y[2]) << " ";
	std::cout << (unsigned int)(y[3]) << ") ";
      }

      // Tex coords 0
      std::cout << " ( " << x[6] << ", ";
      std::cout << x[7] << " ) ";

      // Tex coords 1
      std::cout << " ( " << x[8] << ", ";
      std::cout << x[9] << " ) ";

      // Tex coords 2
      std::cout << " ( " << x[10] << ", ";
      std::cout << x[11] << " ) ";

      // Tex coords 3
      std::cout << " ( " << x[12] << ", ";
      std::cout << x[13] << " ) ";

      // Tex coords 4
      std::cout << " ( " << x[14] << ", ";
      std::cout << x[15] << " ) ";
      break;

    case 72:
      // Tex coords 0
      std::cout << " ( " << x[6] << ", ";
      std::cout << x[7] << " ) ";

      // Tex coords 1
      std::cout << " ( " << x[8] << ", ";
      std::cout << x[9] << " ) ";

      // Tex coords 2
      std::cout << " ( " << x[10] << ", ";
      std::cout << x[11] << " ) ";

      // Tex coords 3
      std::cout << " ( " << x[12] << ", ";
      std::cout << x[13] << " ) ";

      // Tex coords 4
      std::cout << " ( " << x[14] << ", ";
      std::cout << x[15] << " ) ";

      // Tex coords 5
      std::cout << " ( " << x[16] << ", ";
      std::cout << x[17] << " ) ";
      break;
    };

  std::cout << std::endl;
}

void mshVertex::getPosition( float &x, float &y, float &z ) const
{
  float *v = reinterpret_cast<float *>( data );
  x = v[0];
  y = v[1];
  z = v[2];
}

void mshVertex::getNormal( float &nx, float &ny, float &nz ) const
{
  float *v = reinterpret_cast<float *>( data );
  nx = v[3];
  ny = v[4];
  nz = v[5];
}

void mshVertex::getTexCoords( unsigned int &numPairs, float *coords ) const
{
  float *v = reinterpret_cast<float *>( data );

  switch( bytesPerVertex )
    {
    case 32:
      numPairs = 1;
      memcpy( coords, v+6, sizeof( float ) * 2 * numPairs );
      break;
    case 36:
      numPairs = 1;
      memcpy( coords, v+7, sizeof( float ) * 2 * numPairs );
      break;
    case 40:
      numPairs = 2;
      memcpy( coords, v+6, sizeof( float ) * 2 * numPairs );
      break;
    case 44:
      numPairs = 2;
      memcpy( coords, v+7, sizeof( float ) * 2 * numPairs );
      break;
    case 48:
      numPairs = 1;
      memcpy( coords, v+6, sizeof( float ) * 2 * numPairs );
      break;
    case 52:
      numPairs = 1;
      memcpy( coords, v+7, sizeof( float ) * 2 * numPairs );
      break;
    case 56:
      numPairs = 3;
      memcpy( coords, v+6, sizeof( float ) * 2 * numPairs );
      break;
    case 60:
      numPairs = 4;
      memcpy( coords, v+7, sizeof( float ) * 2 * numPairs );
      break;
    case 64:
      numPairs = 4;
      memcpy( coords, v+6, sizeof( float ) * 2 * numPairs );
      break;
    case 68:
      numPairs = 4;
      memcpy( coords, v+7, sizeof( float ) * 2 * numPairs );
      break;
    case 72:
      numPairs = 5;
      memcpy( coords, v+6, sizeof( float ) * 2 * numPairs );
      break;
    default: 
      numPairs = 1;
      coords[0] = 0.0;
      coords[1] = 0.0;
    };
}

void mshVertex::getColor( unsigned char *argb ) const
{
  if( ( 36 == bytesPerVertex )
      || ( 44 == bytesPerVertex )
      || ( 52 == bytesPerVertex )
      || ( 60 == bytesPerVertex )
      || ( 68 == bytesPerVertex )
      )
    {
      memcpy( argb, data+24, sizeof( unsigned int ) );
    }
}

