/** -*-c++-*-
 *  \class  trn
 *  \file   trn.cpp
 *  \author Kenneth R. Sewell III

 meshLib is used for the parsing and exporting .trn models.
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

#include <meshLib/trn.hpp>

#include <iostream>
#include <bitset>
#include <cstdlib>

using namespace ml;

trn::trn()
{
}

trn::~trn()
{
}

unsigned int trn::readTRN( std::istream &file, const std::string &debugString )
{
  unsigned int ptatSize;
  // PTAT Form ( Level 0 )
  unsigned int total = readFormHeader( file, "PTAT", ptatSize );
  ptatSize += 8;
  std::cout << "Found PTAT form" << std::endl;

  // Child form of PTAT ( Level 1 )
  std::string form, type;
  unsigned int size;
  total += readFormHeader( file, form, size, type );
  std::cout << "Found form: " << form << std::endl;

  total += readTRNDATA( file, debugString );

  // TGEN Form ( Level 2 )
  total += readTGEN( file, debugString );

  // DATA before WMAP and SMAP
  total += readMapDATA( file, debugString );

  if( ptatSize == total )
    {
      std::cout << "Finished reading PTAT" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading PTAT" << std::endl;
      std::cout << "Read " << total << " out of " << ptatSize
		<< std::endl;
    }

  return total;
}

unsigned int trn::readTRNDATA( std::istream &file,
			       const std::string &debugString )
{
  std::string dbgStr = debugString + "DATA: ";

  unsigned int size;
  std::string type;

  // DATA record ( Level 2 )
  unsigned int total = readRecordHeader( file, type, size );
  size += 8;
  if( type != "DATA" )
    {
      std::cout << "Expected DATA record: " << type << std::endl;
      throw std::exception();
    }
  std::cout << debugString << "Found DATA record" << std::endl;

  std::string name;
  total += base::read( file, name );
  std::cout << dbgStr << name << std::endl;
    
  std::cout.flags ( std::ios_base::showpoint );
  total += base::read( file, terrainSize );
  std::cout << dbgStr << "Terrain size: " << terrainSize << std::endl;
  
  total += base::read( file, chunkWidth );
  std::cout << dbgStr << "Chunk width: " << chunkWidth << std::endl;

  total += base::read( file, tilesPerChunk );
  std::cout << dbgStr << "Tiles per chunk: " << tilesPerChunk << std::endl;
    
  unsigned int x4;
  total += base::read( file, x4 );
  std::cout << dbgStr << x4 << std::endl;

  total += base::read( file, globalWaterTableHeight );
  std::cout << dbgStr << "Global water table height: "
	    << globalWaterTableHeight << std::endl;
    
  total += base::read( file, globalWaterTableShaderSize );
  std::cout << dbgStr << "Global water table shader size: "
	    << globalWaterTableShaderSize << std::endl;

  total += base::read( file, globalWaterTableShader );
  std::cout << dbgStr << "Global water table shader: "
	    << globalWaterTableShader << std::endl;

  float u1;
  total += base::read( file, u1 );
  std::cout << dbgStr << "???: " << u1 << std::endl;

  total += base::read( file, collidableFloraMinDistance );
  std::cout << dbgStr << "Collidable flora min distance: "
	    << collidableFloraMinDistance << std::endl;

  total += base::read( file, collidableFloraMaxDistance );
  std::cout << dbgStr << "Collidable flora max distance: "
	    << collidableFloraMaxDistance << std::endl;

  total += base::read( file, collidableFloraTileSize );
  std::cout << dbgStr << "Collidable flora tile size: "
	    << collidableFloraTileSize << std::endl;

  total += base::read( file, collidableFloraTileBorder );
  std::cout << dbgStr << "Collidable flora tile border: "
	    << collidableFloraTileBorder << std::endl;

  total += base::read( file, collidableFloraSeed );
  std::cout << dbgStr << "Collidable flora seed: "
	    << collidableFloraSeed << std::endl;

  total += base::read( file, nonCollidableFloraMinDistance );
  std::cout << dbgStr << "Non-collidable flora min distance: "
	    << nonCollidableFloraMinDistance << std::endl;

  total += base::read( file, nonCollidableFloraMaxDistance );
  std::cout << dbgStr << "Non-collidable flora max distance: "
	    << nonCollidableFloraMaxDistance << std::endl;

  total += base::read( file, nonCollidableFloraTileSize );
  std::cout << dbgStr << "Non-collidable flora tile size: "
	    << nonCollidableFloraTileSize << std::endl;

  total += base::read( file, nonCollidableFloraTileBorder );
  std::cout << dbgStr << "Non-collidable flora tile border: "
	    << nonCollidableFloraTileBorder << std::endl;

  total += base::read( file, nonCollidableFloraSeed );
  std::cout << dbgStr << "Non-collidable flora seed: "
	    << nonCollidableFloraSeed << std::endl;

  total += base::read( file, nearRadialFloraMinDistance );
  std::cout << dbgStr << "Near radial flora min distance: "
	    << nearRadialFloraMinDistance << std::endl;

  total += base::read( file, nearRadialFloraMaxDistance );
  std::cout << dbgStr << "Near radial flora max distance: "
	    << nearRadialFloraMaxDistance << std::endl;

  total += base::read( file, nearRadialFloraTileSize );
  std::cout << dbgStr << "Near radial flora tile size: "
	    << nearRadialFloraTileSize << std::endl;

  total += base::read( file, nearRadialFloraTileBorder );
  std::cout << dbgStr << "Near radial flora tile border: "
	    << nearRadialFloraTileBorder << std::endl;

  total += base::read( file, nearRadialFloraSeed );
  std::cout << dbgStr << "Near radial flora seed: "
	    << nearRadialFloraSeed << std::endl;

  total += base::read( file, farRadialFloraMinDistance );
  std::cout << dbgStr << "Far radial flora min distance: "
	    << farRadialFloraMinDistance << std::endl;

  total += base::read( file, farRadialFloraMaxDistance );
  std::cout << dbgStr << "Far radial flora max distance: "
	    << farRadialFloraMaxDistance<< std::endl;

  total += base::read( file, farRadialFloraTileSize );
  std::cout << dbgStr << "Far radial flora tile size: "
	    << farRadialFloraTileSize << std::endl;

  total += base::read( file, farRadialFloraTileBorder );
  std::cout << dbgStr << "Far radial flora tile border: "
	    << farRadialFloraTileBorder << std::endl;

  total += base::read( file, farRadialFloraSeed );
  std::cout << dbgStr << "Far radial flora seed: "
	    << farRadialFloraSeed << std::endl;

  if( size == total )
    {
      std::cout << debugString << "Finished reading DATA" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading DATA" << std::endl;
      std::cout << "Read " << total << " out of " << size
		<< std::endl;
    }

  return total;
}

unsigned int trn::readTGEN( std::istream &file, const std::string &debugString )
{
  std::string dbgStr = debugString + "TGEN: ";
  std::string form;
  unsigned int tgenSize;
  std::string type;

  unsigned int total = readFormHeader( file, "TGEN", tgenSize );
  tgenSize += 8;
  std::cout << debugString << "Found TGEN form" << std::endl;

  unsigned int size;
  total += readFormHeader( file, form, size, type );
  size += 8;
  if( form != "FORM" )
    {
      std::cout << "Expected Form: " << form << std::endl;
      throw std::exception();
    }
  std::cout << dbgStr << "Found FORM: " << type << std::endl;

  while( total < tgenSize )
    {
      base::peekHeader( file, form, size, type );

      if( "FORM" == form )
	{
	  if( "SGRP" == type )
	    {
	      total += readSGRP( file, dbgStr );
	    }
	  else if( "FGRP" == type )
	    {
	      total += readFGRP( file, dbgStr );
	    }
	  else if( "RGRP" == type )
	    {
	      total += readRGRP( file, dbgStr );
	    }
	  else if( "EGRP" == type )
	    {
	      total += readEGRP( file, dbgStr );
	    }
	  else if( "MGRP" == type )
	    {
	      total += readMGRP( file, dbgStr );
	    }
	  else if( "LYRS" == type )
	    {
	      total += readLYRS( file, dbgStr );
	    }
	  else
	    {
	      std::cout << "Unexpected FORM: " << type << std::endl;
	    }
	}
      else
	{
	  std::cout << "Expected FORM, found: " << form << std::endl;
	  throw std::exception();
	}
    }

  if( tgenSize == total )
    {
      std::cout << debugString << "Finished reading TGEN" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading TGEN" << std::endl;
      std::cout << "Read " << total << " out of " << tgenSize
		<< std::endl;
    }
  return total;
}

// Water or weight maps?
unsigned int trn::readWMAP( std::istream &file, const std::string &debugString )
{
  std::string dbgStr = debugString + "WMAP: ";
  std::string form;
  unsigned int wmapSize;
  std::string type;

  unsigned int total = readRecordHeader( file, type, wmapSize );
  wmapSize += 8;
  if( type != "WMAP" )
    {
      std::cout << "Expected record of type WMAP: " << type << std::endl;
      throw std::exception();
    }
  std::cout << debugString << "Found WMAP record of size: "
	    << wmapSize << std::endl;

  if( ( wmapSize - 8 ) != ( mapHeight * mapWidth ) )
    {
      std::cout << dbgStr << "WMAP size: " << wmapSize
		<< " does not match expected size: "
		<< ( mapHeight * mapWidth ) << std::endl;
      throw std::exception();
    }

  unsigned char x;
  for( unsigned int i = 0; i < mapHeight; ++i )
    {
      for( unsigned int j = 0; j < mapWidth; ++j )
	{
	  total += base::read( file, x );
#if 0
	  std::cout  << (unsigned int)x << " ";
#endif
	}
    }

  if( wmapSize == total )
    {
      std::cout << "Finished reading WMAP" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading WMAP" << std::endl;
      std::cout << "Read " << total << " out of " << wmapSize
		<< std::endl;
    }
  return total;
}

// Seed maps?
unsigned int trn::readSMAP( std::istream &file, const std::string &debugString )
{
  std::string dbgStr = debugString + "SMAP: ";
  unsigned int smapSize;
  std::string type;
  unsigned int total = readRecordHeader( file, type, smapSize );
  smapSize += 8;

  if( type != "SMAP" )
    {
      std::cout << "Expected record of type SMAP: " << type << std::endl;
      throw std::exception();
    }
  std::cout << debugString << "Found SMAP record of size: " << smapSize
	    << std::endl;
  

  if( ( smapSize - 8 ) != ( mapHeight * mapWidth ) )
    {
      std::cout << "SMAP size: " << smapSize
		<< " does not match expected size: "
		<< ( mapHeight * mapWidth ) << std::endl;
      throw std::exception();
    }

  unsigned char x;
  for( unsigned int i = 0; i < mapHeight; ++i )
    {
      for( unsigned int j = 0; j < mapWidth; ++j )
	{
	  total += base::read( file, x );
#if 0
	  std::cout << (unsigned int)x << " ";
#endif
	}
    }

  if( smapSize == total )
    {
      std::cout << debugString << "Finished reading SMAP" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading SMAP" << std::endl;
      std::cout << "Read " << total << " out of " << smapSize
		<< std::endl;
    }
  return total;
}

unsigned int trn::readSFAM( std::istream &file,
			    const std::string &debugString,
			    sfam &newSFAM )
{
  std::string dbgStr = debugString + "SFAM: ";
  std::string form;
  unsigned int sfamSize;
  std::string type;

  unsigned int total = readRecordHeader( file, type, sfamSize );
  sfamSize += 8;
  if( type != "SFAM" )
    {
      std::cout << "Expected record of type SFAM: " << type << std::endl;
      throw std::exception();
    }
  std::cout << debugString << "Found SFAM record of size: "
	    << sfamSize << std::endl;

  unsigned int x;
  total += base::read( file, x );
  std::cout << dbgStr << "Shader family number: " << x << std::endl;;

  total += base::read( file, newSFAM.name );
  std::cout << dbgStr << "'" << newSFAM.name << "'" << std::endl;

  total += base::read( file, newSFAM.abstract );
  std::cout << dbgStr << "'" << newSFAM.abstract << "'" << std::endl;

  // Color color...
  file.read( (char*)(newSFAM.rgb), sizeof( unsigned char ) * 3 );
  total += sizeof( unsigned char ) * 3;
  std::cout << dbgStr << "rgb: "
	    << (unsigned int)newSFAM.rgb[0] << ", "
	    << (unsigned int)newSFAM.rgb[1] << ", "
	    << (unsigned int)newSFAM.rgb[2] << std::endl;

  total += base::read( file, newSFAM.u1 );
  std::cout << dbgStr << newSFAM.u1 << std::endl;

  total += base::read( file, newSFAM.u2 );
  std::cout << dbgStr << newSFAM.u2 << std::endl;
  
  unsigned int numShaders;
  total += base::read( file, numShaders );
  std::cout << dbgStr << "numShaders: " << numShaders << std::endl;

  for( unsigned int shader = 0; shader < numShaders; ++shader )
    {
      std::string tempName, shaderName;
      total += base::read( file, tempName );
      if( !tempName.empty() )
	{
	  shaderName = "shader/" + tempName;
	}
      std::cout << dbgStr << "Shader name: '" << shaderName << "'" << std::endl;

      float shaderWeight;
      total += base::read( file, shaderWeight );
      std::cout << dbgStr << "Shader weight: " << shaderWeight << std::endl;

      newSFAM.shaderMap[shaderName] = shaderWeight;
    }

  if( sfamSize == total )
    {
      std::cout << debugString << "Finished reading SFAM" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading SFAM" << std::endl;
      std::cout << "Read " << total << " out of " << sfamSize
		<< std::endl;
    }
  return total;
}

unsigned int trn::readMapDATA( std::istream &file,
			       const std::string &debugString )
{
  std::string dbgStr = debugString + "DATA: ";
  std::string form;
  unsigned int formSize;
  std::string type;

  // Parent Form of DATA,WMAP and SMAP ( Level 2 )
  unsigned int total = readFormHeader( file, form, formSize, type );
  formSize += 8;
  std::cout << debugString << "Found form: " << type << std::endl;

  // DATA
  unsigned int size;
  total += readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected record of type DATA: " << type << std::endl;
      throw std::exception();
    }
  std::cout << dbgStr << "Found DATA record of size: " << size << std::endl;

  float x1, x2;
  total += base::read( file, x1 );
  total += base::read( file, x2 );
  total += base::read( file, mapHeight );
  total += base::read( file, mapWidth );

  std::cout << dbgStr << " Terrain size(m): " << x1 << std::endl;
  std::cout << dbgStr << "   Block size(m): " << x2 << std::endl;
  std::cout << dbgStr << "      Map height: " << mapHeight << std::endl;
  std::cout << dbgStr << "       Map width: " << mapWidth << std::endl;

  // WMAP
  total += readWMAP( file, dbgStr );

  // SMAP
  total += readSMAP( file, dbgStr );

  if( formSize == total )
    {
      std::cout << "Finished reading Map Data" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading Map Data" << std::endl;
      std::cout << "Read " << total << " out of " << size
		<< std::endl;
    }
  return total;
}

unsigned int trn::readSGRP( std::istream &file, const std::string &debugString )
{
  std::string dbgStr = debugString + "SGRP: ";
  unsigned int sgrpSize;
  unsigned int total = readFormHeader( file, "SGRP", sgrpSize );
  sgrpSize += 8;
  std::cout << debugString << "Found SGRP form" << std::endl;

  unsigned int size;
  std::string form, type;
  total += readFormHeader( file, form, size, type );
  size += 8;
  if( form != "FORM" )
    {
      std::cout << "Expected Form: " << form << std::endl;
      throw std::exception();
    }
  std::cout << dbgStr << "Found FORM: " << type << std::endl;

  while( total < size-12 )
    {
      sfam newSFAM;
      total += readSFAM( file, dbgStr, newSFAM );
      sfamMap[newSFAM.familyNumber] = newSFAM;
    }

  if( sgrpSize == total )
    {
      std::cout << debugString << "Finished reading SGRP" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading SGRP" << std::endl;
      std::cout << "Read " << total << " out of " << sgrpSize
		<< std::endl;
    }
  return total;
}

unsigned int trn::readFFAM( std::istream &file, const std::string &debugString )
{
  std::string dbgStr = debugString + "FFAM: ";
  unsigned int size;
  std::string type;
  unsigned int total = readRecordHeader( file, type, size );
  size += 8;
  if( type != "FFAM" )
    {
      std::cout << "Expected record of type FFAM: " << type << std::endl;
      throw std::exception();
    }
  std::cout << debugString << "Found FFAM record" << std::endl;
  
  unsigned int u1;
  total += base::read( file, u1 );
  std::cout << dbgStr << "Flora family number: " << u1 << std::endl;

  std::string name;
  total += base::read( file, name );
  std::cout << dbgStr << "'" << name << "'" << std::endl;

  unsigned short u2;
  total += base::read( file, u2 );
  std::cout << dbgStr << u2 << std::endl;

  total += base::read( file, u2 );
  std::cout << dbgStr << u2 << std::endl;

  total += base::read( file, u2 );
  std::cout << dbgStr << u2 << std::endl;

  unsigned char u3;
  total += base::read( file, u3 );
  std::cout << dbgStr << (unsigned int)u3 << std::endl;

  total += base::read( file, u1 );
  std::cout << dbgStr << u1 << std::endl;

  unsigned int numApt;
  total += base::read( file, numApt );
  std::cout << dbgStr << "numApt: " << numApt << std::endl;

  for( unsigned int i = 0; i < numApt; ++i )
    {
      std::string aptName;
      total += base::read( file, aptName );
      std::cout << dbgStr << "'" << aptName << "'" << std::endl;
	  
      float u4;
      total += base::read( file, u4 );
      std::cout << dbgStr << u4 << std::endl;
	  
      total += base::read( file, u1 );
      std::cout << dbgStr << u1 << std::endl;

      total += base::read( file, u4 );
      std::cout << dbgStr << u4 << std::endl;

      total += base::read( file, u4 );
      std::cout << dbgStr << u4 << std::endl;

      total += base::read( file, u1 );
      std::cout << dbgStr << u1 << std::endl;

      total += base::read( file, u1 );
      std::cout << dbgStr << u1 << std::endl;

      total += base::read( file, u4 );
      std::cout << dbgStr << u4 << std::endl;

      total += base::read( file, u4 );
      std::cout << dbgStr << u4 << std::endl;
    }
  
  if( size == total )
    {
      std::cout << debugString << "Finished reading FFAM" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading FFAM" << std::endl;
      std::cout << "Read " << total << " out of " << size
		<< std::endl;
    }
  return total;
}

unsigned int trn::readFGRP( std::istream &file, const std::string &debugString )
{
  std::string dbgStr = debugString + "FGRP: ";
  unsigned int fgrpSize;
  unsigned int total = readFormHeader( file, "FGRP", fgrpSize );
  fgrpSize += 8;
  std::cout << debugString << "Found FGRP form" << std::endl;

  unsigned int size;
  std::string form, type;
  total += readFormHeader( file, form, size, type );
  size += 8;
  if( form != "FORM" )
    {
      std::cout << "Expected Form: " << form << std::endl;
      throw std::exception();
    }
  std::cout << dbgStr << "Found FORM: " << type << std::endl;

  while( total < fgrpSize )
    {
      total += readFFAM( file, dbgStr );
    }

  if( fgrpSize == total )
    {
      std::cout << debugString << "Finished reading FGRP" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading FGRP" << std::endl;
      std::cout << "Read " << total << " out of " << fgrpSize
		<< std::endl;
    }
  return total;
}

unsigned int trn::readRFAM( std::istream &file,
			    const std::string &rgrpType,
			    const std::string &debugString )
{
  std::string dbgStr = debugString + "RFAM: ";
  unsigned int size;
  std::string type;
  unsigned int total = readRecordHeader( file, type, size );
  size += 8;
  if( type != "RFAM" )
    {
      std::cout << "Expected record of type RFAM: " << type << std::endl;
      throw std::exception();
    }
  std::cout << debugString << "Found RFAM record" << std::endl;
  
  
  unsigned int u1;
  file.read( (char *)&u1, sizeof( u1 ) );
  total += sizeof( u1 );
  std::cout << dbgStr << u1 << std::endl;
  
  std::string name;
  total += base::read( file, name );
  std::cout << dbgStr << "'" << name << "'" << std::endl;

  unsigned short u2;
  file.read( (char *)&u2, sizeof( u2 ) );
  total += sizeof( u2 );
  std::cout << dbgStr << u2 << std::endl;
  
  file.read( (char *)&u2, sizeof( u2 ) );
  total += sizeof( u2 );
  std::cout << dbgStr << u2 << std::endl;
  
  file.read( (char *)&u2, sizeof( u2 ) );
  total += sizeof( u2 );
  std::cout << dbgStr << u2 << std::endl;
  
  unsigned char u3;
  file.read( (char *)&u3, sizeof( u3 ) );
  total += sizeof( u3 );
  std::cout << dbgStr << (unsigned int)u3 << std::endl;
  
  unsigned int numApt;
  file.read( (char *)&numApt, sizeof( numApt ) );
  total += sizeof( numApt );
  std::cout << dbgStr << "numApt: " << numApt << std::endl;

  for( unsigned int i = 0; i < numApt; ++i )
    {
      std::string tempName, aptName;
      total += base::read( file, tempName );
      if( tempName.empty() )
	{
	  aptName = tempName;
	}
      else
	{
	  aptName = "shader/" + tempName;
	}
      std::cout << dbgStr << "'" << aptName << "'" << std::endl;

      float u4;
      total += base::read( file, u4 );
      std::cout << dbgStr << u4 << std::endl;
      
      total += base::read( file, u4 );
      std::cout << dbgStr << u4 << std::endl;
      
      total += base::read( file, u4 );
      std::cout << dbgStr << u4 << std::endl;
      
      total += base::read( file, u4 );
      std::cout << dbgStr << u4 << std::endl;
      
      total += base::read( file, u4 );
      std::cout << dbgStr << u4 << std::endl;
      
      total += base::read( file, u4 );
      std::cout << dbgStr << u4 << std::endl;
      
      total += base::read( file, u4 );
      std::cout << dbgStr << u4 << std::endl;
      
      total += base::read( file, u1 );
      std::cout << dbgStr << u1 << std::endl;
      
      total += base::read( file, u4 );
      std::cout << dbgStr << u4 << std::endl;
      
      if( "0004" == rgrpType )
	{
	  total += base::read( file, u4 );
	  std::cout << dbgStr << u4 << std::endl;

	  total += base::read( file, u1 );
	  std::cout << dbgStr << u1 << std::endl;

	  total += base::read( file, u4 );
	  std::cout << dbgStr << u4 << std::endl;
	}
    }

  if( size == total )
    {
      std::cout << debugString << "Finished reading RFAM" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading RFAM" << std::endl;
      std::cout << "Read " << total << " out of " << size
		<< std::endl;
    }
  return total;
}

unsigned int trn::readRGRP( std::istream &file, const std::string &debugString )
{
  std::string dbgStr = debugString + "RGRP: ";
  std::string form;
  unsigned int rgrpSize;
  std::string type;

  unsigned int total = readFormHeader( file, form, rgrpSize, type );
  rgrpSize += 8;
  if( form != "FORM" || type != "RGRP" )
    {
      std::cout << "Expected Form of type RGRP: " << type << std::endl;
      throw std::exception();
    }
  std::cout << debugString << "Found RGRP form" << std::endl;

  unsigned int size;
  total += readFormHeader( file, form, size, type );
  size += 8;
  if( form != "FORM" )
    {
      std::cout << "Expected Form: " << form << std::endl;
      throw std::exception();
    }
  std::cout << dbgStr << "Found FORM: " << type << std::endl;

  while( total < rgrpSize )
    {
      total += readRFAM( file, type, dbgStr );
    }
    
  if( rgrpSize == total )
    {
      std::cout << debugString << "Finished reading RGRP" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading RGRP" << std::endl;
      std::cout << "Read " << total << " out of " << rgrpSize
		<< std::endl;
    }
  return total;
}

unsigned int trn::readEFAM( std::istream &file, const std::string &debugString )
{
  std::string dbgStr = debugString + "EFAM: ";
  unsigned int efamSize;
  unsigned int total = readFormHeader( file, "EFAM", efamSize );
  efamSize += 8;
  std::cout << debugString << "Found EFAM form" << std::endl;

  unsigned int size;
  std::string type;
  total += readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected record of type DATA: " << type << std::endl;
      throw std::exception();
    }
  std::cout << dbgStr << "Found DATA record" << std::endl;

  unsigned int u1;
  total += base::read( file, u1 );
  std::cout << dbgStr << u1 << std::endl;

  char temp[255];
  std::string name;
  file.read( temp, size - 12 );
  temp[size-12] = 0;
  name = temp;
  std::cout << dbgStr << "'" << name << "'" << std::endl;
  total += name.size();

  unsigned short u3;
  total += base::read( file, u3 );
  std::cout << dbgStr << u3 << std::endl;

  total += base::read( file, u3 );
  std::cout << dbgStr << u3 << std::endl;

  float u2;
  total += base::read( file, u2 );
  std::cout << dbgStr << u2 << std::endl;
  
  if( efamSize == total )
    {
      std::cout << debugString << "Finished reading EFAM" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading EFAM" << std::endl;
      std::cout << "Read " << total << " out of " << efamSize
		<< std::endl;
    }
  return total;
}

unsigned int trn::readEGRP( std::istream &file, const std::string &debugString )
{
  std::string dbgStr = debugString + "EGRP: ";
  std::string form;
  unsigned int egrpSize;
  std::string type;

  unsigned int total = readFormHeader( file, form, egrpSize, type );
  egrpSize += 8;
  if( form != "FORM" || type != "EGRP" )
    {
      std::cout << "Expected Form of type EGRP: " << type << std::endl;
      throw std::exception();
    }
  std::cout << debugString << "Found EGRP form" << std::endl;

  unsigned int size;
  total += readFormHeader( file, form, size, type );
  size += 8;
  if( form != "FORM" )
    {
      std::cout << "Expected Form: " << form << std::endl;
      throw std::exception();
    }
  std::cout << dbgStr << "Found FORM: " << type << std::endl;

  while( total < egrpSize )
    {
      total += readEFAM( file, dbgStr );
    }
    
  if( egrpSize == total )
    {
      std::cout << debugString << "Finished reading EGRP" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading EGRP" << std::endl;
      std::cout << "Read " << total << " out of " << egrpSize
		<< std::endl;
    }
  return total;
}

unsigned int trn::readMFRC( std::istream &file, const std::string &debugString )
{
  std::string dbgStr = debugString + "MFRC: ";
  unsigned int mfrcSize;
  std::string form;
  std::string type;
  unsigned int total = readFormHeader( file, form, mfrcSize, type );
  mfrcSize += 8;
  if( form != "FORM" || type != "MFRC" )
    {
      std::cout << "Expected Form of type MFRC: " << type << std::endl;
      throw std::exception();
    }
  std::cout << debugString << "Found MFRC form" << std::endl;

  unsigned int size;
  total += readFormHeader( file, form, size, type );
  if( form != "FORM" || type != "0001" )
    {
      std::cout << "Expected Form of type 0001: " << type << std::endl;
      throw std::exception();
    }
  std::cout << dbgStr << "Found 0001 form" << std::endl;

  total += readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected record of type DATA: " << type << std::endl;
      throw std::exception();
    }
  std::cout << dbgStr << "Found DATA record" << std::endl;

  unsigned int u1;
  total += base::read( file, u1 );
  std::cout << dbgStr << u1 << std::endl;

  total += base::read( file, u1 );
  std::cout << dbgStr << u1 << std::endl;

  float u2;
  total += base::read( file, u2 );
  std::cout << dbgStr << u2 << std::endl;

  total += base::read( file, u1 );
  std::cout << dbgStr << u1 << std::endl;

  total += base::read( file, u2 );
  std::cout << dbgStr << u2 << std::endl;

  unsigned int octaves;
  total += base::read( file, octaves );
  std::cout << dbgStr << "Octaves: " << octaves << std::endl;

  total += base::read( file, u2 );
  std::cout << dbgStr << u2 << std::endl;

  total += base::read( file, u2 );
  std::cout << dbgStr << u2 << std::endl;

  total += base::read( file, u2 );
  std::cout << dbgStr << u2 << std::endl;

  total += base::read( file, u2 );
  std::cout << dbgStr << u2 << std::endl;

  total += base::read( file, u2 );
  std::cout << dbgStr << u2 << std::endl;

  total += base::read( file, u2 );
  std::cout << dbgStr << u2 << std::endl;

  total += base::read( file, u1 );
  std::cout << dbgStr << u1 << std::endl;

  if( mfrcSize == total )
    {
      std::cout << debugString << "Finished reading MFRC" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading MFRC" << std::endl;
      std::cout << "Read " << total << " out of " << mfrcSize
		<< std::endl;
    }
  return total;
}

unsigned int trn::readMFAM( std::istream &file, const std::string &debugString )
{
  std::string dbgStr = debugString + "MFAM: ";
  unsigned int mfamSize;
  unsigned int total = readFormHeader( file, "MFAM", mfamSize );
  mfamSize += 8;
  std::cout << debugString << "Found MFAM form" << std::endl;

  unsigned int size;
  std::string type;
  total += readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected record of type DATA: " << type << std::endl;
      throw std::exception();
    }
  std::cout << dbgStr << "Found DATA record" << std::endl;

  unsigned int u1;
  total += base::read( file, u1 );
  std::cout << dbgStr << "Fractal family number: " << u1 << std::endl;

  char temp[255];
  std::string name;
  file.read( temp, size - 4 );
  name = temp;
  std::cout << dbgStr << name << std::endl;
  total += name.size()+1;

  total += readMFRC( file, dbgStr );
  
  if( mfamSize == total )
    {
      std::cout << debugString << "Finished reading MFAM" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading MFAM" << std::endl;
      std::cout << "Read " << total << " out of " << mfamSize
		<< std::endl;
    }
  return total;
}

unsigned int trn::readMGRP( std::istream &file, const std::string &debugString )
{
  std::string dbgStr = debugString + "MGRP: ";
  unsigned int mgrpSize;
  unsigned int total = readFormHeader( file, "MGRP", mgrpSize );
  mgrpSize += 8;
  std::cout << debugString << "Found MGRP form" << std::endl;

  unsigned int size;
  std::string form, type;
  total += readFormHeader( file, form, size, type );
  size += 8;
  if( form != "FORM" )
    {
      std::cout << "Expected Form: " << form << std::endl;
      throw std::exception();
    }
  std::cout << dbgStr << "Found FORM: " << type << std::endl;

#if 1
  while( total < mgrpSize )
    {
      total += readMFAM( file, dbgStr );
    }
#else
  total += readUnknown( file, mgrpSize-total );
#endif

   
  if( mgrpSize == total )
    {
      std::cout << debugString << "Finished reading MGRP" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading MGRP" << std::endl;
      std::cout << "Read " << total << " out of " << mgrpSize
		<< std::endl;
    }
  return total;
}

unsigned int trn::readLYRS( std::istream &file, const std::string &debugString )
{
  std::string dbgStr = debugString + "LYRS: ";
  unsigned int lyrsSize;
  unsigned int total = readFormHeader( file, "LYRS", lyrsSize );
  lyrsSize += 8;
  std::cout << debugString << "Found LYRS form" << std::endl;

  while( total < lyrsSize )
    {
      std::shared_ptr<trnLayer> newLayer( new trnLayer );
      total += newLayer->read( file, dbgStr );
      layerList.push_back( newLayer );
    }

  if( lyrsSize == total )
    {
      std::cout << debugString << "Finished reading LYRS" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading LYRS" << std::endl;
      std::cout << "Read " << total << " out of " << lyrsSize
		<< std::endl;
    }
  return total;
}


bool trn::applyLayers( const float &originX,
		       const float &originY,
		       const float &spacingX,
		       const float &spacingY,
		       const unsigned int &numRows,
		       const unsigned int &numCols,
		       float *data) const
{
  for( std::list< std::shared_ptr<trnLayer> >::const_iterator
	 currentLayer = layerList.begin();
       currentLayer != layerList.end();
       ++currentLayer )
    {
      (*currentLayer)->apply( originX,
			      originY,
			      spacingX,
			      spacingY,
			      numRows,
			      numCols,
			      data ) ;
    }

  return true;
}
