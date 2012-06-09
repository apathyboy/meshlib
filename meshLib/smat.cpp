/** -*-c++-*-
 *  \class  smat
 *  \file   smat.cpp
 *  \author Kenneth R. Sewell III

 meshLib is used for the parsing and exporting .msh models.
 Copyright (C) 2009 Kenneth R. Sewell III

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

#include <meshLib/smat.hpp>

#include <iostream>
#include <cstdlib>

using namespace ml;

smat::smat()
{
}

smat::~smat()
{
}

unsigned int smat::readSMAT( std::istream &file )
{
    unsigned int smatSize;
    unsigned int total = readFormHeader( file, "SMAT", smatSize );
    smatSize += 8;
    std::cout << "Found SMAT form"
	      << ": " << smatSize-12 << " bytes"
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

    total += readINFO( file );
    total += readMSGN( file );
    total += readSKTI( file );
    //total += readLATX( file );
    //total += readLDTB( file );
    total += readUnknown( file, smatSize - total );

    if( smatSize == total )
    {
	std::cout << "Finished reading SMAT" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading SMAT" << std::endl;
	std::cout << "Possibly a corrupt or non-finished file" << std::endl;
	std::cout << "Read " << total << " out of " << smatSize
                  << std::endl;
    }
    
    return total;
}

unsigned int smat::readINFO( std::istream &file )
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
    
    total += base::read( file, numMSGN );
    std::cout << "Num MSGN: " << numMSGN << std::endl;

    total += base::read( file, numSKTI );
    std::cout << "Num SKTI: " << numSKTI << std::endl;

    total += readUnknown( file, infoSize - total );

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

unsigned int smat::readMSGN( std::istream &file )
{
    std::string type;
    unsigned int msgnSize;
    unsigned int total = readRecordHeader( file, type, msgnSize );
    msgnSize += 8;
    if( type != "MSGN" )
    {
        std::cout << "Expected record of type MSGN: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    std::string name;
    for( unsigned int i = 0; i < numMSGN; ++i )
      {
	total += base::read( file, name );
	std::cout << name << std::endl;

	msgns.push_back(name);
      }

    if( msgnSize == total )
    {
        std::cout << "Finished reading MSGN" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading MSGN" << std::endl;
        std::cout << "Read " << total << " out of " << msgnSize
                  << std::endl;
     }

    return total;
}

unsigned int smat::readSKTI( std::istream &file )
{
    std::string type;
    unsigned int sktiSize;
    unsigned int total = readRecordHeader( file, type, sktiSize );
    sktiSize += 8;
    if( type != "SKTI" )
    {
        std::cout << "Expected record of type SKTI: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    std::string skeletonFile, name;
    for( unsigned short i = 0; i < numSKTI; ++i )
      {
	total += base::read( file, skeletonFile );
	std::cout << skeletonFile << " ";

	total += base::read( file, name );
	std::cout << name << std::endl;
      }

    if( sktiSize == total )
    {
        std::cout << "Finished reading SKTI" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading SKTI" << std::endl;
        std::cout << "Read " << total << " out of " << sktiSize
                  << std::endl;
     }

    return total;
}

unsigned int smat::readLATX( std::istream &file )
{
    std::string type;
    unsigned int latxSize;
    unsigned int total = readRecordHeader( file, type, latxSize );
    latxSize += 8;
    if( type != "LATX" )
    {
        std::cout << "Expected record of type LATX: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << ": " << latxSize-8 << " bytes"
	      << std::endl;

    unsigned short num;
    total += base::read( file, num );
    std::cout << "Num: " << num << std::endl;

    std::string name;
    for( unsigned short i = 0; i < numSKTI; ++i )
      {
	total += base::read( file, name );
	std::cout << name << " ";

	total += base::read( file, name );
	std::cout << name << std::endl;
      }

    if( latxSize == total )
    {
        std::cout << "Finished reading LATX" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading LATX" << std::endl;
        std::cout << "Read " << total << " out of " << latxSize
                  << std::endl;
     }

    return total;
}

unsigned int smat::readLDTB( std::istream &file )
{
    unsigned int ldtbSize;
    unsigned int total = readFormHeader( file, "LDTB", ldtbSize );
    ldtbSize += 8;
    std::cout << "Found LDTB form"
	      << ": " << ldtbSize-12 << " bytes"
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

    total += readLDTBINFO( file );

    total += readUnknown( file, ldtbSize - total );

    if( ldtbSize == total )
    {
        std::cout << "Finished reading LDTB" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading LDTB" << std::endl;
        std::cout << "Read " << total << " out of " << ldtbSize
                  << std::endl;
     }

    return total;
}

unsigned int smat::readLDTBINFO( std::istream &file )
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
    std::cout << "Found " << type << ": " << infoSize-8 << " bytes"
	      << std::endl;

    unsigned short num;
    total += base::read( file, num );
    std::cout << num << std::endl;

    for( unsigned int i = 0; i < num; ++i )
      {
	unsigned char u1;
	total += base::read( file, u1 );
	std::cout << (int)u1 << " ";

	total += base::read( file, u1 );
	std::cout << (int)u1 << " ";

	total += base::read( file, u1 );
	std::cout << (int)u1 << " ";

	total += base::read( file, u1 );
	std::cout << (int)u1 << " ";

	total += base::read( file, u1 );
	std::cout << (int)u1 << " ";

	total += base::read( file, u1 );
	std::cout << (int)u1 << " ";

	total += base::read( file, u1 );
	std::cout << (int)u1 << " ";

	total += base::read( file, u1 );
	std::cout << (int)u1 << std::endl;
      }

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


void smat::print() const
{
}
