/** -*-c++-*-
 *  \class  mshVertexData
 *  \file   mshVertexData.hpp
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

#include <meshLib/mshVertex.hpp>

#include <fstream>
#include <string>
#include <vector>

#ifndef MSHVERTEXDATA_HPP
#define MSHVERTEXDATA_HPP

namespace ml
{
  class mshVertexData
  {
  public:
    mshVertexData();
    virtual ~mshVertexData();

    unsigned char getBytesPerVertex() const
    {
      return bytesPerVertex;
    }

    void setBytesPerVertex( const unsigned char bpv )
    {
      bytesPerVertex = bpv;
    }

    bool read( std::istream &file, unsigned int numVerts );

    void clear();
  
    static bool isSupportedSize( const unsigned int bpv )
    {
      return mshVertex::isSupportedSize( bpv );
    }

    unsigned int getNumVertices() const
    {
      return v.size();
    }

    const mshVertex *getVertex( unsigned int vertexNum ) const;

    void print() const;

  protected:
    unsigned int bytesPerVertex;

    std::vector<mshVertex *> v;

  private:

  };
}
#endif
