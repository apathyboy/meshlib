/** -*-c++-*-
 *  \class  box
 *  \file   box.hpp
 *  \author Kenneth R. Sewell III

 meshLib is used for the parsing and exporting .msh models.
 Copyright (C) 2009 Kenneth R. Sewell III

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

#ifndef BOX_HPP
#define BOX_HPP

namespace ml
{
  class box
  {
  public:
    box(){};
    
    unsigned int readBOX( std::istream &file );
    unsigned int writeBOX( std::ostream &file ) const;

    void getCorner1( float &x, float &y, float &z ) const
    {
      x = x1;
      y = y1;
      z = z1;
    }

    void getCorner2( float &x, float &y, float &z ) const
    {
      x = x2;
      y = y2;
      z = z2;
    }

  protected:
    float x1, y1, z1;
    float x2, y2, z2;

  private:
  };
}
#endif
