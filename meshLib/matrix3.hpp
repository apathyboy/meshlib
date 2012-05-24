/** -*-c++-*-
 *  \class  matrix3
 *  \file   matrix3.hpp
 *  \author Kenneth R. Sewell III

 meshLib is used for the parsing and exporting .msh models.
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

#ifndef MATRIX3_HPP
#define MATRIX3_HPP

namespace ml
{
  class matrix3
  {
  public:
    matrix3()
    {
      for( unsigned int i = 0; i < 9; ++i )
	{
	  v[i] = 0.0;
	}
    }

    matrix3( const float *V )
    {
      memcpy( v, V, sizeof( float ) * 9 );
    }

    ~matrix3(){}

    float get( int index ) const
    {
      if( index < 9 )
	{
	  return v[index];
	}
      else
	{
	  return 0.0;
	}
    }

    void get( float *V ) const
    {
      memcpy( V, v, sizeof( float ) * 9 );
    }

    void set( const float *V )
    {
      memcpy( v, V, sizeof( float ) * 9 );
    }

    void set( const matrix3 &m )
    {
      memcpy( v, m.v, sizeof( float ) * 9 );
    }

    void print() const
    {
      for( unsigned int i = 0; i < 9; i += 3 )
	{
	  std::cout << std::fixed
		    << v[i] << " " << v[i+1] << " " << v[i+2] << std::endl;
	}
    }


  protected:

  private:
    float v[9];
  };
}
#endif
