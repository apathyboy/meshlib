/** -*-c++-*-
 *  \class  portal
 *  \file   portal.hpp
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
#include <string>
#include <vector>
#include <meshLib/matrix3.hpp>
#include <meshLib/vector3.hpp>

#ifndef PORTAL_HPP
#define PORTAL_HPP

namespace ml
{
  class portal
  {
  public:
    portal(){}
    ~portal(){}

    void setMatrix( const matrix3 &matrix )
    {
      mat.set( matrix );
    }

    void setPosition( const vector3 &position )
    {
      pos.set( position );
    }

    matrix3 getMatrix() const
    {
      return mat;
    }
    
    vector3 getPosition() const
    {
      return pos;
    }
    
    void setPortalID( const unsigned int &id )
    {
      portalId = id;
    }
    
    unsigned int getPortalID() const
    {
      return portalId;
    }

    void setPortalGeometryIndex( const unsigned int &index )
    {
      portalGeometryIndex = index;
    }
    
    unsigned int getPortalGeometryIndex() const
    {
      return portalGeometryIndex;
    }

    void setDestinationCell( const unsigned int &destination )
    {
      destinationCell = destination;
    }

    unsigned int getDestinationCell() const
    {
      return destinationCell;
    }

    void print() const
    {
      std::cout << "Portal: " << portalId << std::endl;
      std::cout << "Portal geometry index: " << portalGeometryIndex
		<< std::endl;
      std::cout << "Destination cell: " << destinationCell << std::endl;
      std::cout << "Portal model filename: " << portalModelFilename
		<< std::endl;
      std::cout << "Portal matrix: " << std::endl;
      mat.print();
      
      std::cout << "Portal position: ";
      pos.print();
    }

  protected:
    unsigned int portalId;
    unsigned int portalGeometryIndex;
    unsigned int destinationCell;
    std::string  portalModelFilename;
    matrix3      mat;
    vector3      pos;
    
  private:
  };
}

#endif
