/** -*-c++-*-
 *  \class  stot
 *  \file   stot.hpp
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
#include <meshLib/shot.hpp>

#include <fstream>
#include <string>
#include <vector>

#ifndef STOT_HPP
#define STOT_HPP

namespace ml
{
  class stot : public shot
  {
  public:
    stot();
    ~stot();
    bool isRightType( std::istream &file )
    {
      return isOfType( file, "STOT" );
    }
    unsigned int readSTOT( std::istream &file );
    void print() const;

	std::string getStotBaseObjectFilename() {
		return stotBaseObjectFilename;
	}

  protected:
    unsigned int readSTOTXXXX( std::istream &file );

    unsigned int numNodes;
    std::string stotBaseObjectFilename;

  };
}
#endif
