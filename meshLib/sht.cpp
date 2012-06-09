/** -*-c++-*-
 *  \class  sht
 *  \file   sht.hpp
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

#include <meshLib/sht.hpp>
#include <meshLib/eft.hpp>
#include <iostream>
#include <cstdlib>
#include <climits>

using namespace ml;

sht::sht():
  mainTextureUnit( 0 )
{
}

sht::~sht()
{
}

unsigned int sht::readSHT( std::istream &file, std::string path )
{
  basePath = path;
  unsigned int sshtSize;
  // Reset class
  normalMapUnit = UINT_MAX;
  texTag.clear();
  coordMapping.clear();
  texTag.resize( 10 );
  coordMapping.resize( 10 );
  for( unsigned int i = 0; i < 10; ++i )
    {
      coordMapping[i] = UINT_MAX;
    }

  unsigned int total = readFormHeader( file, "SSHT", sshtSize );
  sshtSize += 8;
  std::cout << "Found SSHT form"
	    << ": " << sshtSize-12 << " bytes"
	    << std::endl;

  unsigned int size;
  std::string form, type;
  total += readFormHeader( file, form, size, type );
  if( form != "FORM" )
    {
      std::cout << "Expected FORM: " << form << std::endl;
      throw std::exception();
    }
  std::cout << "Found " << form << " " << type
	    << ": " << size-4 << " bytes"
	    << std::endl;

  while( total < sshtSize )
    {
      // Peek at next record, but keep file at same place.
      peekHeader( file, form, size, type );

      if( form == "FORM" )
	{
	  if( type == "MATS" )
	    { total += readMATS( file ); }
	  else if( type == "TXMS" )
	    { total += readTXMS( file ); }
	  else if( type == "TCSS" )
	    { total += readTCSS( file ); }
	  else if( type == "TFNS" )
	    { total += readTFNS( file ); }
	  else if( type == "TSNS" )
	    { total += readTSNS( file ); }
	  else if( type == "ARVS" )
	    { total += readARVS( file ); }
	  else if( type == "EFCT" )
	    {
	      eft effect;
	      total += effect.readEFT( file, basePath );
	    }
	  else
	    {
	      std::cout << "Unexpected form: " << type << std::endl;
	      throw std::exception();
	    }
	}
      else if ( form == "NAME" )
	{
	  total += readNAME( file );
	}
      else
	{
	  std::cout << "Unexpected record: " << form << std::endl;
	  throw std::exception();
	}
    }

  if( sshtSize == total )
    {
      std::cout << "Finished reading SSHT" << std::endl;
    }
  else
    {
      std::cout << "FAILED in reading SSHT" << std::endl;
      std::cout << "Read " << total << " out of " << sshtSize
		<< std::endl;
    }

  return total;
}

unsigned int sht::readMATS( std::istream &file )
{
  unsigned int matsSize;
  unsigned int total = readFormHeader( file, "MATS", matsSize );
  matsSize += 8;
  std::cout << "Found FORM MATS: " << matsSize-12 << " bytes"
	    << std::endl;

  unsigned int size;
  total += readFormHeader( file, "0000", size );
  std::cout << "Found FORM 0000: " << size-4 << " bytes"
	    << std::endl;

  std::string type;
  unsigned int matsFound = 0;
  while( total < matsSize )
    {
      ++matsFound;
      // Read TAG record
      total += readRecordHeader( file, type, size );
      if( type != "TAG " )
	{
	  std::cout << "Expected record of type TAG: " << type << std::endl;
	  throw std::exception();
	}
      std::cout << "Found " << type
		<< ": " << size << " bytes"
		<< std::endl;
	
      file.width( size );
      file >> diffuseTextureTag;
      total += size;
      std::cout << "Material texture tag: " << diffuseTextureTag
		<< std::endl;
	
      // Read MATL record
      total += readRecordHeader( file, type, size );
      if( type != "MATL" )
	{
	  std::cout << "Expected record of type MATL: " << type << std::endl;
	  throw std::exception();
	}
      std::cout << "Found record " << type
		<< ": " << size << " bytes"
		<< std::endl;
	
      if( 68 != size )
	{
	  std::cout << "Expected MATL size 68: " << size << std::endl;
	  throw std::exception();
	}

      file.read( (char *)ambient, sizeof( float ) * 4 );
      file.read( (char *)diffuse, sizeof( float ) * 4 );
      file.read( (char *)specular, sizeof( float ) * 4 );
      file.read( (char *)emissive, sizeof( float ) * 4 );
      file.read( (char *)&shininess, sizeof( float ) );
      total += 17 * sizeof( float );
	
      std::cout << "Ambient: "
		<< ambient[0] << " "
		<< ambient[1] << " "
		<< ambient[2] << " "
		<< ambient[3] << std::endl;
	
      std::cout << "Diffuse: "
		<< diffuse[0] << " "
		<< diffuse[1] << " "
		<< diffuse[2] << " "
		<< diffuse[3] << std::endl;
	
      std::cout << "Specular: "
		<< specular[0] << " "
		<< specular[1] << " "
		<< specular[2] << " "
		<< specular[3] << std::endl;
	
      std::cout << "Emissive: "
		<< emissive[0] << " "
		<< emissive[1] << " "
		<< emissive[2] << " "
		<< emissive[3] << std::endl;
	
      std::cout << "Shininess: " << shininess <<std::endl;
    }

  if( matsFound > 1 ){ std::cout << "*************************"<<std::endl;}
  if( matsSize == total )
    {
      std::cout << "Finished reading MATS" << std::endl;
    }
  else
    {
      std::cout << "FAILED in reading MATS" << std::endl;
      std::cout << "Read " << total << " out of " << matsSize
		<< std::endl;
    }

  return total;
}

unsigned int sht::readTXMS( std::istream &file )
{
  unsigned int txmsSize;
  unsigned int total = readFormHeader( file, "TXMS", txmsSize );
  txmsSize += 8; // Add size of FORM and size fields.
  std::cout << "Found FORM TXMS: " << txmsSize-12 << " bytes"
	    << std::endl;

  while( total < txmsSize )
    {
      total += readTXM( file );
    }

  if( txmsSize == total )
    {
      std::cout << "Finished reading TXMS" << std::endl;
    }
  else
    {
      std::cout << "FAILED in reading TXMS" << std::endl;
      std::cout << "Read " << total << " out of " << txmsSize
		<< std::endl;
    }

  return total;
}

unsigned int sht::readTXM( std::istream &file )
{
  unsigned int txmSize;
  // Read FORM TXM record
  unsigned int total = readFormHeader( file, "TXM ", txmSize );
  txmSize += 8;
  std::cout << "Found FORM TXM : " << txmSize-12 << " bytes"
	    << std::endl;

  // Read FORM 0001 record
  unsigned int size;
  std::string form, type;
  total += readFormHeader( file, form, size, type );
  //if( form != "FORM" || type != "0001" )
  if( form != "FORM" )
    {
      std::cout << "Expected Form of type 0001: " << type << std::endl;
      throw std::exception();
    }
  std::cout << "Found " << form << " " << type
	    << ": " << size-4 << " bytes"
	    << std::endl;


  total += readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected record of type DATA: " << type << std::endl;
      throw std::exception();
    }

  std::string textureTag;
  file.width( 4 );
  file >> textureTag;
  total += 4;

  std::cout << "Texture tag: " << textureTag << std::endl;
  total += readUnknown( file, size-4 );

  if( total < txmSize )
    {
      total += readRecordHeader( file, type, size );
      if( type != "NAME" )
	{
	  std::cout << "Expected record of type NAME: " << type << std::endl;
	  throw std::exception();
	}

      std::string textureName;
      total += base::read( file, textureName );
      base::fixSlash( textureName );

      std::string fullTextureName = basePath + textureName;
      std::cout << "Texture name: " << fullTextureName << std::endl;

      if( textureTag == diffuseTextureTag )
	{
	  diffuseTextureName = fullTextureName;
	}

      if( textureTag == "NIAM" )
	{
	  mainTextureName = fullTextureName;
	}
      else if( textureTag == "LMRN" )
	{
	  normalTextureName = fullTextureName;
	}
      else if( textureTag == "3TOD" )
	{
	  dot3TextureName = fullTextureName;
	}
      else if( textureTag == "PUKL" )
	{
	  lookupTextureName = fullTextureName;
	}
      else if( textureTag == "MVNE" )
	{
	  environmentTextureName = fullTextureName;
	}
      else if( textureTag == "KSAM" )
	{
	  maskTextureName = fullTextureName;
	}
      else if( textureTag == "BEUH" )
	{
	  hueTextureName = fullTextureName;
	}
      else if( textureTag == "CEPS" )
	{
	  specularTextureName = fullTextureName;
	}
      else if( textureTag == "MRNC" )
	{
	  //specularTextureName = fullTextureName;
	}
      else if( textureTag == "SIME" )
	{
	  //specularTextureName = fullTextureName;
	}
      else if( textureTag == "1PLA" )
	{
	  //specularTextureName = fullTextureName;
	}
      else if( textureTag == "2PLA" )
	{
	  //specularTextureName = fullTextureName;
	}
      else if( textureTag == "3PLA" )
	{
	  //specularTextureName = fullTextureName;
	}
      else if( textureTag == "ATED" )
	{
	  //specularTextureName = fullTextureName;
	}
      else if( textureTag == "ALTD" )
	{
	  //specularTextureName = fullTextureName;
	}
      else if( textureTag == "BLTD" )
	{
	  //specularTextureName = fullTextureName;
	}
      else if( textureTag == "TRID" )
	{
	  //specularTextureName = fullTextureName;
	}
      else if( textureTag == "DIRI" )
	{
	  //specularTextureName = fullTextureName;
	}
      else if( textureTag == "NRCS" )
	{
	  //specularTextureName = fullTextureName;
	}
      else if( textureTag == "0PER" )
	{
	  //specularTextureName = fullTextureName;
	}
      else if( textureTag == "LACD" )
	{
	  //specularTextureName = fullTextureName;
	}
      else if( textureTag == "YKS_" )
	{
	  //specularTextureName = fullTextureName;
	}
      else if( textureTag == "EBUC" )
	{
	  //specularTextureName = fullTextureName;
	}
      else if( textureTag == "PFFM" )
	{
	  //specularTextureName = fullTextureName;
	}
      else if( textureTag == "NEPO" )
	{
	  //specularTextureName = fullTextureName;
	}
      else
	{
	  std::cout << "Unknown texture tag: " << textureTag << std::endl;
	  throw std::exception();
	}

      texTag.push_back( textureTag );
    }

  if( txmSize == total )
    {
      std::cout << "Finished reading TXM" << std::endl;
    }
  else
    {
      std::cout << "FAILED in reading TXM" << std::endl;
      std::cout << "Read " << total << " out of " << txmSize
		<< std::endl;
    }

  return total;
}

unsigned int sht::readTCSS( std::istream &file )
{
  unsigned int tcssSize;

  unsigned int total = readFormHeader( file, "TCSS", tcssSize );
  tcssSize += 8;
  std::cout << "Found FORM TCSS: " << tcssSize-12 << " bytes"
	    << std::endl;

  std::string type;
  unsigned int size;
  total += readRecordHeader( file, type, size );
  if( type != "0000" )
    {
      std::cout << "Expected record of type 0000: " << type << std::endl;
      throw std::exception();
    }
  std::cout << "Found record " << type
	    << ": " << size << " bytes"
	    << std::endl;

  unsigned int num = size/5;

  for( unsigned int i = 0; i < num; ++i )
    {
      std::string texName;
      unsigned char texUnit;
      file.width( 4 );
      file >> texName;
      total += 4;
      file.read( (char*)&texUnit, 1 );
      total += 1;

      std::cout << "Texture type: " << texName << " "
		<< "Texture unit: " << (unsigned int)texUnit << std::endl;

      if( texName == "NIAM" )
	{
	  mainTextureUnit = texUnit;
	}
      else if( texName == "LMRN" )
	{
	  normalTextureUnit = texUnit;
	}
      else if( texName == "3TOD" )
	{
	  dot3TextureUnit = texUnit;
	}
      else if( texName == "PUKL" )
	{
	  lookupTextureUnit = texUnit;
	}
      else if( texName == "MVNE" )
	{
	  environmentTextureUnit = texUnit;
	}
      else if( texName == "KSAM" )
	{
	  maskTextureUnit = texUnit;
	}
      else if( texName == "BEUH" )
	{
	  hueTextureUnit = texUnit;
	}
      else if( texName == "CEPS" )
	{
	  specularTextureUnit = texUnit;
	}
      else if( texName == "MRNC" )
	{
	  //specularTextureUnit = texUnit;
	}
      else if( texName == "SIME" )
	{
	  //specularTextureUnit = texUnit;
	}
      else if( texName == "1PLA" )
	{
	  //specularTextureUnit = texUnit;
	}
      else if( texName == "2PLA" )
	{
	  //specularTextureUnit = texUnit;
	}
      else if( texName == "3PLA" )
	{
	  //specularTextureUnit = texUnit;
	}
      else if( texName == "ATED" )
	{
	  //specularTextureUnit = texUnit;
	}
      else if( texName == "ALTD" )
	{
	  //specularTextureUnit = texUnit;
	}
      else if( texName == "BLTD" )
	{
	  //specularTextureUnit = texUnit;
	}
      else if( texName == "TRID" )
	{
	  //specularTextureUnit = texUnit;
	}
      else if( texName == "DIRI" )
	{
	  //specularTextureUnit = texUnit;
	}
      else if( texName == "NRCS" )
	{
	  //specularTextureUnit = texUnit;
	}
      else if( texName == "0PER" )
	{
	  //specularTextureUnit = texUnit;
	}
      else if( texName == "LACD" )
	{
	  //specularTextureUnit = texUnit;
	}
      else if( texName == "YKS_" )
	{
	  //specularTextureUnit = texUnit;
	}
      else if( texName == "EBUC" )
	{
	  //specularTextureUnit = texUnit;
	}
      else if( texName == "PFFM" )
	{
	  //specularTextureUnit = texUnit;
	}
      else if( texName == "NEPO" )
	{
	  //specularTextureUnit = texUnit;
	}
      else
	{
	  std::cout << "Unknown texture tag: " << texName << std::endl;
	  throw std::exception();
	}
    }
    
  if( tcssSize == total )
    {
      std::cout << "Finished reading TCSS" << std::endl;
    }
  else
    {
      std::cout << "FAILED in reading TCSS" << std::endl;
      std::cout << "Read " << total << " out of " << tcssSize
		<< std::endl;
    }

  return total;
}

unsigned int sht::readTFNS( std::istream &file )
{
  unsigned int tfnsSize;
  unsigned int total = readFormHeader( file, "TFNS", tfnsSize );
  tfnsSize += 8;
  std::cout << "Found FORM TFNS: " << tfnsSize-12 << " bytes"
	    << std::endl;

  unsigned int size;
  std::string type;
  total += readRecordHeader( file, type, size );
  if( type != "0000" )
    {
      std::cout << "Expected record of type 0000: " << type << std::endl;
      throw std::exception();
    }
  std::cout << "Found record " << type
	    << ": " << size << " bytes"
	    << std::endl;

  total += readUnknown( file, size );

  if( tfnsSize == total )
    {
      std::cout << "Finished reading TFNS" << std::endl;
    }
  else
    {
      std::cout << "FAILED in reading TFNS" << std::endl;
      std::cout << "Read " << total << " out of " << tfnsSize
		<< std::endl;
    }

  return total;
}

unsigned int sht::readTSNS( std::istream &file )
{
  unsigned int tsnsSize;
  unsigned int total = readFormHeader( file, "TSNS", tsnsSize );
  tsnsSize += 8;
  std::cout << "Found FORM TSNS: " << tsnsSize-12 << " bytes"
	    << std::endl;

  unsigned int size;
  std::string type;
  total += readRecordHeader( file, type, size );
  if( type != "0000" )
    {
      std::cout << "Expected record of type 0000: " << type << std::endl;
      throw std::exception();
    }
  std::cout << "Found record " << type
	    << ": " << size << " bytes"
	    << std::endl;

  total += readUnknown( file, size );

  if( tsnsSize == total )
    {
      std::cout << "Finished reading TSNS" << std::endl;
    }
  else
    {
      std::cout << "FAILED in reading TSNS" << std::endl;
      std::cout << "Read " << total << " out of " << tsnsSize
		<< std::endl;
    }

  return total;
}

unsigned int sht::readARVS( std::istream &file )
{
  unsigned int arvsSize;
  unsigned int total = readFormHeader( file, "ARVS", arvsSize );
  arvsSize += 8;
  std::cout << "Found FORM ARVS: " << arvsSize-12 << " bytes"
	    << std::endl;

  unsigned int size;
  std::string type;
  total += readRecordHeader( file, type, size );
  if( type != "0000" )
    {
      std::cout << "Expected record of type 0000: " << type << std::endl;
      throw std::exception();
    }
  std::cout << "Found record " << type
	    << ": " << size << " bytes"
	    << std::endl;

  total += readUnknown( file, size );
    
  if( arvsSize == total )
    {
      std::cout << "Finished reading ARVS" << std::endl;
    }
  else
    {
      std::cout << "FAILED in reading ARVS" << std::endl;
      std::cout << "Read " << total << " out of " << arvsSize
		<< std::endl;
    }

  return total;
}

unsigned int sht::readEFCT( std::istream &file )
{
  unsigned int efctSize;
  std::string type;

  unsigned int total = readFormHeader( file, "EFCT", efctSize );
  efctSize += 8;
  std::cout << "Found FORM EFCT: " << efctSize-12 << " bytes"
	    << std::endl;

  unsigned int size;
  total += readFormHeader( file, "0001", size );
  std::cout << "Found FORM 0001: " << size-4 << " bytes"
	    << std::endl;

  total += readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected record of type DATA: " << type << std::endl;
      throw std::exception();
    }
  std::cout << "Found record " << type 
	    << ": " << size << " bytes" 
	    << std::endl;

  total += readUnknown( file, size );
    
  if( efctSize == total )
    {
      std::cout << "Finished reading EFCT" << std::endl;
    }
  else
    {
      std::cout << "FAILED in reading EFCT" << std::endl;
      std::cout << "Read " << total << " out of " << efctSize
		<< std::endl;
    }

  return total;
}

unsigned int sht::readNAME( std::istream &file )
{
  unsigned int nameSize;
  std::string type;
  // Read Effect file record
  unsigned int total = readRecordHeader( file, type, nameSize );
  nameSize += 8;
  if( type != "NAME" )
    {
      std::cout << "Expected record of type NAME: " << type << std::endl;
      return 0;
    }

  total += base::read( file, effectName );
  base::fixSlash( effectName );

  std::string fullEffectName = basePath + effectName;
  std::cout << "Effect file: " << fullEffectName << std::endl;

  if( nameSize == total )
    {
      std::cout << "Finished reading NAME" << std::endl;
    }
  else
    {
      std::cout << "FAILED in reading NAMESIZE" << std::endl;
      std::cout << "Read " << total << " out of " << nameSize
		<< std::endl;
    }

  return total;
}

void sht::getAmbient( float &r, float &g, float &b, float &a ) const
{
  r = ambient[0];
  g = ambient[1];
  b = ambient[2];
  a = ambient[3];
}

void sht::getDiffuse( float &r, float &g, float &b, float &a ) const
{
  r = diffuse[0];
  g = diffuse[1];
  b = diffuse[2];
  a = diffuse[3];
}

void sht::getSpecular( float &r, float &g, float &b, float &a ) const
{
  r = specular[0];
  g = specular[1];
  b = specular[2];
  a = specular[3];
}

void sht::getEmissive( float &r, float &g, float &b, float &a ) const
{
  r = emissive[0];
  g = emissive[1];
  b = emissive[2];
  a = emissive[3];
}

void sht::getShininess( float &shiny ) const
{
  shiny = shininess;
}

std::string sht::getMaterialName() const
{
  return materialName;
}

void sht::setMaterialName( const std::string newName )
{
  materialName = newName;
}

