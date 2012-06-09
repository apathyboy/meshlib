/** -*-c++-*-
 *  \class  smat
 *  \file   smat.hpp
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

#include <meshLib/base.hpp>

#include <fstream>
#include <vector>
#include <string>

#ifndef SMAT_HPP
#define SMAT_HPP

namespace ml
{
  class smat : public base
  {
  public:
    smat();
    ~smat();
    bool isRightType( std::istream &file )
    {
      return isOfType( file, "SMAT" );
    }
    unsigned int readSMAT( std::istream &file );
    void print() const;

	std::vector<std::string>& getMSGNS() {
		return msgns;
	}

  protected:
    unsigned int readINFO( std::istream &file );
    unsigned int readMSGN( std::istream &file );
    unsigned int readSKTI( std::istream &file );
    unsigned int readLATX( std::istream &file );
    unsigned int readLDTB( std::istream &file );
    unsigned int readLDTBINFO( std::istream &file );

    unsigned int numMSGN;
    unsigned short numSKTI;
  private:
	  std::vector<std::string> msgns;
  };
} 
#endif
