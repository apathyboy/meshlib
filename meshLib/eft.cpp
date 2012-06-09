/** -*-c++-*-
 *  \class  eft
 *  \file   eft.cpp
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
#include <meshLib/eft.hpp>

#include <iostream>
#include <bitset>
#include <cstdlib>

using namespace ml;

eft::eft()
    :
    numTextures( 1 )
{
}

eft::~eft()
{
}

unsigned int eft::readEFT( std::istream &file, std::string path )
{
  basePath = path;
  unsigned int eftSize;
  unsigned int total = readFormHeader( file, "EFCT", eftSize );
  eftSize += 8;
  std::cout << "Found EFCT form"
	    << ": " << eftSize-12 << " bytes"
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


  // Read DATA record
  total += readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected record of type DATA: " << type << std::endl;
      throw std::exception();
    }
  if( size != 2 )
    {
      std::cout << "Expected DATA record of size 2: " << size << std::endl;
      throw std::exception();
    }

  unsigned short numIMPL;
  total += base::read( file, numIMPL );
  std::cout << "Number of IMPL records: " << (int)numIMPL << std::endl;

  for( unsigned short i = 0; i < numIMPL; ++i )
    {
      total += readIMPL( file );
    }

  if( eftSize == total )
    {
      std::cout << "Finished reading EFCT" << std::endl;
    }
  else
    {
      std::cout << "FAILED in reading EFCT" << std::endl;
      std::cout << "Read " << total << " out of " << eftSize
		<< std::endl;
    }
    
  return total;
}

unsigned int eft::readIMPL( std::istream &file )
{
    unsigned int implSize;
    unsigned int total = readFormHeader( file, "IMPL", implSize );
    implSize += 8;
    std::cout << "Found FORM IMPL: " << implSize-12 << " bytes"
	      << std::endl;

    unsigned int size;
    std::string form, type;
    total += readFormHeader( file, form, size, type );
    if( form != "FORM")
    {
	std::cout << "Expected FORM not: " << form << std::endl;
	throw std::exception();
    }
    std::cout << "Found " << form << " " << type
	      << ": " << size-4 << " bytes"
	      << std::endl;

    while( total < implSize )
    {
      // Peek at next record, but keep file at same place.
      peekHeader( file, form, size, type );

	if( form == "SCAP" )
	{
	    total += readSCAP( file );
	}
	else if( form == "OPTN" )
	{
	    total += readOPTN( file );
	}
	else if( form == "DATA" )
	{
	    total += readIMPLDATA( file );
	}
	else if( form == "FORM" && type == "PASS" )
	{
	    total += readPASS( file );
	}
	else
	{
	    std::cout << "Unexpected record: " << form << std::endl;
	    throw std::exception();
	}

    }
    if( implSize == total )
    {
	std::cout << "Finished reading IMPL" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading IMPL" << std::endl;
	std::cout << "Read " << total << " out of " << implSize
                  << std::endl;
    }

    return total;
}


unsigned int eft::readSCAP( std::istream &file )
{
    unsigned int scapSize;
    std::string type;
    unsigned int total = readRecordHeader( file, type, scapSize );
    if( type != "SCAP" )
    {
        std::cout << "Expected record of type SCAP: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found record " << type 
	      << " (Set Capabilities?) "
	      << scapSize << " bytes"
	      << std::endl;

    unsigned int numScap = scapSize/4;

    unsigned int data;
    for( unsigned int i = 0; i < numScap; ++i )
    {
      total += base::read( file, data );
      std::cout << std::bitset<32>( (int)data ) << " " << std::endl;
    }
    total += scapSize;

    if( scapSize == (total-8) )
    {
	std::cout << "Finished reading SCAP" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading SCAP" << std::endl;
	std::cout << "Read " << total << " out of " << scapSize
                  << std::endl;
    }

    return total;
}

unsigned int eft::readOPTN( std::istream &file )
{
    unsigned int optnSize;
    std::string type;
    unsigned int total = readRecordHeader( file, type, optnSize );
    if( type != "OPTN" )
    {
        std::cout << "Expected record of type OPTN: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found record " << type
	      << ": " << optnSize << " bytes"
	      << std::endl;

    // Skip data for now
    total += readUnknown( file, optnSize );

    if( optnSize == (total-8) )
    {
	std::cout << "Finished reading OPTN" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading OPTN" << std::endl;
	std::cout << "Read " << total << " out of " << optnSize
                  << std::endl;
    }

    return total;
}

unsigned int eft::readIMPLDATA( std::istream &file )
{
    unsigned int impldataSize;
    std::string type;
    unsigned int total = readRecordHeader( file, type, impldataSize );
    if( type != "DATA" )
    {
        std::cout << "Expected record of type DATA: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found record " << type
	      << ": " << impldataSize << " bytes" 
	      << std::endl;

    // Skip data for now
    total += readUnknown( file, impldataSize );

    if( impldataSize == (total-8) )
    {
	std::cout << "Finished reading DATA" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading DATA" << std::endl;
	std::cout << "Read " << total << " out of " << impldataSize
                  << std::endl;
    }

    return total;
}

unsigned int eft::readPASS( std::istream &file )
{
    unsigned int passSize;
    unsigned int total = readFormHeader( file, "PASS", passSize );
    passSize += 8;
    std::cout << "Found FORM PASS: " << passSize-12 << " bytes"
	      << std::endl;

    unsigned int size;
    std::string form, type;
    total += readFormHeader( file, form, size, type );
    if( form != "FORM" )
    {
        std::cout << "Expected FORM not: " << form << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << form << " " << type
	      << ": " << size-4 << " bytes"
	      << std::endl;

    total += readRecordHeader( file, type, size );
    if( type != "DATA" )
    {
        std::cout << "Expected record of type DATA: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found record " << type
	      << ": " << size << " bytes" 
	      << std::endl;

    total += readUnknown( file, size );

    // Peek at next record, but keep file at same place.
    peekHeader( file, form, size, type );

    if( form == "FORM" && type == "PVSH" )
    {
	total += readPVSH( file );
	total += readPPSH( file );
    }
    else if( form == "FORM" && type == "PFFP" )
    {
	total += readPFFP( file );
	total += readSTAG( file );
	if( total < passSize )
	{
	    total += readSTAG( file );
	}
    }
    else
    {
	std::cout << "Unexpected FORM: " << type << std::endl;
	throw std::exception();
    }

    if( passSize == total )
    {
	std::cout << "Finished reading PASS" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading PASS" << std::endl;
	std::cout << "Read " << total << " out of " << passSize
                  << std::endl;
    }

    return total;
}

unsigned int eft::readPVSH( std::istream &file )
{
    unsigned int pvshSize;
    unsigned int total = readFormHeader( file, "PVSH", pvshSize );
    pvshSize += 8;
    std::cout << "Found FORM PVSH (Vertex shader)"
	      << ": " << pvshSize-12 << " bytes"
	      << std::endl;

    unsigned int size;
    std::string type;
    total += readRecordHeader( file, type, size );
    if( type != "0000" )
    {
        std::cout << "Expected record of type 0000: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found record " << type
	      << ": " << size << " bytes"
	      << std::endl;

    std::string vertexProgramName;
    total += base::read( file, vertexProgramName );
    std::cout << "Vertex program: " << vertexProgramName << std::endl;

    if( pvshSize == total )
    {
	std::cout << "Finished reading PVSH" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading PVSH" << std::endl;
	std::cout << "Read " << total << " out of " << pvshSize
                  << std::endl;
    }

    return total;
}

unsigned int eft::readPFFP( std::istream &file )
{
    unsigned int pffpSize;
    unsigned int total = readFormHeader( file, "PFFP", pffpSize );
    pffpSize += 8;
    std::cout << "Found FORM PFFP (Fixed Function Pipeline)"
	      << ": " << pffpSize-12 << " bytes"
	      << std::endl;

    unsigned int size;
    std::string type;
    total += readRecordHeader( file, type, size );
    if( type != "0001" )
    {
        std::cout << "Expected record of type 0001: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found record " << type
	      << ": " << size << " bytes"
	      << std::endl;

    total += readUnknown( file, size );

    if( pffpSize == total )
    {
	std::cout << "Finished reading PFFP" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading PFFP" << std::endl;
	std::cout << "Read " << total << " out of " << pffpSize
                  << std::endl;
    }

    return total;
}

unsigned int eft::readSTAG( std::istream &file )
{
    unsigned int stagSize;
    unsigned int total = readFormHeader( file, "STAG", stagSize );
    stagSize += 8;
    std::cout << "Found FORM STAG: " << stagSize-12 << " bytes"
	      << std::endl;

    unsigned int size;
    std::string type;
    total += readRecordHeader( file, type, size );
    if( type != "0000" )
    {
        std::cout << "Expected record of type 0000: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found record " << type
	      << ": " << size << " bytes"
	      << std::endl;

    // Skip data for now
    total += readUnknown( file, size );

    if( stagSize == total )
    {
	std::cout << "Finished reading STAG" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading STAG" << std::endl;
	std::cout << "Read " << total << " out of " << stagSize
                  << std::endl;
    }

    return total;
}

unsigned int eft::readPPSH( std::istream &file )
{
    unsigned int ppshSize;
    unsigned int total = readFormHeader( file, "PPSH", ppshSize );
    ppshSize += 8;
    std::cout << "Found FORM PPSH (Pixel shader)"
	      << ": " << ppshSize-12 << " bytes"
	      << std::endl;

    unsigned int size;
    std::string form, type;
    total += readFormHeader( file, form, size, type );
    if( form != "FORM" )
    {
        std::cout << "Expected FORM not: " << form << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << form << " " << type
	      << ": " << size-4 << " bytes"
	      << std::endl;

    total += readRecordHeader( file, type, size );
    if( type != "DATA" )
    {
        std::cout << "Expected record of type DATA: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found record " << type
	      << ": " << size << " bytes" 
	      << std::endl;

    std::string pixelShaderName;
    unsigned char num;
    total += base::read( file, num );
    total += base::read( file, pixelShaderName );
    std::cout << "Number of texture arguments to pixel shader: "
	      << (unsigned int)num << std::endl;
    std::cout << "Pixel shader: " << pixelShaderName << std::endl;;

    while( total < ppshSize )
    {
	total += readPTXM( file );
    }

    if( ppshSize == total )
    {
	std::cout << "Finished reading PPSH" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading PPSH" << std::endl;
	std::cout << "Read " << total << " out of " << ppshSize
                  << std::endl;
    }

    return total;
}

unsigned int eft::readPTXM( std::istream &file )
{
    unsigned int ptxmSize;
    unsigned int total = readFormHeader( file, "PTXM", ptxmSize );
    ptxmSize += 8;
    std::cout << "Found FORM PTXM: " << ptxmSize-12 << " bytes"
	      << std::endl;

    unsigned int size;
    std::string type;
    total += readRecordHeader( file, type, size );
#if 0
    if( type != "0002" )
    {
        std::cout << "Expected record of type 0002: " << type << std::endl;
        throw std::exception();
    }
#endif
    std::cout << "Found record " << type
	      << ": " << size << " bytes"
	      << std::endl;

    std::string name;
    unsigned char num;
    total += base::read( file, num );
#if 1
    file.width( size - sizeof( unsigned char ) );
    file >> name;
    total += size;
#else
    total += base::read( file, name );
#endif
    std::cout << "Pixel shader texture " << (unsigned int)num
	      << ": " << name << std::endl;

    if( ptxmSize == total )
    {
	std::cout << "Finished reading PTXM" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading PTXM" << std::endl;
	std::cout << "Read " << total << " out of " << ptxmSize
                  << std::endl;
    }

    return total;
}

