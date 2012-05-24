/** -*-c++-*-
 *  \class  mshVertexData
 *  \file   mshVertexData.cpp
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

#include <meshLib/mshVertexData.hpp>
#include <iostream>

using namespace ml;

mshVertexData::mshVertexData()
  :bytesPerVertex( 0 )
{
}

mshVertexData::~mshVertexData()
{
  this->clear();
}

void mshVertexData::clear()
{
  while( !v.empty() )
    {
      delete v.back();
      v.pop_back();
    }
}

void mshVertexData::print() const
{
  for( std::vector<mshVertex *>::const_iterator i = v.begin();
       i != v.end();
       ++i
       )
    {
      (*i)->print();
    }
}

bool mshVertexData::read( std::istream &file, unsigned int numVerts )
{
  if( 0 == bytesPerVertex )
    {
      std::cerr << "Bytes per vertex needs set first." << std::endl;
      return false;
    }

  for( unsigned int i = 0; i < numVerts; ++i )
    {
      mshVertex *vertex = new mshVertex( bytesPerVertex );
      if( !vertex->read( file ) )
	{
	  delete vertex;
	  return false;
	}
      v.push_back( vertex );
    }

  //this->print();

  return true;
}

const mshVertex *mshVertexData::getVertex( unsigned int vertexNum ) const
{
  return v[vertexNum];
}
