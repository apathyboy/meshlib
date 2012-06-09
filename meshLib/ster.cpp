/** -*-c++-*-
 *  \class  ster
 *  \file   ster.cpp
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
#include <meshLib/ster.hpp>

#include <iostream>
#include <cstdlib>

using namespace ml;

ster::ster()
{
}

ster::~ster()
{
}

unsigned int ster::readSTER( std::istream &file )
{
    unsigned int sterSize;
    std::string type;

    unsigned int total = readFormHeader( file, "STER", sterSize );
    sterSize += 8;
    std::cout << "Found STER form" << std::endl;

    unsigned int size;
    std::string form;
    total += readFormHeader( file, form, size, type );
    if( form != "FORM" )
    {
	std::cout << "Expected FORM: " << form << std::endl;
	throw std::exception();
    }
    std::cout << "Found " << form << " " << type << std::endl;

    total += readPCNT( file );
    for( unsigned int i = 0; i < numNodes; ++i )
      {
	total += readXXXX( file );
      }

    if( sterSize == total )
    {
	std::cout << "Finished reading STER" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading STER" << std::endl;
	std::cout << "Read " << total << " out of " << sterSize
                  << std::endl;
     }

    return total;
}

void ster::print() const
{
}

unsigned int ster::readPCNT( std::istream &file )
{
    unsigned int pcntSize;
    std::string type;

    unsigned int total = readRecordHeader( file, type, pcntSize );
    pcntSize += 8;
    if( type != "PCNT" )
    {
        std::cout << "Expected record of type PCNT: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    if( 4 != pcntSize )
      {
        std::cout << "Expected size 4: " << pcntSize << std::endl;
        throw std::exception();
      }

    total += base::read( file, numNodes );
    std::cout << "numNodes: " << numNodes << std::endl;

    if( pcntSize == total )
    {
        std::cout << "Finished reading PCNT" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading PCNT" << std::endl;
        std::cout << "Read " << total << " out of " << pcntSize
                  << std::endl;
    }

    return total;
}

unsigned int ster::readXXXX( std::istream &file )
{
    std::string form;
    unsigned int xxxxSize;
    std::string type;

    unsigned int total = readRecordHeader( file, type, xxxxSize );
    xxxxSize += 8;
    if( type != "XXXX" )
    {
        std::cout << "Expected record of type XXXX: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    std::string name;
    total += base::read( file, name );
    std::cout << "name: " << name << std::endl;

    unsigned char x;
    total += base::read( file, x );
    std::cout << "?: " << (unsigned int)x << std::endl;

    std::string name2;
    total += base::read( file, name2 );
    std::cout << "name2: " << name2 << std::endl;

    if( "cover" == name )
      {
	unsigned short y;
	total += base::read( file, y );
	std::cout << "?: " << y << std::endl;

	unsigned char z;
	total += base::read( file, z );
	std::cout << "?: " << (unsigned int)z << std::endl;
      }

    if( xxxxSize == total )
    {
        std::cout << "Finished reading XXXX" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading XXXX" << std::endl;
        std::cout << "Read " << total << " out of " << xxxxSize
                  << std::endl;
    }

    return total;
}
