/** -*-c++-*-
 *  \class  ws
 *  \file   ws.hpp
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

#include <meshLib/base.hpp>

#include <fstream>
#include <vector>
#include <list>
#include <string>

#ifndef WS_HPP
#define WS_HPP

namespace ml
{
  class wsNode
  {
  public:
    std::string getObjectFilename() const
    {
      return objectFilename;
    }

    float getX() const
    {
      return x;
    }

    float getY() const
    {
      return y;
    }

    float getZ() const
    {
      return z;
    }

    float getQuatX() const
    {
      return qx;
    }

    float getQuatY() const
    {
      return qy;
    }

    float getQuatZ() const
    {
      return qz;
    }

    float getQuatW() const
    {
      return qw;
    }

    unsigned int getID() const
    {
      return nodeID;
    }

    unsigned int getParentID() const
    {
      return parentNodeID;
    }

    unsigned int getObjectIndex() const
    {
      return objectIndex;
    }

    unsigned int getPositionInParent() const
    {
      return positionInParent;
    }

    //protected:
  
    unsigned int read( std::istream &file );
    unsigned int write( std::ofstream &file );
    void print();
  
    unsigned int nodeID;
    unsigned int parentNodeID;
    unsigned int objectIndex;
    unsigned int positionInParent;
  
    float qx;
    float qy;
    float qz;
    float qw;
  
    float x;
    float y;
    float z;
  
    unsigned int u2;
  
    unsigned int crc;
  
    std::string objectFilename;
  
    // Not stored in record, readSWG use only
    unsigned int level;
  };

  class ws : public base
  {
  public:
    ws();
    ~ws();
    bool isRightType( std::istream &file )
    {
      return isOfType( file, "WSNP" );
    }
    unsigned int readWS( std::istream &file );
    unsigned int readMetaFile( std::istream &infile );
    unsigned int createWS( std::ofstream &outfile );
    bool canWrite() const { return true; }

    unsigned int getNumObjectNodes() const
    {
      return nodes.size();
    }

    wsNode &getObjectNode( unsigned int i );

  protected:
    unsigned int readNODS( std::istream &file );
    unsigned int readNODE( std::istream &file, unsigned int level );
    unsigned int readOTNL( std::istream &file );
	
    unsigned int writeNODS( std::ofstream &outfile );
    unsigned int writeNODE( std::ofstream &outfile );
    unsigned int writeOTNL( std::ofstream &outfile );
	
    std::vector< wsNode > nodes;
    std::vector< std::string > objectNames;
  private:
    std::vector< wsNode >::iterator currentNode;
    unsigned int maxObjectIndex;
  };
}
#endif
