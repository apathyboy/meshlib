/** -*-c++-*-
 *  \class  cldf
 *  \file   cldf.cpp
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
#include <meshLib/base.hpp>
#include <meshLib/cldf.hpp>

#include <iostream>
#include <cstdlib>

using namespace ml;

cldf::cldf()
{
}

cldf::~cldf()
{
}

unsigned int cldf::readCLDF( std::istream &file )
{
//  basePath = path;
  unsigned int cldfSize;
  unsigned int total = readFormHeader( file, "CLDF", cldfSize );
  cldfSize += 8;
  std::cout << "Found CSHD form" << std::endl;

  unsigned int size;
  std::string form, type;
  total += readFormHeader( file, form, size, type );
  if( form != "FORM" )
    {
      std::cout << "Expected FORM: " << form << std::endl;
      throw std::exception();
    }
  std::cout << "Found " << form << " " << type << std::endl;
   
  base::peekHeader( file, form, size, type );

  std::cout << " form:" << form << " type:" << std::endl;

  while (total < cldfSize) 
  {
	base::peekHeader( file, form, size, type );

	if (form == "FORM") {
		//std::cout << " form:" << form << " type:" << std::endl;

		//base::readUnknown(file, size + 8);

		//total += size + 8;
		total += readWEAR(file);

	} else {
		base::readUnknown(file, size + 8);

		total += size + 8;
	}
  }

  if( cldfSize == total )
    {
      std::cout << "Finished reading readCLDF" << std::endl;
    }
  else
    {
      std::cout << "FAILED in reading readCLDF" << std::endl;
      std::cout << "Read " << total << " out of " << cldfSize
		<< std::endl;
    }

  return total;
}

unsigned int cldf::readWEAR( std::istream &file ) {
unsigned int wearSize;
  unsigned int total = readFormHeader( file, "WEAR", wearSize );
  wearSize += 8;
  std::cout << "Found WEAR form" << std::endl;

  //readRecordHeader(file, "

  unsigned int size;
  std::string form, type, name;
 
  base::peekHeader( file, form, size, type );

  while (total < wearSize) {

	  base::peekHeader( file, form, size, type );

	if (form == "MESH") {
		 total += base::readRecordHeader(file, type, size);

		 total += base::read( file, name );
			std::cout << name << std::endl;

			wearMeshes.push_back(name);

	 } else {
		  base::readUnknown(file, size + 8);

			 total += size + 8;
	  }
  }

  return total;
}

