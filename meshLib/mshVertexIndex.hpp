/** -*-c++-*-
 *  \class  mshVertexIndex
 *  \file   mshVertexIndex.hpp
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

#include <fstream>
#include <iostream>
#include <string>

#ifndef MSHVERTEXINDEX_HPP
#define MSHVERTEXINDEX_HPP

namespace ml
{
  class mshVertexIndex
  {
  public:
    mshVertexIndex( unsigned int bpi );
    virtual ~mshVertexIndex();

    unsigned char getBytesPerIndex() const
    {
      return bytesPerIndex;
    }

    bool read( std::istream &file, unsigned int numIndices );

    void clear();
  
    unsigned int getNumIndices() const
    {
      return numIndex;
    }

    unsigned int getDataIndex() const
    {
      return dataIndex;
    }

    void setDataIndex( const unsigned int di )
    {
      dataIndex = di;
    }

    unsigned int getIndex( unsigned int indexNum )
    {
      if( NULL != indexI )
	{
	  return indexI[indexNum];
	}
      else if( NULL != indexS )
	{
	  return static_cast<unsigned int>( indexS[indexNum] );
	}
      else
	{
	  std::cerr << "No index data found" << std::endl;
	  return 0;
	}
    }

    void setShaderIndex( unsigned int index )
    {
      shaderIndex = index;
    }

    unsigned int getShaderIndex() const
    {
      return shaderIndex;
    }

    void print() const;

  protected:
    unsigned int bytesPerIndex;
    unsigned int numIndex;
    unsigned int dataIndex;
    unsigned int shaderIndex;

    unsigned int *indexI;
    unsigned short *indexS;

  private:

  };
}
#endif
