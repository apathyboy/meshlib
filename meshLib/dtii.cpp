/** -*-c++-*-
 *  \class  dtii
 *  \file   dtii.cpp
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

#include <meshLib/dtii.hpp>
#include <iostream>
#include <cstdlib>

#define MAX_SWG_STRING 2048

using namespace ml;

dtii::dtii()
{
    temp = new char[MAX_SWG_STRING];
}

dtii::~dtii()
{
    delete[] temp;
}

unsigned int dtii::readDTII( std::istream &file )
{
    unsigned int dtiiSize;
    unsigned int total = readFormHeader( file, "DTII", dtiiSize );
    dtiiSize += 8;
    std::cout << "Found DTII form"
	      << ": " << dtiiSize-12 << " bytes"
	      << std::endl;

    unsigned int size;
    std::string form, type;
    total += readFormHeader( file, form, size, type );
    if( form != "FORM" )
    {
	std::cout << "Expected FORM: " << form << std::endl;
	throw std::exception();
    }
    std::cout << "Found " << form << " " << type
	      << ": " << size-4 << " bytes"
	      << std::endl;

    total += readCOLS( file );
    total += readTYPE( file );
    total += readROWS( file );

    //total += readUnknown( file, dtiiSize - total );

    if( dtiiSize == total )
    {
	std::cout << "Finished reading DTII" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading DTII" << std::endl;
	std::cout << "Possibly a corrupt or non-finished file" << std::endl;
	std::cout << "Read " << total << " out of " << dtiiSize
                  << std::endl;
    }
    
    return total;
}


unsigned int dtii::readCOLS( std::istream &file )
{
    unsigned int colsSize;
    std::string type;
    unsigned int total = readRecordHeader( file, type, colsSize );
    colsSize += 8;
    if( type != "COLS" )
    {
	std::cout << "Expected record of type COLS: " << type << std::endl;
	throw std::exception();
    }
    std::cout << "Found COLS record"
	      << ": " << colsSize-8 << " bytes"
	      << std::endl;

    total += base::read( file, numColumns );

    columnName.clear();
    for( unsigned int i = 0; i < numColumns; ++i )
    {
      std::string name;
      total += base::read( file, name );
      columnName.push_back( name );
      std::cout << i << ": " << name << std::endl;
    }
    std::cout << std::endl;

    if( colsSize == total )
    {
	std::cout << "Finished reading COLS" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading COLS" << std::endl;
	std::cout << "Read " << total << " out of " << colsSize
                  << std::endl;
    }
    
    return total;
}

unsigned int dtii::readTYPE( std::istream &file )
{
    unsigned int typeSize;
    std::string type;
    unsigned int total = readRecordHeader( file, type, typeSize );
    typeSize += 8;
    if( type != "TYPE" )
    {
	std::cout << "Expected record of type TYPE: " << type << std::endl;
	throw std::exception();
    }
    std::cout << "Found TYPE record"
	      << ": " << typeSize-8 << " bytes"
	      << std::endl;

    columnType.clear();
    for( unsigned int i = 0; i < numColumns; ++i )
    {
      std::string name;
      total += base::read( file, name );
      columnType.push_back( name );
      std::cout << i << ": " << name << std::endl;
    }
    std::cout << std::endl;

    if( typeSize == total )
    {
	std::cout << "Finished reading TYPE" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading TYPE" << std::endl;
	std::cout << "Read " << total << " out of " << typeSize
                  << std::endl;
    }
    
    return total;
}

unsigned int dtii::readROWS( std::istream &file )
{
   unsigned int rowsSize;
   std::string type;
   unsigned int total = readRecordHeader( file, type, rowsSize );
    rowsSize += 8;
    if( type != "ROWS" )
    {
	std::cout << "Expected record of type ROWS: " << type << std::endl;
	throw std::exception();
    }
    std::cout << "Found ROWS record"
	      << ": " << rowsSize-8 << " bytes"
	      << std::endl;

    total += base::read( file, numRows );
    std::cout << "Number of rows: " << numRows << std::endl;

    for( unsigned int row = 0; row < numRows; ++row )
    {
	std::cout << "Row " << row << ": " << std::endl;
	for( unsigned int i = 0; i < numColumns; ++i )
	{
	    std::cout << columnName[i] << ": ";
	    
	    if( 'i' == (columnType[i])[0] )
	      {
		int x;
		total += base::read( file, x );
		std::cout << x << std::endl;
	      }
	    else if( 'I' == (columnType[i])[0] )
	      {
		int x;
		total += base::read( file, x );
		std::cout << x << std::endl;
	      }
	    else if( 'f' == (columnType[i])[0] )
	      {
		float x;
		total += base::read( file, x );
		std::cout << x << std::endl;
	      }
	    else if( 'z' == (columnType[i])[0] )
	      {
		int x;
		total += base::read( file, x );
		std::cout << x << std::endl;
	      }
	    else if( 'e' == (columnType[i])[0] )
	      {
		int x;
		total += base::read( file, x );
		std::cout << x << std::endl;
	      }
	    else if( 's' == (columnType[i])[0] )
	      {
		std::string name;
		total += base::read( file, name );
		std::cout << name << std::endl;
	      }
	    else if( 'b' == (columnType[i])[0] )
	      {
		unsigned int x;
		total += base::read( file, x );
		std::cout << x << std::endl;
	      }
	    else if( 'h' == (columnType[i])[0] )
	      {
		unsigned int x;
		total += base::read( file, x );
		std::cout << std::hex << "0x" << x << std::dec << std::endl;
	      }
	    else
	      {
		std::cout << "Error: Unknown type: " << columnType[i]
			  << std::endl;
		throw std::exception();
	      }
	}
	std::cout << std::endl;
    }

    return total;
}

void dtii::print() const
{
}
