/** -*-c++-*-
 *  \class  lod
 *  \file   lod.cpp
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

#include <meshLib/lod.hpp>
#include <meshLib/msh.hpp>
#include <meshLib/cshd.hpp>
#include <meshLib/sht.hpp>

#include <iostream>
#include <bitset>
#include <cstdlib>

using namespace ml;

lod::lod()
  : x1( -1.0 ),
    y1( -1.0 ),
    z1( -1.0 ),
    x2(  1.0 ),
    y2(  1.0 ),
    z2(  1.0 )
{
}

lod::~lod()
{
}

bool lod::getChild( unsigned int index, 
		    std::string &filename,
		    float &Near, float &Far ) const
{
  if( index > getNumLODs()-1 )
    {
      return false;
    }

  Near = near[index];
  Far = far[index];
  filename = childFilename[index];

  return true;
}

unsigned int lod::readLOD( std::istream &file, std::string path )
{
  basePath = path;
  unsigned int dtlaSize;
  unsigned int total = readFormHeader( file, "DTLA", dtlaSize );
  dtlaSize += 8;
  std::cout << "Found DTLA form" << std::endl;

  unsigned int size;
#if 1
  std::string form, type;
  total += readFormHeader( file, form, size, type );
  if( form != "FORM" )
    {
      std::cout << "Expected Form " << std::endl;
      throw std::exception();
    }
  if( type != "0007" && type != "0006" && type != "0005")
    {
      std::cout << "Expected type 0005, 0006 or 0007: " << type << std::endl;
      throw std::exception();
    }
#else
  total += readFormHeader( file, "0000", size );
#endif
  std::cout << "Found form of type: " << type << std::endl;

  while( total < dtlaSize )
    {
      // Peek at next record, but keep file at same place.
      base::peekHeader( file, form, size, type );
	
      if( form == "FORM" )
	{
	  if( type == "APPR" )
	    {
	      total += model::readAPPR( file );
	    }
	  else if( type == "DATA" )
	    {
	      total += readChildren( file );
	    }
	  else if( type == "RADR" )
	    {
	      total += readRADR( file );
	    }
	  else if( type == "TEST" )
	    {
	      total += readTEST( file );
	    }
	  else if( type == "WRIT" )
	    {
	      total += readWRIT( file );
	    }
	  else
	    {
	      std::cout << "Unexpected FORM: " << type << std::endl;
	      throw std::exception();
	    }
	}
      else if( form == "PIVT" )
	{
	  total += readPIVT( file );
	}
      else if( form == "INFO" )
	{
	  total += readINFO( file );
	}
      else
	{
	  std::cout << "Unexpected record: " << form << std::endl;
	  throw std::exception();
	}
    }

  if( dtlaSize == total )
    {
      std::cout << "Finished reading DTLA" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading DTLA" << std::endl;
      std::cout << "Read " << total << " out of " << dtlaSize
		<< std::endl;
    }

  return total;
}

unsigned int lod::readPIVT( std::istream &file )
{
    unsigned int size;
    std::string type;

    unsigned int total = readRecordHeader( file, type, size );
    if( type != "PIVT" )
    {
	std::cout << "Expected record of type PIVT: " << type << std::endl;
	throw std::exception();
    }
    std::cout << "Found PIVT record" << std::endl;

    total += readUnknown( file, size );
    
    return total;
}

unsigned int lod::readINFO( std::istream &file )
{
    unsigned int size;
    std::string type;

    unsigned int total = readRecordHeader( file, type, size );
    if( type != "INFO" )
    {
	std::cout << "Expected record of type INFO: " << type << std::endl;
	throw std::exception();
    }
    std::cout << "Found INFO record" << std::endl;

    unsigned int num = size/12;

    for( unsigned int i=0; i < num; ++i )
    {
	unsigned int childNo;
	total += base::read( file, childNo );

	float n;
	total += base::read( file, n );
	near.push_back( n );

	float f;
	total += base::read( file, f );
	far.push_back( f );

	std::cout << childNo << ": "
		  << near[far.size()-1] << "..."
		  << far[far.size()-1]
		  << std::endl;
    }
    
    return total;
}

unsigned int lod::readCHLD( std::istream &file )
{
    unsigned int size;
    std::string type;

    unsigned int total = readRecordHeader( file, type, size );
    size += 8;
    if( type != "CHLD" )
    {
	std::cout << "Expected record of type CHLD: " << type << std::endl;
	throw std::exception();
    }
    std::cout << "Found CHLD record" << std::endl;

    unsigned int childNumber;
    total += base::read( file, childNumber );

    std::string tempFilename;
    total += base::read( file, tempFilename );

    // Some files already have appearance/ in them
    if( tempFilename.substr( 0, 11 ) != "appearance/" )
      {
	std::string filename = "appearance/";
	filename += tempFilename;
	std::cout << childNumber << ": " << filename << std::endl;
	childFilename.push_back( filename );
      }
    else
      {
	childFilename.push_back( tempFilename );
      }

    if( size == total )
    {
        std::cout << "Finished reading CHLD" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading CHLD" << std::endl;
        std::cout << "Read " << total << " out of " << size
                  << std::endl;
     }

    return total;
}

unsigned int lod::readChildren( std::istream &file )
{
    unsigned int size;
    unsigned int total = readFormHeader( file, "DATA", size );
    std::cout << "Found DATA form" << std::endl;

#if 0
    while( total < size-4 )
#else
      for( unsigned int i = 0; i < near.size(); ++i )
#endif
    {
	total += readCHLD( file );
    }

    return total;
}

unsigned int lod::readRADR( std::istream &file )
{
    unsigned int radrSize;
    unsigned int total = readFormHeader( file, "RADR", radrSize );
    radrSize += 8;
    std::cout << "Found RADR form" << std::endl;

    std::string type;
    unsigned int size;
    total += readRecordHeader( file, type, size );
    if( type != "INFO" )
    {
	std::cout << "Expected record of type INFO: " << type << std::endl;
	throw std::exception();
    }
    std::cout << "Found INFO record" << std::endl;

    unsigned int numNodes;
    total += base::read( file, numNodes );
    std::cout << "Num nodes: " << numNodes << std::endl;

    // Need to loop here and read IDTL (and others?)
    while( total < radrSize )
      {
	std::vector<vector3> vec;
	std::vector<unsigned int> index;
	total += model::readIDTL( file, vec, index );
      }

    if( radrSize == total )
    {
	std::cout << "Finished reading RADR" << std::endl;
    }
    else
    {
	std::cout << "Failed in reading RADR" << std::endl;
        std::cout << "Read " << total << " out of " << radrSize
                  << std::endl;
    }

    return total;
}

unsigned int lod::readTEST( std::istream &file )
{
    std::string form;
    unsigned int testSize;
    std::string type;

    unsigned int total = readFormHeader( file, "TEST", testSize );
    testSize += 8;
    std::cout << "Found TEST form" << std::endl;

    unsigned int size;
    total += readRecordHeader( file, type, size );
    if( type != "INFO" )
    {
	std::cout << "Expected record of type INFO: " << type << std::endl;
	throw std::exception();
    }
    std::cout << "Found INFO record" << std::endl;
    unsigned int numNodes;
    total += base::read( file, numNodes );
    std::cout << "Num nodes: " << numNodes << std::endl;

    // Need to loop here and read IDTL (and others?)
    while( total < testSize )
      {
	peekHeader( file, form, size, type );
	if( "FORM" == form )
	  {
	    if( "IDTL" == type )
	      {
		std::vector<vector3> vec;
		std::vector<unsigned int> index;
		total += model::readIDTL( file, vec, index );
	      }
	    else
	      {
		std::cout << "Expected Form of type IDTL: "
			  << type << std::endl;
		throw std::exception();
	      }
	  }
	else
	  {
	    std::cout << "Expected Form of type IDTL: "
		      << type << std::endl;
	    throw std::exception();
	  }
      }

    if( testSize == total )
    {
	std::cout << "Finished reading TEST" << std::endl;
    }
    else
    {
	std::cout << "Failed in reading TEST" << std::endl;
        std::cout << "Read " << total << " out of " << testSize
                  << std::endl;
    }

    return total;
}

unsigned int lod::readWRIT( std::istream &file )
{
    std::string form;
    unsigned int writSize;
    std::string type;

    unsigned int total = readFormHeader( file, "WRIT", writSize );
    writSize += 8;
    std::cout << "Found WRIT form" << std::endl;

    unsigned int size;
    total += readRecordHeader( file, type, size );
    if( type != "INFO" )
    {
	std::cout << "Expected record of type INFO: " << type << std::endl;
	throw std::exception();
    }
    std::cout << "Found INFO record" << std::endl;

    unsigned int numNodes;
    total += base::read( file, numNodes );

    std::cout << "Num nodes: " << numNodes << std::endl;

    while( total < writSize )
      {
	std::vector<vector3> vec;
	std::vector<unsigned int> index;
	total += model::readIDTL( file, vec, index );
      }

    if( writSize == total )
    {
	std::cout << "Finished reading WRIT" << std::endl;
    }
    else
    {
	std::cout << "Failed in reading WRIT" << std::endl;
        std::cout << "Read " << total << " out of " << writSize
                  << std::endl;
    }

    return total;
}

