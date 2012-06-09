/** -*-c++-*-
 *  \class  scot
 *  \file   scot.cpp
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
#include <meshLib/scot.hpp>

#include <iostream>
#include <cstdlib>

using namespace ml;

scot::scot()
{
}

scot::~scot()
{
}

unsigned int scot::readSCOT( std::istream &file )
{
    unsigned int scotSize;
    unsigned int total = readFormHeader( file, "SCOT", scotSize );
    scotSize += 8;
    std::cout << "Found SCOT form" << std::endl;

    total += readDERV( file, scotBaseObjectFilename );

	unsigned int verSize; std::string nexttype; std::string nextform;
	peekHeader(file, nextform, verSize, nexttype);

    unsigned int size0001;
    total += readFormHeader( file, nexttype, size0001 );
    size0001 += 8;
    std::cout << "Found " << nexttype << " form" << std::endl;

    total += readPCNT( file, numNodes );
    for( unsigned int i = 0; i < numNodes; ++i )
      {
	total += readSCOTXXXX( file );
      }

    total += readSTOT( file );

//	total += readSHOT( file );

    if( scotSize == total )
    {
	std::cout << "Finished reading SCOT" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading SCOT" << std::endl;
	std::cout << "Read " << total << " out of " << scotSize
                  << std::endl;
     }

    return total;
}

void scot::print() const
{
}

unsigned int scot::readSCOTXXXX( std::istream &file )
{
    unsigned int xxxxSize;
    std::string type;
    unsigned int total = readRecordHeader( file, type, xxxxSize );

	base::readUnknown(file, xxxxSize);

	return xxxxSize + 8;
/*
    if( type != "XXXX" )
    {
        std::cout << "Expected record of type XXXX: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    std::string property;
    total += base::read( file, property );
    std::cout << "Property: " << property << std::endl;

    unsigned char enabled;
    if( property == "terrainModificationFileName" )
      {
	total += base::read( file, enabled );
	if( enabled > 0 )
	  {
	    total += base::read( file, terrainModificationFilename );
	    
	    std::cout << property << ": "
		      << terrainModificationFilename
		      << std::endl;
	  }
      }
    else if( property == "interiorLayoutFileName" )
      {
	total += base::read( file, enabled );
	if( enabled > 0 )
	  {
	    total += base::read( file, interiorLayoutFilename );
	    
	    std::cout << property << ": "
		      << interiorLayoutFilename
		      << std::endl;
	  }
      }
    else if( property == "portalLayoutFilename" )
      {
	total += base::read( file, enabled );
	if( enabled > 0 )
	  {
	    total += base::read( file, portalLayoutFilename );

	    std::cout << property << ": "
		      << portalLayoutFilename
		      << std::endl;
	  }
      }
    else
      {
	std::cout << "Unknown: " << property << std::endl;
	throw std::exception();
      }

    if( xxxxSize == (total-8) )
    {
        std::cout << "Finished reading XXXX" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading XXXX" << std::endl;
        std::cout << "Read " << total << " out of " << xxxxSize
                  << std::endl;
    }

    return total;*/
}
