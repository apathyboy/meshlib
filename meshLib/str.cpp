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

#include <meshLib/base.hpp>
#include <meshLib/str.hpp>

#include <iostream>
#include <string>
#include <vector>

using namespace ml;

str::str()
{
}

str::~str()
{
}

bool str::isRightType( std::istream &file )
{
    unsigned int position = file.tellg();
    unsigned int header;
    base::read( file, header );
    file.seekg( position, std::ios_base::beg );

    return ( 0xabcd == header );
}

unsigned int str::readSTR( std::istream &file )
{
    unsigned int position = file.tellg();
    unsigned int header;
    unsigned int total = base::read( file, header );

    // Check for .str header data
    if( header != 0xabcd )
    {
	std::cout << ".str header not found" << std::endl;
	file.seekg( position, std::ios_base::beg );
	return 0;
    }

    unsigned char unknown;
    total += base::read( file, unknown );
    std::cout << "Unknown: " << (unsigned int)unknown << std::endl;

    unsigned int unknown1;
    total += base::read( file, unknown1 );
    std::cout << "Unknown: " << unknown1 << std::endl;
    
    // Number of ids and descriptions
    unsigned int numStrings;
    total += base::read( file, numStrings );
    std::cout << "Num strings: " << numStrings << std::endl;

    // Allocate vectors to hold IDs and descriptions...
    //std::vector< std::string > id( numStrings );
	std::map<int, std::string> id;
    //std::vector< std::string > desc( numStrings );
	std::map<int, std::string> desc;

    //Read the descriptions
    unsigned int num, key, size;
    for( unsigned int j = 0; j < numStrings; ++j )
    {
      total += base::read( file, num );
      total += base::read( file, key );
      total += base::read( file, size );
      
      std::string description;
      
      char *temp = new char[size*2];
      file.read( temp, size*2 );
      for( unsigned int i = 0; i < size; ++i )
	{
	  description.push_back( temp[i*2] );
	}
      delete[] temp;
      
      // number of 2-byte characters
      total +=  size * 2;
      
      //desc[num-1] = description;
	  desc[num] = description;
    }

    // Read the ID's
    for( unsigned int j = 0; j < numStrings; ++j )
    {
      total += base::read( file, num );
      total += base::read( file, size );
      
      char *temp = new char[size];
      file.read( temp, size );
      std::string name( temp, size );
      delete[] temp;
      
      // Number of characters
      total += size;
      
      //id[num-1] = name;
	  id[num] = name;
    }

    // Erase current map, populate with new data...
    strMap.clear();

	std::map<int, std::string>::const_iterator end = id.end();

	for (std::map<int, std::string>::const_iterator it = id.begin(); it != end; ++it) {
		int num = it->first;
		std::string id = it->second;

		//std::string value = desc[num];

		strMap[id] = desc[num];
	}

   /* for( unsigned int i = 0; i < numStrings; ++i )
    {
	//std::cout << id[i] << ": " << desc[i] << std::endl;
	strMap[id[i]] = desc[i];
    }*/

    return total;
}


void str::print() const
{
    // Print out the map
    std::map< std::string, std::string>::const_iterator i;
    unsigned int j = 1;
    for( i = strMap.begin(); i != strMap.end(); ++i, ++j )
    {
	std::cout << j << ": " << i->first << std::endl;
	std::cout << "\t" << i->second << std::endl;
	std::cout << std::endl;
    }
}
