/** -*-c++-*-
 *  \class  mshVertex
 *  \file   mshVertex.hpp
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

#include <fstream>
#include <string>

#ifndef MSHVERTEX_HPP
#define MSHVERTEX_HPP

namespace ml
{
  class mshVertex
  {
  public:
    mshVertex( unsigned int bpv );
    virtual ~mshVertex();

    unsigned char getBytesPerVertex() const
    {
      return bytesPerVertex;
    }

    bool read( std::istream &file );
    bool setData( const char *buffer );
    bool getData( char *newBuf ) const;

    static bool isSupportedSize( const unsigned int bpv )
    {
      switch( bpv )
	{
	case 32:
	case 36:
	case 40:
	case 44:
	case 48:
	case 52:
	case 56:
	case 60:
	case 64:
	case 68:
	case 72:
	  return true;
	  break;
	default: return false;
	};
    }

    void print() const;

    void getPosition( float &x, float &y, float &z ) const;
    void getNormal( float &nx, float &ny, float &nz ) const;
    void getTexCoords( unsigned int &numPairs, float *coords ) const;

    void getColor( unsigned char *argb ) const;

#if 0
    float getX() const;
    float getY() const;
    float getZ() const;

    float getNX() const;
    float getNY() const;
    float getNZ() const;

    float getS1() const;
    float getT1() const;

    float getS2() const;
    float getT2() const;

    float getS3() const;
    float getT3() const;

    float getS4() const;
    float getT4() const;

    float getS5() const;
    float getT5() const;
#endif

  protected:
    unsigned int bytesPerVertex;
    char *data;

  };
}
#endif
