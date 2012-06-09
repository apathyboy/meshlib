/** -*-c++-*-
 *  \class  prto
 *  \file   prto.cpp
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
#include <meshLib/prto.hpp>

#include <iostream>
#include <bitset>
#include <cstdlib>

using namespace ml;

prto::prto()
{
}

prto::~prto()
{
}

unsigned int prto::readPRTO( std::istream &file, std::string path )
{
  basePath = path;
  std::string form;
  unsigned int prtoSize;
  std::string type;

  unsigned int total = readFormHeader( file, "PRTO", prtoSize );
  prtoSize += 8;
  std::cout << "Found PRTO form"
	    << ": " << prtoSize-12 << " bytes"
	    << std::endl;

  unsigned int size;
  total += readFormHeader( file, form, size, type );
  if( form != "FORM" )
    {
      std::cout << "Expected FORM: " << form << std::endl;
      throw std::exception();
    }
  std::cout << "Found " << form << " " << type
	    << ": " << size-4 << " bytes"
	    << std::endl;

  total += readDATA( file );
  total += readPRTS( file );
  total += readCELS( file );
  total += readPGRF( file );
  total += readCRC( file );

  if( prtoSize == total )
    {
      std::cout << "Finished reading PRTO" << std::endl;
    }
  else
    {
      std::cout << "FAILED in reading PRTO" << std::endl;
      std::cout << "Read " << total << " out of " << prtoSize
		<< std::endl;
    }
    
  return total;
}

unsigned int prto::readDATA( std::istream &file )
{
    unsigned int dataSize;
    std::string type;

    unsigned int total = readRecordHeader( file, type, dataSize );
    dataSize += 8;
    if( type != "DATA" )
    {
        std::cout << "Expected record of type DATA: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found record " << type 
	      << ": "
	      << dataSize-8 << " bytes"
	      << std::endl;

    total += base::read( file, numPortals );
    total += base::read( file, numCells );

    std::cout << "Num portals: " << numPortals << std::endl;
    std::cout << "Num cells: " << numCells << std::endl;

    if( dataSize == total )
    {
	std::cout << "Finished reading DATA" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading DATA" << std::endl;
	std::cout << "Read " << total << " out of " << dataSize
                  << std::endl;
    }

    return total;
}

unsigned int prto::readLGHT( std::istream &file )
{
    std::string form;
    unsigned int lghtSize;
    std::string type;

    unsigned int total = readRecordHeader( file, type, lghtSize );
    lghtSize += 8;
    if( type != "LGHT" )
    {
        std::cout << "Expected record of type LGHT: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found record " << type 
	      << ": "
	      << lghtSize-8 << " bytes"
	      << std::endl;

    unsigned int numLights;
    total += base::read( file, numLights );
    std::cout << "Num lights: " << numLights << std::endl;

    ml::matrix3 mat;
    ml::vector3 vec;

    unsigned char x;
    float z;
    for( unsigned int i = 0; i < numLights; ++i )
      {
	std::cout << "Light: " << i << std::endl;
	total += base::read( file, x );
	std::cout << (unsigned int)x << std::endl;
	
	//
	total += base::read( file, z );
	std::cout << z << " ";
	
	total += base::read( file, z );
	std::cout << z << " ";
	
	total += base::read( file, z );
	std::cout << z << " ";
	
	total += base::read( file, z );
	std::cout << z << std::endl;

	//
	total += base::read( file, z );
	std::cout << z << " ";
	
	total += base::read( file, z );
	std::cout << z << " ";
	
	total += base::read( file, z );
	std::cout << z << " ";
	
	total += base::read( file, z );
	std::cout << z << std::endl;

	total += model::readMatrixAndPosition( file, mat, vec );
	std::cout << "Matrix: " << std::endl;
	mat.print();

	std::cout << "Position: ";
	vec.print();
	
	total += base::read( file, z );
	std::cout << z << " ";
	
	total += base::read( file, z );
	std::cout << z << " ";
	
	total += base::read( file, z );
	std::cout << z << std::endl;
      }

    if( lghtSize == total )
    {
	std::cout << "Finished reading LGHT" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading LGHT" << std::endl;
	std::cout << "Read " << total << " out of " << lghtSize
                  << std::endl;
    }

    return total;
}

unsigned int prto::readPRTS( std::istream &file )
{
    unsigned int prtsSize;
    std::string type;

    unsigned int total = readFormHeader( file, "PRTS", prtsSize );
    prtsSize += 8;
    std::cout << "Found FORM " << type
	      << ": " << prtsSize-12 << " bytes"
	      << std::endl;

    unsigned int size;
    std::string form;
    for( unsigned int i = 0; i < numPortals; ++i )
      {
	// Peek at next record, but keep file at same place.
	peekHeader( file, form, size, type );

	if( "PRTL" == form )
	  {
	    std::cout << std::endl;
	    std::cout << "PRTL " << i << std::endl;

	    total += readPRTLRecord( file );
	  }
	else if( "IDTL" == type )
	  {
	    std::vector<vector3> vec;
	    std::vector<unsigned int> index;
	    total += model::readIDTL( file, vec, index );
	  }
      }

    if( prtsSize == total )
    {
	std::cout << "Finished reading PRTS" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading PRTS" << std::endl;
	std::cout << "Read " << total << " out of " << prtsSize
                  << std::endl;
    }

    return total;
}

unsigned int prto::readCELS( std::istream &file )
{
    unsigned int celsSize;
    std::string type;

    unsigned int total = readFormHeader( file, "CELS", celsSize );
    celsSize += 8;
    std::cout << "Found FORM " << type
	      << ": " << celsSize-12 << " bytes"
	      << std::endl;

    for( unsigned int i = 0; i < numCells; ++i )
      {
	std::cout << std::endl;
	std::cout << "CELL " << i << std::endl;
	total += readCELL( file );
      }

    if( celsSize == total )
    {
	std::cout << "Finished reading CELS" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading CELS" << std::endl;
	std::cout << "Read " << total << " out of " << celsSize
                  << std::endl;
    }

    return total;
}

unsigned int prto::readPRTLRecord( std::istream &file )
{
    unsigned int prtlSize;
    std::string type;

    unsigned int total = readRecordHeader( file, type, prtlSize );
    prtlSize += 8;
    if( type != "PRTL" )
    {
        std::cout << "Expected record of type PRTL: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found record " << type 
	      << ": "
	      << prtlSize-8 << " bytes"
	      << std::endl;

    unsigned int numVerts;
    total += base::read( file, numVerts );
    std::cout << "NumVerts: " << numVerts << std::endl;

    float x, y, z;
    for( unsigned int i = 0; i < numVerts; ++i )
      {
	total += base::read( file, x );
	total += base::read( file, y );
	total += base::read( file, z );
#if 0
	std::cout << "vert: " << x << ", "
		  << y << ", " << z
		  << std::endl;
#endif
      }

    if( prtlSize == total )
    {
	std::cout << "Finished reading PRTL" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading PRTL" << std::endl;
	std::cout << "Read " << total << " out of " << prtlSize
                  << std::endl;
    }

    return total;
}

unsigned int prto::readCELL( std::istream &file )
{
    std::string form;
    unsigned int cellSize;
    std::string type;

    unsigned int total = readFormHeader( file, "CELL", cellSize );
    cellSize += 8;
    std::cout << "Found FORM " << type
	      << ": " << cellSize-12 << " bytes"
	      << std::endl;

    unsigned int size;
    total += readFormHeader( file, form, size, type );
    if( form != "FORM")
    {
	std::cout << "Expected FORM not: " << form << std::endl;
	throw std::exception();
    }
    std::cout << "Found " << form << " " << type
	      << ": " << size-4 << " bytes"
	      << std::endl;

    unsigned int numCellPortals;
    total += readCELLDATA( file, numCellPortals );

    while( total < cellSize )
      {
	// Peek at next record, but keep file at same place.
	peekHeader( file, form, size, type );

	if( "CMSH" == type )
	  {
	    total += readCMSH( file );
	  }
	else if( "CMPT" == type )
	  {
	    total += readCMPT( file );
	  }
	else if( "NULL" == type )
	  {
	    total += readFormHeader( file, form, size, type );
	  }
	else if( "PRTL" == type )
	  {
	    ml::matrix3 mat;
	    ml::vector3 vec;
	    total += readPRTL( file, mat, vec );
	  }
	else if( "EXBX" == type )
	  {
	    float cx, cy, cz, radius;
	    box box1;
	    total += readEXBX( file, cx, cy, cz, radius, box1 );
	    bbox.push_back( box1 );
	  }
	else if( "XCYL" == type )
	  {
	    float u1, u2, u3, u4, u5;
	    total += readXCYL( file, u1, u2, u3, u4, u5 );
	  }
	else if( "LGHT" == form )
	  {
	    total += readLGHT( file );
	  }
	else if( "DTAL" == type )
	  {
	    total += readDTAL( file );
	  }
	else
	  {
	    std::cout << "Unexpected type: " << type << std::endl;
	    throw std::exception();
	  }
      }
 
    if( cellSize == total )
    {
	std::cout << "Finished reading CELL" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading CELL" << std::endl;
	std::cout << "Read " << total << " out of " << cellSize
                  << std::endl;
    }

    return total;
}

unsigned int prto::readCELLDATA( std::istream &file,
				 unsigned int &numCellPortals )
{
    unsigned int dataSize;
    std::string type;

    unsigned int total = readRecordHeader( file, type, dataSize );
    dataSize += 8;
    if( type != "DATA" )
    {
        std::cout << "Expected record of type DATA: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found record " << type 
	      << ": "
	      << dataSize-8 << " bytes"
	      << std::endl;

    ml::cell newCell;

    total += base::read( file, numCellPortals );
    std::cout << "Num portals in this cell: " << numCellPortals << std::endl;

    unsigned char u1;
    total += base::read( file, u1 );
    newCell.setUnknown1( u1 );
    std::cout << "???: " << (unsigned int)u1 << std::endl;

    std::string cellName;
    total += base::read( file, cellName );
    newCell.setName( cellName );
    std::cout << "Cell name: " << cellName << std::endl;

    std::string cellModel;
    total += base::read( file, cellModel );
    newCell.setModelFilename( cellModel );
    std::cout << "Cell model: " << cellModel << std::endl;

    unsigned char hasFloor;
    total += base::read( file, hasFloor );
    newCell.setHasFloor( 0 < hasFloor );
    std::cout << "Has floor: " << (unsigned int)hasFloor << std::endl;

    if( hasFloor > 0 )
      {
	std::string cellFloor;
	total += base::read( file, cellFloor );
	newCell.setFloorFilename( cellFloor );
	std::cout << "Cell floor: " << cellFloor << std::endl;
      }
    
    if( dataSize == total )
      {
	cells.push_back( newCell );
	std::cout << "Finished reading DATA" << std::endl;
      }
    else
      {
	std::cout << "FAILED in reading DATA" << std::endl;
	std::cout << "Read " << total << " out of " << dataSize
                  << std::endl;
      }
    
    return total;
}

unsigned int prto::readPRTL( std::istream &file,
			     ml::matrix3 &mat, 
			     ml::vector3 &vec )
{
    std::string form;
    unsigned int prtlSize;
    std::string type;

    unsigned int total = readFormHeader( file, "PRTL", prtlSize );
    prtlSize += 8;
    std::cout << "Found FORM " << type
	      << ": " << prtlSize-12 << " bytes"
	      << std::endl;

    unsigned int size;
    total += readRecordHeader( file, type, size );
    if( type != "0004" && type != "0005" )
    {
        std::cout << "Expected record of type 0004: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found record " << type
	      << ": " << size << " bytes"
	      << std::endl;

    unsigned char y;
    unsigned int z;

    total += base::read( file, y );
    std::cout << (unsigned int)y << std::endl;
    
    total += base::read( file, z );
    std::cout << "Portal geometry index?: " << z << std::endl;
    
    total += base::read( file, y );
    std::cout << (unsigned int)y << std::endl;
    
    total += base::read( file, z );
    std::cout << "Adjacent cell: " << z << std::endl;
    
    std::string name;
    total += base::read( file, name );
    std::cout << "'" << name << "'" << std::endl;

    total += base::read( file, y );
    std::cout << (unsigned int)y << std::endl;

    total += model::readMatrixAndPosition( file, mat, vec );
    std::cout << "Matrix: " << std::endl;
    mat.print();
    
    std::cout << "Position: ";
    vec.print();
	
    if( prtlSize == total )
    {
	std::cout << "Finished reading PRTL" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading PRTL" << std::endl;
	std::cout << "Read " << total << " out of " << prtlSize
                  << std::endl;
    }

    return total;
}

unsigned int prto::readPGRF( std::istream &file )
{
    unsigned int pgrfSize;
    std::string type;

    unsigned int total = readFormHeader( file, "PGRF", pgrfSize );
    pgrfSize += 8;
    std::cout << "Found FORM " << type
	      << ": " << pgrfSize-12 << " bytes"
	      << std::endl;

    unsigned int size;
    std::string form;
    total += readFormHeader( file, form, size, type );
    if( form != "FORM")
    {
	std::cout << "Expected FORM not: " << form << std::endl;
	throw std::exception();
    }
    std::cout << "Found " << form << " " << type
	      << ": " << size-4 << " bytes"
	      << std::endl;

    total += readMETA( file );
    total += readPNOD( file );
    total += readPEDG( file );
    total += readECNT( file );
    total += readESTR( file );

    if( pgrfSize == total )
    {
	std::cout << "Finished reading PGRF" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading PGRF" << std::endl;
	std::cout << "Read " << total << " out of " << pgrfSize
                  << std::endl;
    }

    return total;
}

unsigned int prto::readCRC( std::istream &file )
{
    std::string form;
    unsigned int crcSize;
    std::string type;

    unsigned int total = readRecordHeader( file, type, crcSize );
    crcSize += 8;
    if( type != "CRC " )
    {
        std::cout << "Expected record of type CRC: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found record " << type 
	      << ": "
	      << crcSize-8 << " bytes"
	      << std::endl;

    total += base::read( file, crc );
    std::cout << "CRC: 0x" << std::hex << crc
	      << std::dec << std::endl;

    if( crcSize == total )
    {
	std::cout << "Finished reading CRC" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading CRC" << std::endl;
	std::cout << "Read " << total << " out of " << crcSize
                  << std::endl;
    }

    return total;
}

unsigned int prto::readMETA( std::istream &file )
{
    unsigned int metaSize;
    std::string type;

    unsigned int total = readRecordHeader( file, type, metaSize );
    metaSize += 8;
    if( type != "META" )
    {
        std::cout << "Expected record of type META: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found record " << type 
	      << ": "
	      << metaSize-8 << " bytes"
	      << std::endl;

    unsigned int x;
    total += base::read( file, x );
    std::cout << "X: " << x << std::endl;

    if( metaSize == total )
    {
	std::cout << "Finished reading META" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading META" << std::endl;
	std::cout << "Read " << total << " out of " << metaSize
                  << std::endl;
    }

    return total;
}

unsigned int prto::readPNOD( std::istream &file )
{
    unsigned int pnodSize;
    std::string type;

    unsigned int total = readRecordHeader( file, type, pnodSize );
    pnodSize += 8;
    if( type != "PNOD" )
    {
        std::cout << "Expected record of type PNOD: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found record " << type 
	      << ": "
	      << pnodSize-8 << " bytes"
	      << std::endl;

    unsigned int num;
    total += base::read( file, num );
    std::cout << "Num: " << num << std::endl;

    unsigned int x;
    float y;
    for( unsigned int i = 0; i < num; ++i )
      {
	total += base::read( file, x );
	std::cout << "Portal number: " << x << std::endl;

	total += base::read( file, x );
	std::cout << std::hex << "0x" << x << std::dec << std::endl;

	total += base::read( file, x );
	std::cout << "???: " << x << std::endl;

	total += base::read( file, x );
	std::cout << "???: " << x << std::endl;

	total += base::read( file, y );
	std::cout << y << std::endl;

	total += base::read( file, y );
	std::cout << y << std::endl;

	total += base::read( file, y );
	std::cout << y << std::endl;

	total += base::read( file, x );
	std::cout << x << std::endl;
      }

    if( pnodSize == total )
    {
	std::cout << "Finished reading PNOD" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading PNOD" << std::endl;
	std::cout << "Read " << total << " out of " << pnodSize
                  << std::endl;
    }

    return total;
}

unsigned int prto::readPEDG( std::istream &file )
{
    unsigned int pedgSize;
    std::string type;

    unsigned int total = readRecordHeader( file, type, pedgSize );
    pedgSize += 8;
    if( type != "PEDG" )
    {
        std::cout << "Expected record of type PEDG: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found record " << type 
	      << ": "
	      << pedgSize-8 << " bytes"
	      << std::endl;

    unsigned int num;
    total += base::read( file, num );
    std::cout << "Num: " << num << std::endl;

    unsigned int x;
    for( unsigned int i = 0; i < num; ++i )
      {
	total += base::read( file, x );
	std::cout << x << " ";

	total += base::read( file, x );
	std::cout << x << " ";

	total += base::read( file, x );
	std::cout << x << " ";

	total += base::read( file, x );
	std::cout << x << std::endl;
      }

    if( pedgSize == total )
    {
	std::cout << "Finished reading PEDG" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading PEDG" << std::endl;
	std::cout << "Read " << total << " out of " << pedgSize
                  << std::endl;
    }

    return total;
}

unsigned int prto::readECNT( std::istream &file )
{
    unsigned int ecntSize;
    std::string type;

    unsigned int total = readRecordHeader( file, type, ecntSize );
    ecntSize += 8;
    if( type != "ECNT" )
    {
        std::cout << "Expected record of type ECNT: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found record " << type 
	      << ": "
	      << ecntSize-8 << " bytes"
	      << std::endl;

    unsigned int num;
    total += base::read( file, num );
    std::cout << "Num: " << num << std::endl;

    unsigned int x;
    for( unsigned int i = 0; i < num; ++i )
      {
	total += base::read( file, x );
	std::cout << "Entry points for cell "
		  << i << ": " << x << std::endl;
      }

    if( ecntSize == total )
    {
	std::cout << "Finished reading ECNT" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading ECNT" << std::endl;
	std::cout << "Read " << total << " out of " << ecntSize
                  << std::endl;
    }

    return total;
}

unsigned int prto::readESTR( std::istream &file )
{
    unsigned int estrSize;
    std::string type;

    unsigned int total = readRecordHeader( file, type, estrSize );
    estrSize += 8;
    if( type != "ESTR" )
    {
        std::cout << "Expected record of type ESTR: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found record " << type 
	      << ": "
	      << estrSize-8 << " bytes"
	      << std::endl;

    unsigned int num;
    total += base::read( file, num );
    std::cout << "Num: " << num << std::endl;

    unsigned int x;
    for( unsigned int i = 0; i < num; ++i )
      {
	total += base::read( file, x );
	std::cout << x << std::endl;
      }

    if( estrSize == total )
    {
	std::cout << "Finished reading ESTR" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading ESTR" << std::endl;
	std::cout << "Read " << total << " out of " << estrSize
                  << std::endl;
    }

    return total;
}



