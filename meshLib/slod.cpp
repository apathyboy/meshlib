/** -*-c++-*-
 *  \class  slod
 *  \file   slod.cpp
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

/**
   This class still needs work.
 */

#include <meshLib/base.hpp>
#include <meshLib/slod.hpp>

#include <iostream>
#include <cstdlib>

using namespace ml;

slod::slod()
{
}

slod::~slod()
{
}

unsigned int slod::readSLOD( std::istream &file )
{
    unsigned int slodSize;
    std::string type;

    unsigned int total = readFormHeader( file, "SLOD", slodSize );
    slodSize += 8;
    std::cout << "Found SLOD form" << std::endl;

    unsigned int size;
    std::string form;
    total += readFormHeader( file, form, size, type );
    if( form != "FORM" )
    {
	std::cout << "Expected Form" << std::endl;
	exit( 0 );
    }
    std::cout << "Found form of type: " << type<< std::endl;

    unsigned short numSktm;
    total += readINFO( file, numSktm );

    for( unsigned int i = 0; i < numSktm; ++i )
      {
	ml::sktm newSKTM;
	skeletonList.push_back( newSKTM );
	total += skeletonList.back().readSKTM( file );
      }
    
    if( slodSize == total )
    {
	std::cout << "Finished reading SLOD" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading SLOD" << std::endl;
	std::cout << "Read " << total << " out of " << slodSize
                  << std::endl;
     }

    return total;
}

unsigned int slod::readINFO( std::istream &file, unsigned short &value )
{
    std::string type;
    unsigned int infoSize;
    unsigned int total = readRecordHeader( file, type, infoSize );
    infoSize += 8;
    if( type != "INFO" )
    {
        std::cout << "Expected record of type INFO: " << type << std::endl;
        exit( 0 );
    }
    std::cout << "Found " << type << std::endl;
    
    total += base::read( file, value );

    if( infoSize == total )
    {
        std::cout << "Finished reading INFO" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading INFO" << std::endl;
        std::cout << "Read " << total << " out of " << infoSize
                  << std::endl;
     }

    return total;
}
