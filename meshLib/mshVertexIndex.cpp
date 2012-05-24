/** -*-c++-*-
 *  \class  mshVertexIndex
 *  \file   mshVertexIndex.cpp
 *  \author Kenneth R. Sewell III

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

#include <meshLib/mshVertexIndex.hpp>
#include <iostream>

using namespace ml;

mshVertexIndex::mshVertexIndex( unsigned int bpi )
  :bytesPerIndex( bpi ),
   numIndex( 0 ),
   indexI( NULL ),
   indexS( NULL )
{
}

mshVertexIndex::~mshVertexIndex()
{
  this->clear();
}

void mshVertexIndex::clear()
{
  if( NULL != indexS )
    {
      delete[] indexS;
      indexS = NULL;
    }

  if( NULL != indexI )
    {
      delete[] indexI;
      indexI = NULL;
    }
}

void mshVertexIndex::print() const
{
  if( NULL != indexI )
    {
      for( unsigned int i = 0; i < numIndex; ++i )
	{
	  std::cout << indexI[i] << " ";
	  if( ( ( i+1 ) % 3 ) == 0 )
	    {
	      std::cout << std::endl;
	    }
	}
    }
  else if( NULL != indexS )
    {
      for( unsigned int i = 0; i < numIndex; ++i )
	{
	  std::cout << indexS[i] << " ";
	  if( ( ( i+1 ) % 3 ) == 0 )
	    {
	      std::cout << std::endl;
	    }
	}
    }
  else
    {
      std::cerr << bytesPerIndex << " bytes per index is not supported"
		<< std::endl;
    }

}

bool mshVertexIndex::read( std::istream &file, unsigned int numIndices )
{
  if( 0 == bytesPerIndex )
    {
      std::cerr << "Bytes per vertex needs set first." << std::endl;
      return false;
    }

  if( ( 4 != bytesPerIndex ) && ( 2 != bytesPerIndex ) )
    {
      std::cerr << "Indices must be 2 or 4 byte values" << std::endl;
      return false;
    }

  this->clear();

  std::cout << "Reading " << bytesPerIndex*numIndices << " indices" 
	    << std::endl;
  if( 2 == bytesPerIndex ) 
    {
      indexS = new unsigned short[numIndices];
      file.read( (char *)indexS, bytesPerIndex*numIndices );
    }
  else 
    {
      indexI = new unsigned int[numIndices];
      file.read( (char *)indexI, bytesPerIndex*numIndices );
    }

  numIndex = numIndices;

  return true;
}

