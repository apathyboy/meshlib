/** -*-c++-*-
 *  \class  vector3
 *  \file   vector3.hpp
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

#include <iostream>
#include <cstring>

#ifndef VECTOR3_HPP
#define VECTOR3_HPP

namespace ml
{
  class vector3
  {
  public:
    vector3()
    {v[0] = v[1] = v[2] = 0.0;}

    vector3( const float *V )
    {
      memcpy( v, V, sizeof( float ) * 3 );
    }

    vector3( const float &X, const float &Y, const float &Z )
    {
      v[0] = X;
      v[1] = Y;
      v[2] = Z;
    }

    ~vector3(){}

    void get( float &X, float &Y, float &Z ) const
    {
      X = v[0];
      Y = v[1];
      Z = v[2];
    }

    float getX() const
    {
      return v[0];
    }

    float getY() const
    {
      return v[1];
    }

    float getZ() const
    {
      return v[2];
    }

    void set( const float &X, const float &Y, const float &Z )
    {
      v[0] = X;
      v[1] = Y;
      v[2] = Z;
    }

    void set( const float *V )
    {
      memcpy( v, V, sizeof( float ) * 3 );
    }

    void set( const vector3 &vec )
    {
      memcpy( v, vec.v, sizeof( float ) * 3 );
    }

    void print() const
    {
      std::cout << std::fixed << v[0] << ", "
		<< v[1] << ", "
		<< v[2] << std::endl;
    }
  
  protected:

  private:
    float v[3];
  };
}
#endif
