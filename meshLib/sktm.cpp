/** -*-c++-*-
 *  \class  sktm
 *  \file   sktm.cpp
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
#include <meshLib/sktm.hpp>

#include <iostream>
#include <cstdlib>

using namespace ml;

sktm::sktm()
{
}

sktm::~sktm()
{
}

unsigned int sktm::readSKTM( std::istream &file )
{
    unsigned int sktmSize;
    unsigned int total = readFormHeader( file, "SKTM", sktmSize );
    sktmSize += 8;
    std::cout << "Found SKTM form" << std::endl;

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
    total += readNAME( file );
    total += readPRNT( file );
    total += readRPRE( file );
    total += readRPST( file );
    total += readBPTR( file );
    total += readBPRO( file );
    total += readJROR( file );
    
    if( sktmSize == total )
    {
	std::cout << "Finished reading SKTM" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading SKTM" << std::endl;
	std::cout << "Read " << total << " out of " << sktmSize
                  << std::endl;
     }

    return total;
}

unsigned int sktm::readINFO( std::istream &file )
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

    total += base::read( file, numBones );
    std::cout << "Num bones: " << numBones << std::endl;

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

unsigned int sktm::readNAME( std::istream &file )
{
    std::string type;
    unsigned int nameSize;
    unsigned int total = readRecordHeader( file, type, nameSize );
    nameSize += 8;
    if( type != "NAME" )
    {
        std::cout << "Expected record of type NAME: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    std::string filename;
    for( unsigned int i = 0; i < numBones; ++i )
      {
	total += base::read( file, filename );
	std::cout << i << ": " << filename << std::endl;
	boneName.push_back( filename );
      }

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

void sktm::print() const
{
}

/// Parent bone
unsigned int sktm::readPRNT( std::istream &file )
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

    if( (prntSize-8)/numBones != 4 )
      {
	std::cout << "Expected 4 byte values" << std::endl;
	throw std::exception();
      }

    int parent;
    for( unsigned int i = 0; i < numBones; ++i )
      {
	total += base::read( file, parent );
	boneParent.push_back( parent );

	std::cout << "Bone " << boneName[i];
	if( parent < 0 )
	  {
	    std::cout  << " has no parent.";
	  }
	else
	  {
	    std::cout  << " has parent bone " << boneName[parent];
	  }
	std::cout << std::endl;
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


unsigned int sktm::readRPRE( std::istream &file )
{
    std::string type;
    unsigned int rpreSize;
    unsigned int total = readRecordHeader( file, type, rpreSize );
    rpreSize += 8;
    if( type != "RPRE" )
    {
        std::cout << "Expected record of type RPRE: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    if( (rpreSize-8)/numBones != 16 )
      {
	std::cout << "Expected 16 byte values" << std::endl;
	throw std::exception();
      }

    std::cout << std::fixed;
    float x, y, z, w;
    for( unsigned int i = 0; i < numBones; ++i )
      {
	total += base::read( file, x );
	total += base::read( file, y );
	total += base::read( file, z );
	total += base::read( file, w );

	bonePreQuatX.push_back( x );
	bonePreQuatY.push_back( y );
	bonePreQuatZ.push_back( z );
	bonePreQuatW.push_back( w );

	std::cout << "Bone ";
	std::cout.width( 10 );
	std::cout << boneName[i] << ": "
		  << x << " "
		  << y << " "
		  << z << " "
		  << w << std::endl;
      }

    if( rpreSize == total )
    {
        std::cout << "Finished reading RPRE" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading RPRE" << std::endl;
        std::cout << "Read " << total << " out of " << rpreSize
                  << std::endl;
     }

    return total;
}

unsigned int sktm::readRPST( std::istream &file )
{
    std::string type;
    unsigned int rpstSize;
    unsigned int total = readRecordHeader( file, type, rpstSize );
    rpstSize += 8;
    if( type != "RPST" )
    {
        std::cout << "Expected record of type RPST: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    if( (rpstSize-8)/numBones != 16 )
      {
	std::cout << "Expected 16 byte values" << std::endl;
	throw std::exception();
      }

    std::cout << std::fixed;
    float x, y, z, w;
    for( unsigned int i = 0; i < numBones; ++i )
      {
	total += base::read( file, x );
	total += base::read( file, y );
	total += base::read( file, z );
	total += base::read( file, w );

	bonePostQuatX.push_back( x );
	bonePostQuatY.push_back( y );
	bonePostQuatZ.push_back( z );
	bonePostQuatW.push_back( w );

	std::cout << "Bone ";
	std::cout.width( 10 );
	std::cout << boneName[i] << ": "
		  << x << " "
		  << y << " "
		  << z << " "
		  << w << std::endl;
      }

    if( rpstSize == total )
    {
        std::cout << "Finished reading RPST" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading RPST" << std::endl;
        std::cout << "Read " << total << " out of " << rpstSize
                  << std::endl;
     }

    return total;
}

unsigned int sktm::readBPTR( std::istream &file )
{
    std::string type;
    unsigned int bptrSize;
    unsigned int total = readRecordHeader( file, type, bptrSize );
    bptrSize += 8;
    if( type != "BPTR" )
    {
        std::cout << "Expected record of type BPTR: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    if( (bptrSize-8)/numBones != 12 )
      {
	std::cout << "Expected 12 byte values" << std::endl;
	throw std::exception();
      }

    float x, y, z;
    for( unsigned int i = 0; i < numBones; ++i )
      {
	total += base::read( file, x );
	total += base::read( file, y );
	total += base::read( file, z );
	boneXOffset.push_back( x );
	boneYOffset.push_back( y );
	boneZOffset.push_back( z );

	std::cout << "Bone ";
	std::cout.width( 10 );
	std::cout << boneName[i] << ": "
		  << x << " "
		  << y << " "
		  << z << std::endl;
      }

    if( bptrSize == total )
    {
        std::cout << "Finished reading BPTR" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading BPTR" << std::endl;
        std::cout << "Read " << total << " out of " << bptrSize
                  << std::endl;
     }

    return total;
}

unsigned int sktm::readBPRO( std::istream &file )
{
    std::string type;
    unsigned int bproSize;
    unsigned int total = readRecordHeader( file, type, bproSize );
    bproSize += 8;
    if( type != "BPRO" )
    {
        std::cout << "Expected record of type BPRO: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    if( (bproSize-8)/numBones != 16 )
      {
	std::cout << "Expected 16 byte values" << std::endl;
	throw std::exception();
      }

    float value;
    for( unsigned int i = 0; i < numBones; ++i )
      {
	std::cout << "Bone ";
	std::cout.width( 10 );
	std::cout << boneName[i] << ": ";

	total += base::read( file, value );
	std::cout << value << " ";

	total += base::read( file, value );
	std::cout << value << " ";

	total += base::read( file, value );
	std::cout << value << " ";

	total += base::read( file, value );
	std::cout << value << " ";
	std::cout << std::endl;
      }

    if( bproSize == total )
    {
        std::cout << "Finished reading BPRO" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading BPRO" << std::endl;
        std::cout << "Read " << total << " out of " << bproSize
                  << std::endl;
     }

    return total;
}

unsigned int sktm::readJROR( std::istream &file )
{
    std::string type;
    unsigned int jrorSize;
    unsigned int total = readRecordHeader( file, type, jrorSize );
    jrorSize += 8;
    if( type != "JROR" )
    {
        std::cout << "Expected record of type JROR: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    if( (jrorSize-8)/numBones != 4 )
      {
	std::cout << "Expected 4 byte values" << std::endl;
	throw std::exception();
      }

    unsigned int value;
    for( unsigned int i = 0; i < numBones; ++i )
      {
	std::cout << "Bone ";
	std::cout.width( 10 );
	std::cout << boneName[i] << ": ";

	total += base::read( file, value );
	std::cout << value << std::endl;
      }
    std::cout << std::endl;

    if( jrorSize == total )
    {
        std::cout << "Finished reading JROR" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading JROR" << std::endl;
        std::cout << "Read " << total << " out of " << jrorSize
                  << std::endl;
     }

    return total;
}

