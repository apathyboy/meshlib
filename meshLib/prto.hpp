/** -*-c++-*-
 *  \class  prto
 *  \file   prto.hpp
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
#include <meshLib/model.hpp>
#include <meshLib/matrix3.hpp>
#include <meshLib/vector3.hpp>
#include <meshLib/cell.hpp>

#include <fstream>
#include <string>
#include <map>

#ifndef PRTO_HPP
#define PRTO_HPP

namespace ml
{
  class prto : public model
  {
  public:
    prto();
    ~prto();
    bool isRightType( std::istream &file )
    {
      return isOfType( file, "PRTO" );
    }
    unsigned int readPRTO( std::istream &file, std::string path="" );

    unsigned int getNumCells() const
    {
      return numCells;
    }
    
    unsigned int getNumPortals() const
    {
      return numPortals;
    }
    

    cell &getCell( unsigned int i )
    {
      if( i < numCells )
	{
	  return cells[i];
	}
      else
	{
	  return cells[ numCells-1 ];
	}
    }

  protected:
    unsigned int readDATA( std::istream &file );
    unsigned int readPRTS( std::istream &file );
    unsigned int readPRTL( std::istream &file,
			   ml::matrix3 &mat,
			   ml::vector3 &vec );
    unsigned int readPRTLRecord( std::istream &file );
    unsigned int readCELS( std::istream &file );
    unsigned int readCELL( std::istream &file );
    unsigned int readCELLDATA( std::istream &file,
			       unsigned int &numCellPortals );
    unsigned int readLGHT( std::istream &file );
    unsigned int readPGRF( std::istream &file );
    unsigned int readMETA( std::istream &file );
    unsigned int readPNOD( std::istream &file );
    unsigned int readPEDG( std::istream &file );
    unsigned int readECNT( std::istream &file );
    unsigned int readESTR( std::istream &file );
    unsigned int readCRC( std::istream &file );

    unsigned int numAdjCells;
    unsigned int numPortals;
    unsigned int numCells;
    unsigned int crc;
		
    std::vector<cell> cells;
  private:

  };
}
#endif
