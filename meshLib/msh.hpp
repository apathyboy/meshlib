/** -*-c++-*-
 *  \class  msh
 *  \file   msh.hpp
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
#include <meshLib/model.hpp>
#include <meshLib/cshd.hpp>
#include <meshLib/sht.hpp>
#include <meshLib/mshVertexData.hpp>
#include <meshLib/mshVertexIndex.hpp>

#include <fstream>
#include <string>
#include <vector>

#ifndef MSH_HPP
#define MSH_HPP

namespace ml
{
  enum maxTextures {
    MAX_TEXTURES = 8
  };

  class msh : public model
  {
  public:
    msh();
    ~msh();
    bool isRightType( std::istream &file )
    {
      return isOfType( file, "MESH" );
    }
    unsigned int readMSH( std::istream &file, std::string path="" );

    unsigned int getNumIndexTables() const
    {
      return indexData.size();
    }

    unsigned int getNumVertexSets() const
    {
      return vertexData.size();
    }

    unsigned int getBytesPerVertex( const unsigned int &index ) const
    {
      return vertexData[index]->getBytesPerVertex();
    }

    bool getIndex(
		  unsigned int indexNum,
		  mshVertexData **vData,
		  mshVertexIndex **iData,
		  std::string &shaderFilename
		  );
    bool getMeshIndex( unsigned int indexNum,
		       unsigned int &dataSet,
		       mshVertexIndex **iData
		       );
    
    bool getIndex(
		  unsigned int indexNum,
		  mshVertexData **vData,
		  std::string &shaderFilename
		  );
  
    unsigned int getNumShaders() const
    {
      return shaderList.size();
    }

    std::string getShader( unsigned int index ) const
    {
      if( index < shaderList.size() )
	{
	  return shaderList[index];
	}
      else
	{
	  return std::string("");
	}
    }

    void getBoundingSphere( float &centerX, float &centerY, float &centerZ,
			    float &Radius )
    {
      centerX = cx;
      centerY = cy;
      centerZ = cz;
      Radius = radius;
    }

    void getBoundingBox( float &X1, float &Y1, float &Z1,
			 float &X2, float &Y2, float &Z2 )
    {
      X1 = x1;
      Y1 = y1;
      Z1 = z1;
      X2 = x2;
      Y2 = y2;
      Z2 = z2;
    }

  protected:
    unsigned int readD3DFVF( std::istream &file,
			     unsigned int &codes,
			     unsigned int &numTextures );
  
    unsigned int readSPS( std::istream &file );
    unsigned int readGeode( std::istream &file,
			    const unsigned int nodeNumber );
    unsigned int readGeometry( std::istream &file );
  
    unsigned int readGeometryDATA( std::istream &file,
				   unsigned int numVerts );
    unsigned int readGeometryINDX( std::istream &file, 
				   unsigned int &bytesPerIndex );
    unsigned int readGeometrySIDX( std::istream &file,
				   unsigned int bytesPerIndex );
  private:
    std::vector<bool> isSHT;
    std::vector<std::string> shaderList;

    std::vector<mshVertexData *> vertexData;
    std::vector<mshVertexIndex *> indexData;

    // Bounding sphere center and radius
    float cx, cy, cz, radius;

    // 2 xyz points defining bounding box
    float x1, y1, z1;
    float x2, y2, z2;

  };
}
#endif
