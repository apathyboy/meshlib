/** -*-c++-*-
 *  \class  peft
 *  \file   peft.cpp
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
#include <meshLib/peft.hpp>

#include <iostream>
#include <bitset>
#include <cstdlib>

using namespace ml;

peft::peft()
{
}

peft::~peft()
{
}

unsigned int peft::readPEFT( std::istream &file, std::string path )
{
  basePath = path;
  unsigned int peftSize;
  unsigned int total = readFormHeader( file, "PEFT", peftSize );
  peftSize += 8;
  std::cout << "Found PEFT form"
	    << ": " << peftSize-12 << " bytes"
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

  total += readPTIM( file );
  unsigned int numEmitterGroups;
  total += read0000( file, numEmitterGroups );

  std::cout << "Num emitters: " << numEmitterGroups << std::endl;

  for( unsigned int i = 0; i < numEmitterGroups; ++i )
    {
      total += readEMGP( file );
    }

  if( peftSize == total )
    {
      std::cout << "Finished reading EFCT" << std::endl;
    }
  else
    {
      std::cout << "FAILED in reading EFCT" << std::endl;
      std::cout << "Read " << total << " out of " << peftSize
		<< std::endl;
    }
    
  return total;
}


unsigned int peft::readEMGP( std::istream &file )
{
    unsigned int emgpSize;
    unsigned int total = readFormHeader( file, "EMGP", emgpSize );
    emgpSize += 8;
    std::cout << "Found FORM EMGP: " << emgpSize-12 << " bytes"
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

    total += readPTIM( file );
    unsigned int numEmitters;
    total += read0000( file, numEmitters );
    for( unsigned int i = 0; i < numEmitters; ++i )
      {
	total += readEMTR( file );
      }

    if( emgpSize == total )
    {
	std::cout << "Finished reading EMGP" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading EMGP" << std::endl;
	std::cout << "Read " << total << " out of " << emgpSize
                  << std::endl;
    }

    return total;
}

unsigned int peft::readEMTR( std::istream &file )
{
    unsigned int emtrSize;
    unsigned int total = readFormHeader( file, "EMTR", emtrSize );
    emtrSize += 8;
    std::cout << "Found FORM EMTR: " << emtrSize-12 << " bytes"
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

    total += readPTIM( file );
    total += readWVFM( file );
    total += readWVFM( file );
    total += readWVFM( file );
    total += readWVFM( file );
    total += readWVFM( file );
    total += readWVFM( file );
    total += readWVFM( file );
    total += readWVFM( file );
    total += readWVFM( file );
    total += readWVFM( file );
    total += readWVFM( file );
    total += readWVFM( file );
    total += readWVFM( file );
    total += readWVFM( file );
    total += readWVFM( file );
    total += readWVFM( file );
    total += readEMTR0000( file );
    total += readPTQD( file );

    total += readUnknown( file, emtrSize - total );

    if( emtrSize == total )
    {
	std::cout << "Finished reading EMTR" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading EMTR" << std::endl;
	std::cout << "Read " << total << " out of " << emtrSize
                  << std::endl;
    }

    return total;
}

unsigned int peft::readPTIM( std::istream &file )
{
    unsigned int ptimSize;
    unsigned int total = readFormHeader( file, "PTIM", ptimSize );
    ptimSize += 8;
    std::cout << "Found FORM PTIM: " << ptimSize-12 << " bytes"
	      << std::endl;

    unsigned int size;
    std::string type;
    total += readRecordHeader( file, type, size );
    if( type != "0001" )
    {
        std::cout << "Expected record of type 0001: " << type << std::endl;
        exit( 0 );
    }
    std::cout << "Found record " << type
	      << ": " << size << " bytes"
	      << std::endl;

    int x;
    for( unsigned int i = 0; i < 6; ++i )
      {
	total += base::read( file, x );
	std::cout << x << std::endl;
      }

    if( ptimSize == total )
    {
	std::cout << "Finished reading PTIM" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading PTIM" << std::endl;
	std::cout << "Read " << total << " out of " << ptimSize
                  << std::endl;
    }

    return total;
}

unsigned int peft::readWVFM( std::istream &file )
{
    unsigned int wvfmSize;
    unsigned int total = readFormHeader( file, "WVFM", wvfmSize );
    wvfmSize += 8;
    std::cout << "Found FORM WVFM: " << wvfmSize-12 << " bytes"
	      << std::endl;

    unsigned int size;
    std::string type;
    total += readRecordHeader( file, type, size );
    if( type != "0001" )
    {
        std::cout << "Expected record of type 0001: " << type << std::endl;
        exit( 0 );
    }
    std::cout << "Found record " << type
	      << ": " << size << " bytes"
	      << std::endl;
    
    int u1;

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    unsigned int num;
    total += base::read( file, num );
    std::cout << "Num: " << num << std::endl;

    float u2;
    std::cout << std::fixed;
    for( unsigned int i = 0; i < num; ++i )
      {
	total += base::read( file, u2 );
	std::cout << u2 << " ";

	total += base::read( file, u2 );
	std::cout << u2 << " ";
	
	total += base::read( file, u2 );
	std::cout << u2 << " ";
	
	total += base::read( file, u2 );
	std::cout << u2 << std::endl;
      }

    if( wvfmSize == total )
    {
	std::cout << "Finished reading WVFM" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading WVFM" << std::endl;
	std::cout << "Read " << total << " out of " << wvfmSize
                  << std::endl;
    }

    return total;
}

unsigned int peft::readPTQD( std::istream &file )
{
    unsigned int ptqdSize;
    unsigned int total = readFormHeader( file, "PTQD", ptqdSize );
    ptqdSize += 8;
    std::cout << "Found FORM PTQD: " << ptqdSize-12 << " bytes"
	      << std::endl;
    
    total += readPTCL( file );

    unsigned int size;
    total += readFormHeader( file, "0001", size );
    size += 8;
    std::cout << "Found FORM 0001: " << size-12 << " bytes"
	      << std::endl;

    total += readWVFM( file );
    total += readWVFM( file );
    total += readWVFM( file );
    total += readPTEX( file );
    
    std::string type;
    total += readRecordHeader( file, type, size );
    size += 8;
    if( type != "0000" )
      {
        std::cout << "Expected record of type 0000: " << type << std::endl;
        exit( 0 );
      }
    std::cout << "Found record " << type
	      << ": " << size << " bytes" 
	      << std::endl;

    char u3;
    total += base::read( file, u3 );
    std::cout << (int)u3 << std::endl;

    if( ptqdSize == total )
    {
	std::cout << "Finished reading PTQD" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading PTQD" << std::endl;
	std::cout << "Read " << total << " out of " << ptqdSize
                  << std::endl;
    }

    return total;
}

unsigned int peft::readPTEX( std::istream &file )
{
    unsigned int ptexSize;
    unsigned int total = readFormHeader( file, "PTEX", ptexSize );
    ptexSize += 8;
    std::cout << "Found FORM PTEX: " << ptexSize-12 << " bytes"
	      << std::endl;

    std::string type;
    unsigned int size;
    total += readRecordHeader( file, type, size );
    size += 8;
    if( type != "0000" )
      {
        std::cout << "Expected record of type 0000: " << type << std::endl;
        exit( 0 );
      }
    std::cout << "Found record " << type
	      << ": " << size << " bytes" 
	      << std::endl;
    
    std::string name;
    total += base::read( file, name );
    std::cout << name << std::endl;

    float u2;
    total += base::read( file, u2 );
    std::cout << u2 << std::endl;

    total += base::read( file, u2 );
    std::cout << u2 << std::endl;

    total += base::read( file, u2 );
    std::cout << u2 << std::endl;

    total += base::read( file, u2 );
    std::cout << u2 << std::endl;

    total += base::read( file, u2 );
    std::cout << u2 << std::endl;

    total += base::read( file, u2 );
    std::cout << u2 << std::endl;

    char u3;
    total += base::read( file, u3 );
    std::cout << (int)u3 << std::endl;

    if( ptexSize == total )
    {
	std::cout << "Finished reading PTEX" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading PTEX" << std::endl;
	std::cout << "Read " << total << " out of " << ptexSize
                  << std::endl;
    }

    return total;
}

unsigned int peft::readPTCL( std::istream &file )
{
    unsigned int ptclSize;
    unsigned int total = readFormHeader( file, "PTCL", ptclSize );
    ptclSize += 8;
    std::cout << "Found FORM PTCL: " << ptclSize-12 << " bytes"
	      << std::endl;
    
    unsigned int size;
    total += readFormHeader( file, "0002", size );
    size += 8;
    std::cout << "Found FORM 0002: " << size-12 << " bytes"
	      << std::endl;

    std::string type;
    total += readRecordHeader( file, type, size );
    size += 8;
    if( type != "0000" )
      {
        std::cout << "Expected record of type 0000: " << type << std::endl;
        exit( 0 );
      }
    std::cout << "Found record " << type
	      << ": " << size << " bytes" 
	      << std::endl;

    std::string name;
    total += base::read( file, name );
    std::cout << name << std::endl;

    unsigned int u1;
    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    unsigned char u2;
    total += base::read( file, u2 );
    std::cout << (int)u2 << std::endl;

    total += readCLRR( file );
    total += readWVFM( file );
    total += readWVFM( file );

    total += readUnknown( file, ptclSize-total );

    if( ptclSize == total )
    {
	std::cout << "Finished reading PTCL" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading PTCL" << std::endl;
	std::cout << "Read " << total << " out of " << ptclSize
                  << std::endl;
    }

    return total;
}

unsigned int peft::readCLRR( std::istream &file )
{
    unsigned int clrrSize;
    unsigned int total = readFormHeader( file, "CLRR", clrrSize );
    clrrSize += 8;
    std::cout << "Found FORM CLRR: " << clrrSize-12 << " bytes"
	      << std::endl;
    
    float u1;
    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    if( clrrSize == total )
    {
	std::cout << "Finished reading CLRR" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading CLRR" << std::endl;
	std::cout << "Read " << total << " out of " << clrrSize
                  << std::endl;
    }

    return total;
}


unsigned int peft::read0000( std::istream &file, unsigned int &num )
{
    unsigned int size;
    std::string type;
    unsigned int total = readRecordHeader( file, type, size );
    size += 8;
    if( type != "0000" )
    {
        std::cout << "Expected record of type 0000: " << type << std::endl;
        exit( 0 );
    }
    std::cout << "Found record " << type
	      << ": " << size << " bytes" 
	      << std::endl;

    total += base::read( file, num );

    if( size == total )
    {
	std::cout << "Finished reading 0000" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading 0000" << std::endl;
	std::cout << "Read " << total << " out of " << size
                  << std::endl;
    }

    return total;
}

unsigned int peft::readEMTR0000( std::istream &file )
{
    unsigned int size;
    std::string type;
    unsigned int total = readRecordHeader( file, type, size );
    size += 8;
    if( type != "0000" )
    {
        std::cout << "Expected record of type 0000: " << type << std::endl;
        exit( 0 );
    }
    std::cout << "Found record " << type
	      << ": " << size << " bytes" 
	      << std::endl;

    std::string name;
    total += base::read( file, name );
    std::cout << name << std::endl;

    int u1;
    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    float u2;
    total += base::read( file, u2 );
    std::cout << u2 << std::endl;

    total += base::read( file, u2 );
    std::cout << u2 << std::endl;

    short u3;
    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u3 );
    std::cout << u3 << std::endl;

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    total += readUnknown( file, size - total) ;

    if( size == total )
    {
	std::cout << "Finished reading 0000" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading 0000" << std::endl;
	std::cout << "Read " << total << " out of " << size
                  << std::endl;
    }

    return total;
}


