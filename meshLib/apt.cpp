/** -*-c++-*-
 *  \class  apt
 *  \file   apt.cpp
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
#include <meshLib/apt.hpp>

#include <iostream>
#include <cstdlib>

using namespace ml;

apt::apt()
{
}

apt::~apt()
{
}

unsigned int apt::readAPT( std::istream &file )
{
    unsigned int total = 0;
    std::string form;
    unsigned int aptSize;
    std::string type;

    total += readFormHeader( file, form, aptSize, type );
    aptSize += 8;
    if( form != "FORM" || type != "APT " )
    {
	std::cout << "Expected Form of type APT: " << type << std::endl;
	exit( 0 );
    }
    std::cout << "Found APT form" << std::endl;

    unsigned int size;
    total += readFormHeader( file, form, size, type );
    if( form != "FORM" )
    {
	std::cout << "Expected Form" << std::endl;
	exit( 0 );
    }
    std::cout << "Found form of type: " << type<< std::endl;

    total += readNAME( file, childFilename );
    
    if( aptSize == total )
    {
	std::cout << "Finished reading APT" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading APT" << std::endl;
	std::cout << "Read " << total << " out of " << aptSize
                  << std::endl;
     }

    return total;
}

unsigned int apt::readNAME( std::istream &file, std::string &filename )
{
    unsigned int total = 0;
    std::string form;
    std::string type;

    unsigned int nameSize;
    total += readRecordHeader( file, type, nameSize );
    nameSize += 8;
    if( type != "NAME" )
    {
        std::cout << "Expected record of type NAME: " << type << std::endl;
        exit( 0 );
    }
    std::cout << "Found " << type << std::endl;

    char temp[255];
    file.getline( temp, 255, 0 );
    filename = temp;
    total += filename.size() + 1;

    if( nameSize == total )
    {
        std::cout << "Finished reading NAME" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading NAME" << std::endl;
        std::cout << "Read " << total << " out of " << nameSize
                  << std::endl;
     }

    return total;
}

void apt::print() const
{
}

