/** -*-c++-*-
 *  \class  cell
 *  \file   cell.hpp
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
#include <meshLib/portal.hpp>
#include <vector>

#ifndef CELL_HPP
#define CELL_HPP

namespace ml
{
  class cell
  {
  public:
    cell(){}
    ~cell(){}
    
    void setUnknown1( unsigned char u1 )
    {
      m_Unknown1 = u1;
    }

    unsigned char getUnknown1() const
    {
      return m_Unknown1;
    }

    void setName( const std::string &name )
    {
      m_Name = name;
    }
    
    const std::string &getName() const
    {
      return m_Name;
    }

    void setModelFilename( const std::string &filename )
    {
      m_ModelFilename = filename;
    }
    
    const std::string &getModelFilename() const
    {
      return m_ModelFilename;
    }

    void setHasFloor( bool floor )
    {
      m_HasFloor = floor;
    }

    bool hasFloor() const
    {
      return m_HasFloor;
    }

    void setFloorFilename( const std::string &filename )
    {
      m_FloorFilename = filename;
    }
    
    const std::string &getFloorFilename() const
    {
      return m_FloorFilename;
    }

  protected:
    unsigned int numPortals;
    std::vector<portal> portals;

    unsigned char m_Unknown1;
    std::string m_Name;
    std::string m_ModelFilename;
    bool m_HasFloor;
    std::string m_FloorFilename;

  private:
  };
}

#endif
