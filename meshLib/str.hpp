/** -*-c++-*-
 *  \class  str
 *  \file   str.hpp
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

#include <fstream>
#include <string>
#include <map>

#ifndef STR_HPP
#define STR_HPP

namespace ml
{
  class str
  {
  public:
    str();
    ~str();
    bool isRightType( std::istream &file );
    unsigned int readSTR( std::istream &file );
    void print() const;
	std::map< std::string, std::string >* getMap() {
		return &strMap;
	}

  protected:

  private:
    std::map< std::string, std::string> strMap;
  };
}
#endif
