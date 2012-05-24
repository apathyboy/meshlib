/** -*-c++-*-
 *  \class  spam
 *  \file   spam.cpp
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

#include <meshLib/spam.hpp>

#include <iostream>
#include <cstdlib>

#define MAX_SWG_STRING 2048

using namespace ml;

spam::spam()
{
}

spam::~spam()
{
}

unsigned int spam::readSPAM( std::istream &file )
{
    unsigned int spamSize;
    unsigned int total = readFormHeader( file, "SPAM", spamSize );
    spamSize += 8;
    std::cout << "Found SPAM form"
	      << ": " << spamSize-12 << " bytes"
	      << std::endl;

    unsigned int size;
  std::string form, type;
    total += readFormHeader( file, form, size, type );
    if( form != "FORM" )
    {
	std::cout << "Expected FORM: " << form << std::endl;
	exit( 0 );
    }
    std::cout << "Found " << form << " " << type
	      << ": " << size-4 << " bytes"
	      << std::endl;

    total += readAPPE( file );
    total += readCLIE( file );
    total += readPORT( file );
    total += readSOUN( file );

    if( spamSize == total )
    {
	std::cout << "Finished reading SPAM" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading SPAM" << std::endl;
	std::cout << "Possibly a corrupt or non-finished file" << std::endl;
	std::cout << "Read " << total << " out of " << spamSize
                  << std::endl;
    }
    
    return total;
}


unsigned int spam::readAPPE( std::istream &file )
{
    unsigned int formSize;
    unsigned int total = readFormHeader( file, "APPE", formSize );
    formSize += 8;
    std::cout << "Found APPE form"
	      << ": " << formSize-8 << " bytes"
	      << std::endl;
    
    unsigned int size;
    std::string type;
    total += readRecordHeader( file, type, size );
    size += 8;
    if( type != "0000" )
    {
	std::cout << "Expected record of type 0000: " << type << std::endl;
	exit( 0 );
    }

    while( total < size )
      {
	std::string newName;
	total += base::read( file, newName );
	appe.push_back( newName );
    }

    if( formSize == total )
    {
	std::cout << "Finished reading APPE" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading APPE" << std::endl;
	std::cout << "Read " << total << " out of " << formSize
                  << std::endl;
    }
    
    return total;
}

unsigned int spam::readCLIE( std::istream &file )
{
    unsigned int formSize;
    unsigned int total = readFormHeader( file, "CLIE", formSize );
    formSize += 8;
    std::cout << "Found CLIE form"
	      << ": " << formSize-8 << " bytes"
	      << std::endl;
    
    unsigned int size;
    std::string type;
    total += readRecordHeader( file, type, size );
    size += 8;
    if( type != "0000" )
    {
	std::cout << "Expected record of type 0000: " << type << std::endl;
	exit( 0 );
    }

    while( total < size )
    {
	std::string newName;
	total += base::read( file, newName );
	clie.push_back( newName );
    }

    if( formSize == total )
    {
	std::cout << "Finished reading CLIE" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading CLIE" << std::endl;
	std::cout << "Read " << total << " out of " << formSize
                  << std::endl;
    }
    
    return total;
}

unsigned int spam::readPORT( std::istream &file )
{
    unsigned int formSize;
    unsigned int total = readFormHeader( file, "PORT", formSize );
    formSize += 8;
    std::cout << "Found PORT form"
	      << ": " << formSize-8 << " bytes"
	      << std::endl;
    
    unsigned int size;
    std::string type;
    total += readRecordHeader( file, type, size );
    size += 8;
    if( type != "0000" )
    {
	std::cout << "Expected record of type 0000: " << type << std::endl;
	exit( 0 );
    }

    while( total < size )
    {
	std::string newName;
	total += base::read( file, newName );
	port.push_back( newName );
    }

    if( formSize == total )
    {
	std::cout << "Finished reading PORT" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading PORT" << std::endl;
	std::cout << "Read " << total << " out of " << formSize
                  << std::endl;
    }
    
    return total;
}

unsigned int spam::readSOUN( std::istream &file )
{
    unsigned int formSize;
    unsigned int total = readFormHeader( file, "SOUN", formSize );
    formSize += 8;
    std::cout << "Found SOUN form: " << formSize-8 << " bytes"
	      << std::endl;
    
    unsigned int size;
    std::string type;
    total += readRecordHeader( file, type, size );
    size += 8;
    if( type != "0000" )
    {
	std::cout << "Expected record of type 0000: " << type << std::endl;
	exit( 0 );
    }

    while( total < size )
    {
	std::string newName;
	total += base::read( file, newName );
	soun.push_back( newName );
    }

    if( formSize == total )
    {
	std::cout << "Finished reading SOUN" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading SOUN" << std::endl;
	std::cout << "Read " << total << " out of " << formSize
                  << std::endl;
    }
    
    return total;
}

void spam::print() const
{
    std::cout << "Appe" << std::endl;
    for( unsigned int i = 0; i < appe.size(); ++i )
    {
        std::cout << i << ": "
                  << appe[i]
                  << std::endl;
    }
    std::cout << "Clie" << std::endl;
    for( unsigned int i = 0; i < clie.size(); ++i )
    {
        std::cout << i << ": "
                  << clie[i]
                  << std::endl;
    }
    std::cout << "Port" << std::endl;
    for( unsigned int i = 0; i < port.size(); ++i )
    {
        std::cout << i << ": "
                  << port[i]
                  << std::endl;
    }
    std::cout << "Soun" << std::endl;
    for( unsigned int i = 0; i < soun.size(); ++i )
    {
        std::cout << i << ": "
                  << soun[i]
                  << std::endl;
    }
}
