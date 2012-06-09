/** -*-c++-*-
 *  \class  flor
 *  \file   flor.cpp
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

/**
   This class still needs work.
 */

#include <meshLib/base.hpp>
#include <meshLib/flor.hpp>

#include <iostream>
#include <cstdlib>

using namespace ml;

flor::flor()
{
}

flor::~flor()
{
}

unsigned int flor::readFLOR( std::istream &file )
{
    unsigned int florSize;
    std::string type;

    unsigned int total = readFormHeader( file, "FLOR", florSize );
    florSize += 8;
    std::cout << "Found FLOR form" << std::endl;

    unsigned int size;
    total += readFormHeader( file, "0006", size );
    size += 8;
    std::cout << "Found 0006 form" << std::endl;

    total += readVERT( file );
    total += readTRIS( file );

    total += base::readUnknown( file, size-total );
    total += base::readUnknown( file, florSize-total );
    
    if( total == florSize )
    {
	std::cout << "Finished reading FLOR." << std::endl;
    }
    else
    {
	std::cout << "Error reading FLOR!" << std::endl;
	std::cout << "Read " << total << " out of " << florSize
		  << std::endl;
    }
    
    return total;
}

unsigned int flor::readVERT( std::istream &file )
{
  unsigned int vertSize;
  std::string type;
  
  unsigned int total = readRecordHeader( file, type, vertSize );
  vertSize += 8;
  if( type != "VERT" )
    {
      std::cout << "Expected record of type VERT: " << type << std::endl;
      throw std::exception();
    }
  std::cout << "Found VERT record" << std::endl;

  unsigned int numVerts;
  total += read( file, numVerts );
  std::cout << "Number of vertices: " << numVerts << std::endl;

  vertex.resize( numVerts * 3 );
  unsigned int numBytes = numVerts * 3 * sizeof( float );
  file.read( (char *)&(vertex[0]), numBytes );
  total += numBytes;

  std::cout << std::fixed;
  for( unsigned int i = 0; i < numVerts; ++i )
    {
      std::cout << vertex[(i*3)] << ", "
		<< vertex[(i*3)+1] << ", "
		<< vertex[(i*3)+2] << std::endl;
    }

  if( vertSize == total )
    {
      std::cout << "Finished reading VERT" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading VERT" << std::endl;
      std::cout << "Read " << total << " out of " << vertSize
		<< std::endl;
    }
    
  return total;

}

unsigned int flor::readTRIS( std::istream &file )
{
  unsigned int trisSize;
  std::string type;
  
  unsigned int total = readRecordHeader( file, type, trisSize );
  trisSize += 8;
  if( type != "TRIS" )
    {
      std::cout << "Expected record of type TRIS: " << type << std::endl;
      throw std::exception();
    }
  std::cout << "Found TRIS record" << std::endl;
  std::cout << "Size: " << trisSize << std::endl;

  unsigned int numTris;
  total += read( file, numTris );
  std::cout << "Number of triangles: " << numTris << std::endl;

  for( unsigned int i = 0; i < numTris; ++i )
    {
      int u1;
      total += read( file, u1 );
      std::cout << u1 << std::endl;

      total += read( file, u1 );
      std::cout << u1 << std::endl;

      total += read( file, u1 );
      std::cout << u1 << std::endl;

      total += read( file, u1 );
      std::cout << u1 << std::endl;

      total += read( file, u1 );
      std::cout << u1 << std::endl;

      total += read( file, u1 );
      std::cout << u1 << std::endl;

      total += read( file, u1 );
      std::cout << u1 << std::endl;

      float u2;
      total += read( file, u2 );
      std::cout << u2 << std::endl;

      total += read( file, u2 );
      std::cout << u2 << std::endl;

      total += read( file, u2 );
      std::cout << u2 << std::endl;

      total += read( file, u2 );
      std::cout << u2 << std::endl;

      total += read( file, u1 );
      std::cout << u1 << std::endl;

      total += read( file, u1 );
      std::cout << u1 << std::endl;

      total += read( file, u1 );
      std::cout << u1 << std::endl;

      total += read( file, u1 );
      std::cout << u1 << std::endl;

      std::cout << std::endl;
    }

  if( trisSize == total )
    {
      std::cout << "Finished reading TRIS" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading TRIS" << std::endl;
      std::cout << "Read " << total << " out of " << trisSize
		<< std::endl;
    }
    
  return total;

}

