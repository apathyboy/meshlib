/** -*-c++-*-
 *  \class  swts
 *  \file   swts.cpp
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
#include <meshLib/swts.hpp>

#include <iostream>
#include <cstdlib>

using namespace ml;

swts::swts()
{
}

swts::~swts()
{
}

unsigned int swts::readSWTS( std::istream &file, std::string path )
{
  basePath = path;
  unsigned int swtsSize;
  std::string type;

  unsigned int total = readFormHeader( file, "SWTS", swtsSize );
  swtsSize += 8;
  std::cout << "Found SWTS form" << std::endl;

  unsigned int size;
  std::string form;
  total += readFormHeader( file, form, size, type );
  if( form != "FORM" )
    {
      std::cout << "Expected FORM: " << form << std::endl;
      exit( 0 );
    }
  std::cout << "Found " << form << " " << type << std::endl;

  while( total < swtsSize )
    {
      // Peek at next record, but keep file at same place.
      peekHeader( file, form, size, type );

      if( form == "FORM" )
	{
	  if( type == "DTST" )
	    {
	      total += readDTST( file );
	    }
	  else if( type == "DRTS" )
	    {
	      total += readDRTS( file );
	    }
	  else
	    {
	      std::cout << "Unexpected form: " << type << std::endl;
	      exit( 0 );
	    }
	}
      else if( form == "TEXT" )
	{
	  total += readTEXT( file );
	}
      else if( form == "NAME" )
	{
	  total += readNAME( file );
	}
      else
	{
	  std::cout << "Unexpected record: " << form << std::endl;
	  exit( 0 );
	}
    }

  if( swtsSize == total )
    {
      std::cout << "Finished reading SWTS" << std::endl;
    }
  else
    {
      std::cout << "FAILED in reading SWTS" << std::endl;
      std::cout << "Read " << total << " out of " << swtsSize
		<< std::endl;
    }

  return total;
}

unsigned int swts::readDTST( std::istream &file )
{
    unsigned int dtstSize;
    std::string type;

    unsigned int total = readFormHeader( file, "DTST", dtstSize );
    dtstSize += 8; // Add size of FORM and size fields.
    std::cout << "Found FORM " << type << std::endl;

    unsigned int size;
    total += readRecordHeader( file, type, size );
    if( type != "0000" )
    {
        std::cout << "Expected record of type 0000: " << type << std::endl;
        exit( 0 );
    }
    std::cout << "Found " << type << std::endl;
    
    if( size !=8 )
      {
	std::cout << "Expected size of 8: " << size << std::endl;
      }

    unsigned int x;
    total += base::read( file, x );
    std::cout << x << std::endl;

    float y;
    total += base::read( file, y );
    std::cout << y << std::endl;

    if( dtstSize == total )
    {
        std::cout << "Finished reading DTST" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading DTST" << std::endl;
        std::cout << "Read " << total << " out of " << dtstSize
                  << std::endl;
    }

    return total;
}

unsigned int swts::readDRTS( std::istream &file )
{
    unsigned int dtstSize;
    std::string type;

    unsigned int total = readFormHeader( file, "DRTS", dtstSize );
    dtstSize += 8; // Add size of FORM and size fields.
    std::cout << "Found FORM " << type << std::endl;

    unsigned int size;
    total += readRecordHeader( file, type, size );
    if( type != "0000" )
    {
        std::cout << "Expected record of type 0000: " << type << std::endl;
        exit( 0 );
    }
    std::cout << "Found " << type << std::endl;
    
    if( size != 12 )
      {
	std::cout << "Expected size of 12: " << size << std::endl;
      }

    unsigned int x;
    total += base::read( file, x );
    std::cout << x << std::endl;

    float y;
    total += base::read( file, y );
    std::cout << y << std::endl;

    float z;
    total += base::read( file, z );
    std::cout << z << std::endl;

    if( dtstSize == total )
    {
        std::cout << "Finished reading DRTS" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading DRTS" << std::endl;
        std::cout << "Read " << total << " out of " << dtstSize
                  << std::endl;
    }

    return total;
}

unsigned int swts::readNAME( std::istream &file )
{
    unsigned int nameSize;
    std::string type;

    unsigned int total = readRecordHeader( file, type, nameSize );
    nameSize += 8;
    if( type != "NAME" )
    {
        std::cout << "Expected record of type NAME: " << type << std::endl;
        exit( 0 );
    }
    std::cout << "Found " << type << std::endl;
    
    total += base::read( file, shaderFilename );

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

unsigned int swts::readTEXT( std::istream &file )
{
    unsigned int textSize;
    std::string type;

    unsigned int total = readRecordHeader( file, type, textSize );
    textSize += 8;
    if( type != "TEXT" )
    {
        std::cout << "Expected record of type TEXT: " << type << std::endl;
        exit( 0 );
    }
    std::cout << "Found " << type << std::endl;
    
    char temp[255];
    file.read( temp, 4 );
    total += 4;
    temp[4] = 0;
    textureTagList.push_back( std::string( temp ) );

    std::string textName( temp );
    total += base::read( file, textName );
    textureList.push_back( textName );

    if( textSize == total )
    {
        std::cout << "Finished reading TEXT" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading TEXT" << std::endl;
        std::cout << "Read " << total << " out of " << textSize
                  << std::endl;
    }

    return total;
}

void swts::print() const
{
  for( unsigned int i = 0; i < textureList.size(); ++i )
    {
      std::cout << i << ": " << textureList[i] << std::endl;
    }
}

bool swts::getTextureInfo( const unsigned int &index,
			   std::string &textureFilename,
			   std::string &textureTag ) const
{
  if( index >= getNumTextures() )
    {
      return false;
    }

  textureFilename = textureList[index];
  textureTag = textureTagList[index];

  return true;
}

