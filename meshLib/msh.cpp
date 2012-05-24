/** -*-c++-*-
 *  \class  msh
 *  \file   msh.cpp
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

#include <meshLib/msh.hpp>
#include <meshLib/cshd.hpp>
#include <meshLib/sht.hpp>

#include <iostream>
#include <bitset>
#include <cstdlib>

using namespace ml;

msh::msh()
{
}

msh::~msh()
{
  while( !vertexData.empty() )
    {
      delete vertexData.back();
      vertexData.pop_back();
    }

  while( !indexData.empty() )
    {
      delete indexData.back();
      indexData.pop_back();
    }
}

bool msh::getIndex( unsigned int indexNum,
		    mshVertexData **vData,
		    mshVertexIndex **iData,
		    std::string &shaderFilename
		    )
{
  if( indexNum > indexData.size() )
    {
      std::cout << "Index out of range" << std::endl;
      return false;
    }

  *iData = indexData[indexNum];

  *vData = vertexData[(*iData)->getDataIndex()];

  shaderFilename = shaderList[(*iData)->getDataIndex()];

  return true;
}

bool msh::getMeshIndex( unsigned int indexNum,
			unsigned int &dataSet,
			mshVertexIndex **iData
			)
{
  if( indexNum > indexData.size() )
    {
      std::cout << "Index out of range" << std::endl;
      return false;
    }

  *iData = indexData[indexNum];

  dataSet = (*iData)->getDataIndex();

  return true;
}

bool msh::getIndex( unsigned int indexNum,
		    mshVertexData **vData,
		    std::string &shaderFilename
		    )
{
  if( indexNum > indexData.size() )
    {
      std::cout << "Index out of range" << std::endl;
      return false;
    }

  *vData = vertexData[indexNum];
  shaderFilename = shaderList[indexNum];

  return true;
}

// Some of this works...  Needs more investigating
unsigned int msh::readD3DFVF(
    std::istream &file,
    unsigned int &codes,
    unsigned int &numTex
    )
{
#define D3DFVF_RESERVED0           0x0001
#define D3DFVF_POSITION_MASK       0x000E
#define D3DFVF_XYZ                 0x0002
#define D3DFVF_XYZRHW              0x0004
#define D3DFVF_XYZB1               0x0006
#define D3DFVF_XYZB2               0x0008
#define D3DFVF_XYZB3               0x000a
#define D3DFVF_XYZB4               0x000c
#define D3DFVF_XYZB5               0x000e
#define D3DFVF_XYZW                0x4002
#define D3DFVF_NORMAL              0x0010
#define D3DFVF_PSIZE               0x0020
#define D3DFVF_DIFFUSE             0x0040
#define D3DFVF_SPECULAR            0x0080
#define D3DFVF_TEXCOUNT_MASK       0x0f00
#define D3DFVF_TEXCOUNT_SHIFT           8
#define D3DFVF_TEX0                0x0000
#define D3DFVF_TEX1                0x0100
#define D3DFVF_TEX2                0x0200
#define D3DFVF_TEX3                0x0300
#define D3DFVF_TEX4                0x0400
#define D3DFVF_TEX5                0x0500
#define D3DFVF_TEX6                0x0600
#define D3DFVF_TEX7                0x0700
#define D3DFVF_TEX8                0x0800
#define D3DFVF_LASTBETA_UBYTE4     0x1000
#define D3DFVF_LASTBETA_D3DCOLOR   0x8000
#define D3DFVF_RESERVED2           0x6000
    
  base::read( file, codes );
  std::bitset <32> bs( codes );

    std::cout << "D3D Flexible Vertex Format Bits: ";
    std::cout << bs << std::endl;

    numTex = (codes >> 8) & 0x0f;
    std::cout << " - Num textures: " << numTex << std::endl;

    switch( codes & D3DFVF_POSITION_MASK )
      {
      case D3DFVF_XYZ:
	std::cout << " -Vertex format includes the position of an untransformed vertex." << std::endl;
	break;

      case D3DFVF_XYZRHW:
	std::cout << " -Vertex format includes the position of a transformed vertex." << std::endl;
	break;
	
      case D3DFVF_XYZW:
	std::cout << " -Vertex format contains transformed and clipped (x, y, z, w) data." << std::endl;
	break;

      case D3DFVF_XYZB1:
	std::cout << " -Vertex format contains position data, and 1 weighting values to use for multimatrix vertex blending operations." << std::endl;
	break;
	
      case D3DFVF_XYZB2:
	std::cout << " -Vertex format contains position data, and 2 weighting values to use for multimatrix vertex blending operations." << std::endl;
	break;
	
      case D3DFVF_XYZB3:
	std::cout << " -Vertex format contains position data, and 3 weighting values to use for multimatrix vertex blending operations." << std::endl;
	break;
	
      case D3DFVF_XYZB4:
	std::cout << " -Vertex format contains position data, and 4 weighting values to use for multimatrix vertex blending operations." << std::endl;
	break;
	
      case D3DFVF_XYZB5:
	std::cout << " -Vertex format contains position data, and 5 weighting values to use for multimatrix vertex blending operations." << std::endl;
	break;
	
      }

    if( (codes & D3DFVF_NORMAL) == D3DFVF_NORMAL )
    {
	std::cout << " -Vertex format includes a vertex normal vector."
		  << std::endl;
    }

    if( (codes & D3DFVF_DIFFUSE) == D3DFVF_DIFFUSE )
    {
	std::cout << " -Vertex format includes a diffuse color component."
		  << std::endl;
    }

    if( (codes & D3DFVF_SPECULAR) == D3DFVF_SPECULAR )
    {
	std::cout << " -Vertex format includes a specular color component."
		  << std::endl;
    }

    switch( codes & D3DFVF_TEXCOUNT_MASK )
      {
      case D3DFVF_TEX0:
	std::cout << " -Vertex format includes no tex coords."
		  << std::endl;
	break;

      case D3DFVF_TEX1:
	std::cout << " -Vertex format includes 1 set of tex coords."
		  << std::endl;
	break;

      case D3DFVF_TEX2:
	std::cout << " -Vertex format includes 2 sets of tex coords."
		  << std::endl;
	break;

      case D3DFVF_TEX3:
	std::cout << " -Vertex format includes 3 sets of tex coords."
		  << std::endl;
	break;

      case D3DFVF_TEX4:
	std::cout << " -Vertex format includes 4 sets of tex coords."
		  << std::endl;
	break;

      case D3DFVF_TEX5:
	std::cout << " -Vertex format includes 5 sets of tex coords."
		  << std::endl;
	break;

      case D3DFVF_TEX6:
	std::cout << " -Vertex format includes 6 sets of tex coords."
		  << std::endl;
	break;

      case D3DFVF_TEX7:
	std::cout << " -Vertex format includes 7 sets of tex coords."
		  << std::endl;
	break;

      case D3DFVF_TEX8:
	std::cout << " -Vertex format includes 8 sets of tex coords."
		  << std::endl;
	break;
      }

    if( (codes & D3DFVF_LASTBETA_UBYTE4) == D3DFVF_LASTBETA_UBYTE4 )
    {
	std::cout << " - The last beta field in the vertex position data"
		  << " will be of type UBYTE4." << std::endl;
    }

    if( (codes & D3DFVF_LASTBETA_D3DCOLOR) == D3DFVF_LASTBETA_D3DCOLOR )
    {
	std::cout << " - The last beta field in the vertex position data "
		  << "will be of type D3DCOLOR." << std::endl;
    }

    return (sizeof( codes ));
}

unsigned int msh::readMSH( std::istream &file, std::string path )
{
  basePath = path;
  unsigned int total = 0;
  std::string form;
  unsigned int meshSize;
  std::string type;
  
  total += readFormHeader( file, "MESH", meshSize );
  std::cout << "Found MESH form" << std::endl;
  
  unsigned int size;
  total += readFormHeader( file, form, size, type );
  if( form != "FORM")
    {
      std::cout << "Expected FORM not: " << form << std::endl;
      exit( 0 );
    }
  std::cout << "Found " << form << " " << type
	    << ": " << size-4 << " bytes"
	    << std::endl;
  
  total += model::readAPPR( file );
  total += readSPS( file );
  
  if( meshSize == (total-8) )
    {
      std::cout << "Finished reading MESH" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading MESH" << std::endl;
    }
  
  return total;
}


unsigned int msh::readSPS( std::istream &file )
{
    unsigned int total = 0;
    std::string form, type;
    unsigned int spsSize;

    total += readFormHeader( file, form, spsSize, type );
    spsSize += 8; // Size of geode including initial FORM and size.
    if( form != "FORM" || type != "SPS " )
    {
	std::cout << "Expected Form of type SPS: " << type << std::endl;
	exit( 0 );
    }
    std::cout << "Found SPS form" << std::endl;

    // Skip next form, size and type...
    file.seekg( 12, std::ios_base::cur );
    total += 12;

    // Read CNT record
    unsigned int cntSize;
    total += readRecordHeader( file, type, cntSize );
    if( type != "CNT " || cntSize != 4 )
    {
	std::cout << "Expected CNT record with size 4" << std::endl;
	exit( 0 );
    }

    unsigned int numGeode;
    total += base::read( file, numGeode );
    std::cout << "CNT: " << numGeode << std::endl;

    for( unsigned int i = 0; i < numGeode; ++i )
    {
	total += readGeode( file, i+1 );
    }

    if( total == spsSize )
    {
	std::cout << "Finished reading SPS." << std::endl;
    }
    else
    {
	std::cout << "Error reading SPS!" << std::endl;
	std::cout << "Read " << total << " out of " << spsSize
		  << std::endl;
    }

    return total;
}

unsigned int msh::readGeode( std::istream &file,
			     const unsigned int nodeNumber )
{
    unsigned int total = 0;

    std::string type;
    unsigned int geodeSize;
    unsigned int size;
    unsigned int number;

    // Read top level FORM record.
    total += readRecordHeader( file, type, geodeSize );
    geodeSize += 8; // Size of geode including initial FORM and size.
    file.width( 4 );
    file >> number;
    total += sizeof( number );
    if( type != "FORM" || number != nodeNumber )
    {
	std::cout << "Geometry id. Expected: " << nodeNumber
		  << " found: " << number << std::endl;
	exit( 0 );
    }

    // Read Shader file record
    total += readRecordHeader( file, type, size );
    if( type != "NAME" )
    {
	std::cout << "Expected record of type NAME: " << type << std::endl;
	exit( 0 );
    }
    char temp[255];
    std::string shaderName;
    file.getline( temp, size, 0 );
    shaderName = temp;
    total += size;
    base::fixSlash( shaderName );
    std::cout << "Shader file: " << shaderName << std::endl;


    // Read INFO record
    total += readRecordHeader( file, type, size );
    if( type != "INFO" || size != 4 )
    {
	std::cout << "Expected record of type INFO: " << type << std::endl;
	exit( 0 );
    }
    unsigned int infoNumber;
    total += base::read( file, infoNumber );
    std::cout << "Info: " << infoNumber << std::endl;

    // Load shader and textures...
    std::string fullShaderName = basePath;
    fullShaderName += shaderName;
    shaderList.push_back( shaderName );

    while( total < geodeSize )
    {
	total += readGeometry( file );
    }

    if( total == geodeSize )
    {
	std::cout << "Finished reading Geode." << std::endl;
    }
    else
    {
	std::cout << "Error reading Geode!" << std::endl;
	std::cout << "Read " << total << " out of " << geodeSize
		  << std::endl;
    }

    return total;
}

unsigned int msh::readGeometry( std::istream &file )
{
    std::string type;
    unsigned int geometrySize;
    unsigned int size;

    // Read top level FORM record.
    std::string form;
    unsigned int total = readFormHeader( file, form, geometrySize, type );
    geometrySize += 8; // Size of geometry including initial FORM and size.
    if( form != "FORM" )
    {
	std::cout << "Expected record of type FORM: " << form << std::endl;
	exit( 0 );
    }

    // Read INFO record
    total += readRecordHeader( file, type, size );
    if( type != "INFO" || size != 6 )
    {
	std::cout << "Expected INFO record of size 8: " << size << std::endl;
	exit( 0 );
    }

    unsigned int u1;
    total += base::read( file, u1 );
    std::cout << u1 << std::endl;
    
    unsigned short u2;
    total += base::read( file, u2 );
    std::cout << u2 << std::endl;
    
    //total += readUnknown( file, size-6 );

    // Read VTXA FORM record.
    total += readFormHeader( file, form, size, type );
    if( form != "FORM" || type != "VTXA" )
    {
	std::cout << "Expected FORM of type VTXA: " << type << std::endl;
	exit( 0 );
    }

    // Read next level FORM record.
    total += readFormHeader( file, form, size, type );
    if( form != "FORM" )
    {
	std::cout << "Expected record of type FORM: " << form << std::endl;
	exit( 0 );
    }

    // Read INFO record
    total += readRecordHeader( file, type, size );
    if( type != "INFO" || size != 8 )
    {
	std::cout << "Expected INFO record of size 8: " << size << std::endl;
	exit( 0 );
    }

    unsigned int d3dfvfCodes;
    unsigned int numTextures;
    total += readD3DFVF( file, d3dfvfCodes, numTextures );

    unsigned int numVerts;
    total += base::read( file, numVerts );
    std::cout << "Num Vertices: " << numVerts << std::endl;
    
    total += readGeometryDATA( file, numVerts );

    unsigned int bytesPerIndex = 0;
    total += readGeometryINDX( file, bytesPerIndex );

    if( total != geometrySize )
    {
	total += readGeometrySIDX( file, bytesPerIndex );
    }

    if( total == geometrySize )
    {
	std::cout << "Finished reading Geometry." << std::endl;
    }
    else
    {
	std::cout << "Error reading Geometry!" << std::endl;
	std::cout << "Read " << total << " out of " << geometrySize
		  << std::endl;
    }


    return total;
}

unsigned int msh::readGeometrySIDX( std::istream &file, unsigned int bytesPerIndex )
{
    std::string type;
    unsigned int size;
    // Read SIDX record
    unsigned int total = readRecordHeader( file, type, size );
    if( type != "SIDX" )
    {
	std::cout << "Expected SIDX record not: " << type << std::endl;
	return 0;
    }
    std::cout << "Reading SIDX record." << std::endl;
    std::cout << "size: " << size << std::endl;

    unsigned int num;
    total += base::read( file, num );
    std::cout << "Num matrix/index/triangle sets: " << num << std::endl;
    
    for( unsigned int j = 0; j < num; ++j )
    {
      float rx, ry, rz;
      total += base::read( file, rx );
      std::cout << "X rotation?: " << rx << std::endl;
      total += base::read( file, ry );
      std::cout << "Y rotation?: " << ry << std::endl;
      total += base::read( file, rz );
      std::cout << "Z rotation?: " << rz << std::endl;
      
      unsigned int numIndex;
      total += base::read( file, numIndex );
      std::cout << "Num index: " << numIndex << std::endl;
      std::cout << "Num triangles: " << numIndex/3 << std::endl;
      
      std::cout << "Bytes per index: " << bytesPerIndex << std::endl;
      
      mshVertexIndex *mvi = new mshVertexIndex( bytesPerIndex );
      
      mvi->read( file, numIndex );
      
      if( vertexData.size() > 0 )
	{
	  std::cout << "Index data: " << (vertexData.size()-1) << std::endl;
	  mvi->setShaderIndex( shaderList.size() -1 );
	  mvi->setDataIndex( vertexData.size()-1 );
	}
      
      indexData.push_back( mvi );
    }
    
    return size+8;
}

unsigned int msh::readGeometryINDX( std::istream &file, unsigned int &bytesPerIndex )
{
    std::string type;
    unsigned int size;

    // Read INDX record
    readRecordHeader( file, type, size );
    if( type != "INDX" )
    {
	std::cout << "Expected INDX record not: " << type << std::endl;
	exit( 0 );
    }
    std::cout << "Reading INDX record." << std::endl;

    std::cout << "size: " << size << std::endl;

    unsigned int numIndex;
    base::read( file, numIndex );
    std::cout << "Num index: " << numIndex << std::endl;
    std::cout << "Num triangles: " << numIndex/3 << std::endl;

    bytesPerIndex = (size-4)/numIndex;
    std::cout << "Bytes per index: " << bytesPerIndex << std::endl;

    mshVertexIndex *mvi = new mshVertexIndex( bytesPerIndex );

    mvi->read( file, numIndex );

    if( vertexData.size() > 0 )
      {
	std::cout << "Index data: " << (vertexData.size()-1) << std::endl;
	mvi->setShaderIndex( shaderList.size() -1 );
	mvi->setDataIndex( vertexData.size()-1 );
      }

    indexData.push_back( mvi );

    // Return size + size of FORM/size data.
    return size+8;
}


unsigned int msh::readGeometryDATA( std::istream &file,
				    unsigned int numVerts )
{
    std::string type;
    unsigned int size;
    // Read DATA record
    unsigned int total = readRecordHeader( file, type, size );
    size += 8;
    if( type != "DATA" )
    {
	std::cout << "Expected DATA record not: " << type << std::endl;
	exit( 0 );
    }

    unsigned int bytesPerVertex = (size-8)/numVerts;

    std::cout << std::fixed;
    std::cout << "Bytes per vertex: " << bytesPerVertex << std::endl;

    if( mshVertexData::isSupportedSize( bytesPerVertex ) )
      {
	std::cout << "Vertex size is supported" << std::endl;
	ml::mshVertexData *vData = new mshVertexData;
	vData->setBytesPerVertex( bytesPerVertex );
	vData->read( file, numVerts );
	//vData->print();
	vertexData.push_back( vData );
	total += numVerts * bytesPerVertex;
      }
    else
      {
	std::cerr << "Unsupported vertex size: "
		  << bytesPerVertex
		  << std::endl;
	exit( 0 );
      }

    if( size == total )
    {
        std::cout << "Finished reading DATA" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading DATA" << std::endl;
        std::cout << "Read " << total << " out of " << size
                  << std::endl;
     }

    return total;
}

