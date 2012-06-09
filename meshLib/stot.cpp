/** -*-c++-*-
 *  \class  stot
 *  \file   stot.cpp
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
#include <meshLib/stot.hpp>

#include <iostream>
#include <cstdlib>

using namespace ml;

stot::stot()
{
}

stot::~stot()
{
}

unsigned int stot::readSTOT( std::istream &file )
{
    unsigned int stotSize;
    unsigned int total = readFormHeader( file, "STOT", stotSize );
    stotSize += 8;
    std::cout << "Found STOT form" << std::endl;

    total += readDERV( file, stotBaseObjectFilename );

    unsigned int size;
    std::string form, type;
    total += readFormHeader( file, form, size, type );
    //size += 8;
    if( form != "FORM" )
    {
	std::cout << "Expected FORM: " << form << std::endl;
	throw std::exception();
    }
    std::cout << "Found FORM:" << type << std::endl;

    /*total += readPCNT( file, numNodes );
    for( unsigned int i = 0; i < numNodes; ++i )
      {
	total += readSTOTXXXX( file );
      }*/

	total += base::readUnknown(file, size - 4);



    total += readSHOT( file );

    if( stotSize == total )
    {
	std::cout << "Finished reading STOT" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading STOT" << std::endl;
	std::cout << "Read " << total << " out of " << stotSize
                  << std::endl;
     }

    return total;
}

void stot::print() const
{
}

unsigned int stot::readSTOTXXXX( std::istream &file )
{

	 unsigned int xxxxSize;
    std::string type;
    unsigned int total = readRecordHeader( file, type, xxxxSize );

	base::readUnknown(file, xxxxSize);

	return xxxxSize + 8;

    /*unsigned int xxxxSize;
    std::string type;
    unsigned int total = readRecordHeader( file, type, xxxxSize );
    if( type != "XXXX" )
    {
        std::cout << "Expected record of type XXXX: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    std::string property;
    total += base::read( file, property );
    std::cout << "Property: " << property << std::endl;
    total += property.size() + 1;

    if( property == "paletteColorCustomizationVariables" )
      {
        file.seekg( xxxxSize - (property.size() + 1 ), std::ios_base::cur );
        total += xxxxSize - ( property.size() + 1 );
      }
    else if( property == "rangedIntCustomizationVariables" )
      {
        file.seekg( xxxxSize - (property.size() + 1 ), std::ios_base::cur );
        total += xxxxSize - ( property.size() + 1 );
      }
    else if( property == "constStringCustomizationVariables" )
      {
        file.seekg( xxxxSize - (property.size() + 1 ), std::ios_base::cur );
        total += xxxxSize - ( property.size() + 1 );
      }
    else if( property == "socketDestinations" )
      {
        file.seekg( xxxxSize - (property.size() + 1 ), std::ios_base::cur );
        total += xxxxSize - ( property.size() + 1 );
      }
    else if( property == "structureFootprintFileName" )
      {
        file.seekg( xxxxSize - (property.size() + 1 ), std::ios_base::cur );
        total += xxxxSize - ( property.size() + 1 );
      }
    else if( property == "useStructureFootprintOutline" )
      {
        file.seekg( xxxxSize - (property.size() + 1 ), std::ios_base::cur );
        total += xxxxSize - ( property.size() + 1 );
      }
    else if( property == "targetable" )
      {
        file.seekg( xxxxSize - (property.size() + 1 ), std::ios_base::cur );
        total += xxxxSize - ( property.size() + 1 );
      }
    else if( property == "certificationsRequired" )
      {
        file.seekg( xxxxSize - (property.size() + 1 ), std::ios_base::cur );
        total += xxxxSize - ( property.size() + 1 );
      }
    else if( property == "customizationVariableMapping" )
      {
        file.seekg( xxxxSize - (property.size() + 1 ), std::ios_base::cur );
        total += xxxxSize - ( property.size() + 1 );
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
