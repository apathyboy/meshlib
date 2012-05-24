/** -*-c++-*-
 *  \class  quat
 *  \file   quat.hpp
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

#ifndef QUAT_HPP
#define QUAT_HPP

namespace ml
{
  class quat
  {
  public:
    quat()
    {v[0] = v[1] = v[2] = v[3] = 0.0;}

    quat( const float *V )
    {
      memcpy( v, V, sizeof( float ) * 4 );
    }

    quat( const float &X, const float &Y, const float &Z, const float &W )
    {
      v[0] = X;
      v[1] = Y;
      v[2] = Z;
      v[3] = W;
    }

    ~quat(){}

    void get( float &X, float &Y, float &Z, float &W ) const
    {
      X = v[0];
      Y = v[1];
      Z = v[2];
      W = v[3];
    }

    const float &getX() const
    {
      return v[0];
    }

    const float &getY() const
    {
      return v[1];
    }

    const float &getZ() const
    {
      return v[2];
    }

    const float &getW() const
    {
      return v[3];
    }

    void set( const float &X, const float &Y, const float &Z, const float &W )
    {
      v[0] = X;
      v[1] = Y;
      v[2] = Z;
      v[3] = W;
    }

    void set( const float *V )
    {
      memcpy( v, V, sizeof( float ) * 4 );
    }

    void set( const quat &vec )
    {
      memcpy( v, vec.v, sizeof( float ) * 4 );
    }

    void print() const
    {
      std::cout << std::fixed << v[0] << ", "
		<< v[1] << ", "
		<< v[2] << ", "
		<< v[3] << std::endl;
    }
  
  protected:

  private:
    float v[4];
  };
}
#endif
