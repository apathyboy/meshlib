/** -*-c++-*-
 *  \class  foot
 *  \file   foot.cpp
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
#include <meshLib/foot.hpp>

#include <iostream>
#include <cstdlib>

using namespace ml;

foot::foot()
{
}

foot::~foot()
{
}

unsigned int foot::readFOOT( std::istream &file )
{
    unsigned int footSize;
    unsigned int total = readFormHeader( file, "FOOT", footSize );
    footSize += 8;
    std::cout << "Found FOOT form" << std::endl;

    unsigned int size;
    std::string form, type;
    total += readFormHeader( file, form, size, type );
    if( form != "FORM" )
    {
	std::cout << "Expected Form" << std::endl;
	throw std::exception();
    }
    std::cout << "Found form of type: " << type<< std::endl;

    total += readINFO( file );
    total += readPRNT( file );
    
    if( footSize == total )
    {
	std::cout << "Finished reading FOOT" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading FOOT" << std::endl;
	std::cout << "Read " << total << " out of " << footSize
                  << std::endl;
     }

    return total;
}


unsigned int foot::readINFO( std::istream &file  )
{
    std::string type;
    unsigned int infoSize;
    unsigned int total = readRecordHeader( file, type, infoSize );
    infoSize += 8;
    if( type != "INFO" )
    {
        std::cout << "Expected record of type INFO: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    unsigned int x;
    total += base::read( file, numColumns );
    std::cout << "Number columns: " << numColumns << std::endl;
    
    total += base::read( file, numRows );
    std::cout << "Num rows: " << numRows << std::endl;
    
    total += base::read( file, x );
    std::cout << "???: " << x << std::endl;
    
    total += base::read( file, x );
    std::cout << "???: " << x << std::endl;

    total += base::read( file, blockWidth );
    std::cout << std::fixed << blockWidth << std::endl;
    
    total += base::read( file, blockHeight );
    std::cout << std::fixed << blockHeight << std::endl;

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

unsigned int foot::readPRNT( std::istream &file )
{
    std::string type;
    unsigned int prntSize;
    unsigned int total = readRecordHeader( file, type, prntSize );
    prntSize += 8;
    if( type != "PRNT" )
    {
        std::cout << "Expected record of type PRNT: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    for( unsigned int i = 0; i < numRows; ++i )
      {
	std::string prntString;
	total += base::read( file, prntString );
	std::cout << prntString << std::endl;
      }

    if( prntSize == total )
    {
        std::cout << "Finished reading PRNT" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading PRNT" << std::endl;
        std::cout << "Read " << total << " out of " << prntSize
                  << std::endl;
     }

    return total;
}

void foot::print() const
{
}

