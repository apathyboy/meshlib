/** -*-c++-*-
 *  \class  sd2d
 *  \file   sd2d.cpp
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
#include <meshLib/sd2d.hpp>

#include <iostream>
#include <cstdlib>

using namespace ml;

sd2d::sd2d()
{
}

sd2d::~sd2d()
{
}

unsigned int sd2d::readSD2D( std::istream &file )
{
    unsigned int sd2dSize;
    unsigned int total = readFormHeader( file, "SD2D", sd2dSize );
    sd2dSize += 8;
    std::cout << "Found SD2D form" << std::endl;

    total += read0003( file );
    
    if( sd2dSize == total )
    {
	std::cout << "Finished reading SD2D" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading SD2D" << std::endl;
	std::cout << "Read " << total << " out of " << sd2dSize
                  << std::endl;
     }

    return total;
}

unsigned int sd2d::read0003( std::istream &file )
{
    std::string type;
    unsigned int size;
    unsigned int total = readRecordHeader( file, type, size );
    size += 8;
    if( type != "0003" )
    {
        std::cout << "Expected record of type 0003: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    total += base::read( file, numSamples );
    std::cout << "Num samples: " << numSamples << std::endl;

    std::string sampleName;
    for( unsigned int i = 0; i < numSamples; ++i )
      {
	total += base::read( file, sampleName );
	base::fixSlash( sampleName );
	std::cout << "Sample: " << sampleName << std::endl;
	samples.push_back( sampleName );
      }

    unsigned char x;
    for( unsigned int i = 0; i < 28; ++i )
      {
	total += base::read( file, x );
	std::cout << (unsigned int)x << " ";

	total += base::read( file, x );
	std::cout << (unsigned int)x << " ";

	total += base::read( file, x );
	std::cout << (unsigned int)x << " ";

	total += base::read( file, x );
	std::cout << (unsigned int)x << std::endl;
      }
	
    if( size == total )
    {
        std::cout << "Finished reading 0003" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading 0003" << std::endl;
        std::cout << "Read " << total << " out of " << size
                  << std::endl;
     }

    return total;
}

bool sd2d::getSample( const unsigned int &index,
		      std::string &sampleName ) const
{
  if( index >= numSamples )
    {
      return false;
    }

  sampleName = samples[index];

  return true;
}

void sd2d::print() const
{
}

