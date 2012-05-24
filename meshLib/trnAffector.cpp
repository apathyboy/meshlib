/** -*-c++-*-
 *  \class  trnAffector
 *  \file   trnAffector.cpp
 *  \author Kenneth R. Sewell III

 meshLib is used for the parsing and exporting .trn models.
 Copyright (C) 2009 Kenneth R. Sewell III

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

#include <meshLib/trnAffector.hpp>
#include <cstdlib>

using namespace ml;

trnAffector::trnAffector()
{
}

trnAffector::~trnAffector()
{
}

void trnAffector::apply( const float &currentX,
			 const float &currentY,
			 float &data) const
{
}

unsigned int trnAffector::read( std::istream &file,
				const std::string &debugString )
{
  return 0;
}

//*****************************************************************************
// ACCN
affectorColorConstant::affectorColorConstant()
{
}

affectorColorConstant::~affectorColorConstant()
{
}

void affectorColorConstant::apply( const float &currentX,
				   const float &currentY,
				   float &data) const
{
}

unsigned int affectorColorConstant::read( std::istream &file,
					  const std::string &debugString )
{
  std::string dbgStr = debugString + "ACCN: ";
  unsigned int accnSize;
  unsigned int total = base::readFormHeader( file, "ACCN", accnSize );
  accnSize += 8;
  std::cout << debugString << "Found ACCN form" << std::endl;

  unsigned int size;
  std::string form, type;
  total += base::readFormHeader( file, form, size, type );
  if( form != "FORM" || type != "0000" )
    {
      std::cout << "Expected Form of type 0000: " << type << std::endl;
      std::exit( 0 );
    }
  std::cout << dbgStr << "Found 0000 form" << std::endl;

  total += readIHDR( file, dbgStr );

  // DATA record
  total += base::readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected DATA record: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found DATA record" << std::endl;

  total += base::read( file, u2 );
  total += base::read( file, u3 );
  total += base::read( file, u4 );
  total += base::read( file, u5 );

  std::cout << dbgStr << u2 << std::endl;;
  std::cout << dbgStr << (int)u3 << std::endl;;
  std::cout << dbgStr << (int)u4 << std::endl;;
  std::cout << dbgStr << (int)u5 << std::endl;;

  if( accnSize == total )
    {
      std::cout << debugString << "Finished reading ACCN" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading ACCN" << std::endl;
      std::cout << "Read " << total << " out of " << accnSize
		<< std::endl;
    }
  return total;
}

//*****************************************************************************
// ACRF
affectorColorRampFractal::affectorColorRampFractal()
{
}

affectorColorRampFractal::~affectorColorRampFractal()
{
}

void affectorColorRampFractal::apply( const float &currentX,
				      const float &currentY,
				      float &data) const
{
}

unsigned int affectorColorRampFractal::read( std::istream &file,
					     const std::string &debugString )
{
  std::string dbgStr = debugString + "ACRF: ";
  unsigned int acrfSize;
  unsigned int total = base::readFormHeader( file, "ACRF", acrfSize );
  acrfSize += 8;
  std::cout << debugString << "Found ACRF form" << std::endl;

  unsigned int size;
  total += base::readFormHeader( file, "0001", size );
  std::cout << dbgStr << "Found 0001 form" << std::endl;

  total += readIHDR( file, dbgStr );

  total += base::readFormHeader( file, "DATA", size );
  std::cout << dbgStr << "Found DATA form" << std::endl;

  // PARM record
  std::string type;
  total += base::readRecordHeader( file, type, size );
  if( type != "PARM" )
    {
      std::cout << "Expected PARM record: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found PARM record" << std::endl;

  total += base::read( file, u2 );
  total += base::read( file, u3 );

  total += base::read( file, name2 );
  base::fixSlash( name2 );

  std::cout << dbgStr << u2 << " "
	    << u3 << " "
	    << "'" << name2 << "'" << std::endl;

  if( acrfSize == total )
    {
      std::cout << debugString << "Finished reading ACRF" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading ACRF" << std::endl;
      std::cout << "Read " << total << " out of " << acrfSize
		<< std::endl;
    }
  return total;
}

//*****************************************************************************
// ACRH
affectorColorRampHeight::affectorColorRampHeight()
{
}

affectorColorRampHeight::~affectorColorRampHeight()
{
}

void affectorColorRampHeight::apply( const float &currentX,
				     const float &currentY,
				     float &data) const
{
}

unsigned int affectorColorRampHeight::read( std::istream &file,
					    const std::string &debugString )
{
  std::string dbgStr = debugString + "ACRH: ";
  unsigned int acrhSize;
  unsigned int total = base::readFormHeader( file, "ACRH", acrhSize );
  acrhSize += 8;
  std::cout << "Found ACRH form" << std::endl;

  unsigned int size;
  std::string form, type;
  total += base::readFormHeader( file, form, size, type );
  if( form != "FORM" || type != "0000" )
    {
      std::cout << "Expected Form of type 0000: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found 0000 form" << std::endl;

  total += readIHDR( file, dbgStr );

  // DATA record
  total += base::readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected DATA record: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found DATA record" << std::endl;

  total += base::read( file, u2 );
  total += base::read( file, u3 );
  total += base::read( file, u4 );
  total += base::read( file, name2 );

  std::cout << dbgStr << u2 << std::endl;
  std::cout << dbgStr << u3 << std::endl;
  std::cout << dbgStr << u4 << std::endl;
  std::cout << dbgStr << "'" << name2 << "'" << std::endl;

  if( acrhSize == total )
    {
      std::cout << debugString << "Finished reading ACRH" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading ACRH" << std::endl;
      std::cout << "Read " << total << " out of " << acrhSize
		<< std::endl;
    }
  return total;
}

//*****************************************************************************
// AENV
affectorEnvironment::affectorEnvironment()
{
}

affectorEnvironment::~affectorEnvironment()
{
}

void affectorEnvironment::apply( const float &currentX,
				 const float &currentY,
				 float &data) const
{
}

unsigned int affectorEnvironment::read( std::istream &file,
					const std::string &debugString )
{
  std::string dbgStr = debugString + "AENV: ";
  unsigned int aenvSize;

  // FORM AENV
  unsigned int total = base::readFormHeader( file, "AENV", aenvSize );
  aenvSize += 8;
  std::cout << debugString << "Found AENV form" << std::endl;

  // FORM 0001
  unsigned int size;
  total += base::readFormHeader( file, "0000", size );
  std::cout << dbgStr << "Found 0000 form" << std::endl;

  // IHDR
  total += readIHDR( file, dbgStr );

  // DATA
  std::string type;
  total += base::readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected record of type DATA: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found DATA record" << std::endl;

  total += base::read( file, u2 );
  total += base::read( file, u3 );
  total += base::read( file, u4 );

  std::cout << dbgStr << u2 << " "
	    << u3 << " "
	    << u4 << std::endl;
    
  if( aenvSize == total )
    {
      std::cout << debugString << "Finished reading AENV" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading AENV" << std::endl;
      std::cout << "Read " << total << " out of " << aenvSize
		<< std::endl;
    }
  return total;
}

//*****************************************************************************
// AEXC
affectorExclude::affectorExclude()
{
}

affectorExclude::~affectorExclude()
{
}

void affectorExclude::apply( const float &currentX,
			     const float &currentY,
			     float &data) const
{
}

unsigned int affectorExclude::read( std::istream &file,
				    const std::string &debugString )
{
  std::string dbgStr = debugString + "AEXC: ";
  unsigned int aexcSize;
  unsigned int total = base::readFormHeader( file, "AEXC", aexcSize );
  aexcSize += 8;
  std::cout << debugString << "Found AEXC form" << std::endl;

  unsigned int size;
  std::string form, type;
  total += base::readFormHeader( file, form, size, type );
  if( form != "FORM" || type != "0000" )
    {
      std::cout << "Expected Form of type 0000: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found 0000 form" << std::endl;

  total += readIHDR( file, dbgStr );

  // DATA record
  total += base::readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected DATA record: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found DATA record" << std::endl;

  if( aexcSize == total )
    {
      std::cout << debugString << "Finished reading AEXC" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading AEXC" << std::endl;
      std::cout << "Read " << total << " out of " << aexcSize
		<< std::endl;
    }
  return total;
}

//*****************************************************************************
// AFDF
affectorRadialFarConstant::affectorRadialFarConstant()
{
}

affectorRadialFarConstant::~affectorRadialFarConstant()
{
}

void affectorRadialFarConstant::apply( const float &currentX,
				       const float &currentY,
				       float &data) const
{
}

unsigned int affectorRadialFarConstant::read( std::istream &file,
					      const std::string &debugString )
{
  std::string dbgStr = debugString + "AFDF: ";
  unsigned int afdfSize;
  unsigned int total = base::readFormHeader( file, "AFDF", afdfSize );
  afdfSize += 8;
  std::cout << debugString << "Found AFDF form" << std::endl;

  unsigned int size;
  total += base::readFormHeader( file, "0002", size );
  std::cout << dbgStr << "Found 0002 form" << std::endl;

  total += readIHDR( file, dbgStr );

  // DATA record
  std::string type;
  total += base::readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected DATA record: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found DATA record" << std::endl;

  total += base::read( file, u2 );
  total += base::read( file, u3 );
  total += base::read( file, u4 );
  total += base::read( file, u5 );
  total += base::read( file, u6 );

  std::cout << dbgStr << u2 << std::endl;;
  std::cout << dbgStr << u3 << std::endl;;
  std::cout << dbgStr << u4 << std::endl;;
  std::cout << dbgStr << u5 << std::endl;;
  std::cout << dbgStr << u6 << std::endl;;

  if( afdfSize == total )
    {
      std::cout << debugString << "Finished reading AFDF" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading AFDF" << std::endl;
      std::cout << "Read " << total << " out of " << afdfSize
		<< std::endl;
    }
  return total;
}

//*****************************************************************************
// AFDN
affectorRadialConstant::affectorRadialConstant()
{
}

affectorRadialConstant::~affectorRadialConstant()
{
}

void affectorRadialConstant::apply( const float &currentX,
				    const float &currentY,
				    float &data) const
{
}

unsigned int affectorRadialConstant::read( std::istream &file,
					   const std::string &debugString )
{
  std::string dbgStr = debugString + "AFDN: ";
  unsigned int afdnSize;
  unsigned int total = base::readFormHeader( file, "AFDN", afdnSize );
  afdnSize += 8;
  std::cout << debugString << "Found AFDN form" << std::endl;

  unsigned int size;
  std::string form, type;
  total += base::readFormHeader( file, form, size, type );
  if( form != "FORM" || type != "0002" )
    {
      std::cout << "Expected Form of type 0002: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found 0002 form" << std::endl;

  total += readIHDR( file, dbgStr );

  // DATA record
  total += base::readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected DATA record: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found DATA record" << std::endl;

  total += base::read( file, u2 );
  total += base::read( file, u3 );
  total += base::read( file, u4 );
  total += base::read( file, u5 );
  total += base::read( file, u6 );

  std::cout << dbgStr << u2 << " ";
  std::cout << u3 << " ";
  std::cout << u4 << " ";
  std::cout << u5 << " ";
  std::cout << u6 << std::endl;;

  if( afdnSize == total )
    {
      std::cout << debugString << "Finished reading AFDN" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading AFDN" << std::endl;
      std::cout << "Read " << total << " out of " << afdnSize
		<< std::endl;
    }
  return total;
}

//*****************************************************************************
// AFSC
affectorFloraConstant::affectorFloraConstant()
{
}

affectorFloraConstant::~affectorFloraConstant()
{
}

void affectorFloraConstant::apply( const float &currentX,
				   const float &currentY,
				   float &data) const
{
}

unsigned int affectorFloraConstant::read( std::istream &file,
					  const std::string &debugString )
{
  std::string dbgStr = debugString + "AFSC: ";
  unsigned int afscSize;
  unsigned int total = base::readFormHeader( file, "AFSC", afscSize );
  afscSize += 8;
  std::cout << debugString << "Found AFSC form" << std::endl;

  unsigned int size;
  std::string form, type;
  total += base::readFormHeader( file, form, size, type );
  if( form != "FORM" || type != "0004" )
    {
      std::cout << "Expected Form of type 0004: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found 0004 form" << std::endl;

  total += readIHDR( file, dbgStr );

  // DATA record
  total += base::readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected DATA record: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found DATA record" << std::endl;

  total += base::read( file, u2 );
  total += base::read( file, u3 );
  total += base::read( file, u4 );
  total += base::read( file, u5 );
  total += base::read( file, u6 );

  std::cout << dbgStr << u2 << std::endl;;
  std::cout << dbgStr << u3 << std::endl;;
  std::cout << dbgStr << u4 << std::endl;;
  std::cout << dbgStr << u5 << std::endl;;
  std::cout << dbgStr << u6 << std::endl;;

  if( afscSize == total )
    {
      std::cout << debugString << "Finished reading AFSC" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading AFSC" << std::endl;
      std::cout << "Read " << total << " out of " << afscSize
		<< std::endl;
    }
  return total;
}

//*****************************************************************************
// AFSN
affectorFloraNonCollidableConstant::affectorFloraNonCollidableConstant()
{
}

affectorFloraNonCollidableConstant::~affectorFloraNonCollidableConstant()
{
}

void affectorFloraNonCollidableConstant::apply( const float &currentX,
						const float &currentY,
						float &data) const
{
}

unsigned int
affectorFloraNonCollidableConstant::read( std::istream &file,
					  const std::string &debugString )
{
  std::string dbgStr = debugString + "AFSN: ";
  unsigned int afsnSize;
  unsigned int total = base::readFormHeader( file, "AFSN", afsnSize );
  afsnSize += 8;
  std::cout << debugString << "Found AFSN form" << std::endl;

  unsigned int size;
  total += base::readFormHeader( file, "0004", size );
  std::cout << dbgStr << "Found 0004 form" << std::endl;

  total += readIHDR( file, dbgStr );

  // DATA record
  std::string type;
  total += base::readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected DATA record: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found DATA record" << std::endl;

  total += base::read( file, u2 );
  total += base::read( file, u3 );
  total += base::read( file, u4 );
  total += base::read( file, u5 );
  total += base::read( file, u6 );

  std::cout << dbgStr << u2 << std::endl;
  std::cout << dbgStr << u3 << std::endl;
  std::cout << dbgStr << u4 << std::endl;
  std::cout << dbgStr << u5 << std::endl;
  std::cout << dbgStr << u6 << std::endl;

  if( afsnSize == total )
    {
      std::cout << debugString << "Finished reading AFSN" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading AFSN" << std::endl;
      std::cout << "Read " << total << " out of " << afsnSize
		<< std::endl;
    }
  return total;
}

//*****************************************************************************
// AHCN
affectorHeightConstant::affectorHeightConstant()
{
}

affectorHeightConstant::~affectorHeightConstant()
{
}

void affectorHeightConstant::apply( const float &currentX,
				    const float &currentY,
				    float &data) const
{
  data += height;
}

unsigned int affectorHeightConstant::read( std::istream &file,
					   const std::string &debugString )
{
  std::string dbgStr = debugString + "AHCN: ";
  unsigned int ahcnSize;
  unsigned int total = base::readFormHeader( file, "AHCN", ahcnSize );
  ahcnSize += 8;
  std::cout << debugString << "Found AHCN form" << std::endl;

  unsigned int size;
  std::string form, type;
  total += base::readFormHeader( file, form, size, type );
  if( form != "FORM" || type != "0000" )
    {
      std::cout << "Expected Form of type 0000: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found 0000 form" << std::endl;

  total += readIHDR( file, dbgStr );

  total += base::readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected record of type DATA: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found DATA record" << std::endl;

  total += base::read( file, u2 );
  total += base::read( file, height );

  std::cout << dbgStr << u2 << std::endl;
  std::cout << dbgStr << "Height: " << height << std::endl;

  if( ahcnSize == total )
    {
      std::cout << debugString << "Finished reading AHCN" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading AHCN" << std::endl;
      std::cout << "Read " << total << " out of " << ahcnSize
		<< std::endl;
    }
  return total;
}

//*****************************************************************************
// AHFR

affectorHeightFractal::affectorHeightFractal()
{
}

affectorHeightFractal::~affectorHeightFractal()
{
}

void affectorHeightFractal::apply( const float &currentX,
				   const float &currentY,
				   float &data) const
{
  data += height;
}

unsigned int affectorHeightFractal::read( std::istream &file,
					  const std::string &debugString )
{
  std::string dbgStr = debugString + "AHFR: ";
  unsigned int ahfrSize;
  unsigned int total = base::readFormHeader( file, "AHFR", ahfrSize );
  ahfrSize += 8;
  std::cout << debugString << "Found AHFR form" << std::endl;

  std::string form, type;
  unsigned int size;
  total += base::readFormHeader( file, form, size, type );
  if( form != "FORM" || type != "0003" )
    {
      std::cout << "Expected Form of type 0003: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found 0003 form" << std::endl;

  total += readIHDR( file, dbgStr );

  total += base::readFormHeader( file, "DATA", size );
  std::cout << dbgStr << "Found DATA form" << std::endl;

  // PARM record
  total += base::readRecordHeader( file, type, size );
  if( type != "PARM" )
    {
      std::cout << "Expected PARM record: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found PARM record" << std::endl;

  total += base::read( file, fractalIndex );
  std::cout << dbgStr << "Fractal index: " << fractalIndex
	    << std::endl;;

  total += base::read( file, u2 );
  std::cout << dbgStr << u2 << std::endl;

  total += base::read( file, height );
  std::cout << dbgStr << "Height: " << height << std::endl;

  if( ahfrSize == total )
    {
      std::cout << debugString << "Finished reading AHFR" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading AHFR" << std::endl;
      std::cout << "Read " << total << " out of " << ahfrSize
		<< std::endl;
    }
  return total;
}

//*****************************************************************************
// AHTR
affectorHeightTerrace::affectorHeightTerrace()
{
}

affectorHeightTerrace::~affectorHeightTerrace()
{
}

void affectorHeightTerrace::apply( const float &currentX,
				   const float &currentY,
				   float &data) const
{
}

unsigned int affectorHeightTerrace::read( std::istream &file,
					  const std::string &debugString )
{
  std::string dbgStr = debugString + "AHTR: ";
  unsigned int ahtrSize;
  unsigned int total = base::readFormHeader( file, "AHTR", ahtrSize );
  ahtrSize += 8;
  std::cout << debugString << "Found AHTR form" << std::endl;

  unsigned int size;
  std::string form, type;
  total += base::readFormHeader( file, form, size, type );
  if( form != "FORM" || type != "0004" )
    {
      std::cout << "Expected Form of type 0004: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found 0004 form" << std::endl;

  total += readIHDR( file, dbgStr );

  // DATA record
  total += base::readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected DATA record: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found DATA record" << std::endl;

  total += base::read( file, u2 );
  total += base::read( file, u3 );

  std::cout << dbgStr << u2 << std::endl;;
  std::cout << dbgStr << u3 << std::endl;;

  if( ahtrSize == total )
    {
      std::cout << debugString << "Finished reading AHTR" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading AHTR" << std::endl;
      std::cout << "Read " << total << " out of " << ahtrSize
		<< std::endl;
    }
  return total;
}



//*****************************************************************************
// ARIV
affectorRiver::affectorRiver()
{
}

affectorRiver::~affectorRiver()
{
}

void affectorRiver::apply( const float &currentX,
			  const float &currentY,
			  float &data) const
{
}

unsigned int affectorRiver::read( std::istream &file,
				 const std::string &debugString )
{
  std::string dbgStr = debugString + "ARIV: ";
  unsigned int aroaSize;
  unsigned int total = base::readFormHeader( file, "ARIV", aroaSize );
  aroaSize += 8;
  std::cout << debugString << "Found ARIV form" << std::endl;
  unsigned int size;
  std::string form, type;
  total += base::readFormHeader( file, form, size, type );
  if( form != "FORM" || type != "0005" )
    {
      std::cout << "Expected Form of type 0005: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found 0005 form" << std::endl;

  total += readIHDR( file, dbgStr );

  // DATA form
  total += base::readFormHeader( file, "DATA", size );
  std::cout << dbgStr << "Found DATA form" << std::endl;

#if 0
  total += base::read( file, u2 );
  total += base::read( file, u3 );
  total += base::read( file, u4 );
  total += base::read( file, u5 );

  std::cout << dbgStr << u2 << std::endl;
  std::cout << dbgStr << u3 << std::endl;
  std::cout << dbgStr << u4 << std::endl;
  std::cout << dbgStr << u5 << std::endl;
#endif
  total += base::readUnknown( file, aroaSize-total );

  if( aroaSize == total )
    {
      std::cout << debugString << "Finished reading AROA" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading AROA" << std::endl;
      std::cout << "Read " << total << " out of " << aroaSize
		<< std::endl;
    }
  return total;
}

//*****************************************************************************
// AROA
affectorRoad::affectorRoad()
{
}

affectorRoad::~affectorRoad()
{
}

void affectorRoad::apply( const float &currentX,
			  const float &currentY,
			  float &data) const
{
}

unsigned int affectorRoad::read( std::istream &file,
				 const std::string &debugString )
{
  std::string dbgStr = debugString + "AROA: ";
  unsigned int aroaSize;
  unsigned int total = base::readFormHeader( file, "AROA", aroaSize );
  aroaSize += 8;
  std::cout << debugString << "Found AROA form" << std::endl;
  unsigned int size;
  std::string form, type;
  total += base::readFormHeader( file, form, size, type );
  if( form != "FORM" || type != "0005" )
    {
      std::cout << "Expected Form of type 0005: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found 0005 form" << std::endl;

  total += readIHDR( file, dbgStr );

  // DATA form
  total += base::readFormHeader( file, "DATA", size );
  std::cout << dbgStr << "Found DATA form" << std::endl;

#if 0
  total += base::read( file, u2 );
  total += base::read( file, u3 );
  total += base::read( file, u4 );
  total += base::read( file, u5 );

  std::cout << dbgStr << u2 << std::endl;
  std::cout << dbgStr << u3 << std::endl;
  std::cout << dbgStr << u4 << std::endl;
  std::cout << dbgStr << u5 << std::endl;
#endif
  total += base::readUnknown( file, aroaSize-total );

  if( aroaSize == total )
    {
      std::cout << debugString << "Finished reading AROA" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading AROA" << std::endl;
      std::cout << "Read " << total << " out of " << aroaSize
		<< std::endl;
    }
  return total;
}

//*****************************************************************************
// ASCN
affectorShaderConstant::affectorShaderConstant()
{
}

affectorShaderConstant::~affectorShaderConstant()
{
}

void affectorShaderConstant::apply( const float &currentX,
				    const float &currentY,
				    float &data) const
{
}

unsigned int affectorShaderConstant::read( std::istream &file,
					   const std::string &debugString )
{
  std::string dbgStr = debugString + "ASCN: ";
  unsigned int ascnSize;

  // FORM ASCN
  unsigned int total = base::readFormHeader( file, "ASCN", ascnSize );
  ascnSize += 8;
  std::cout << debugString << "Found ASCN form" << std::endl;

  // FORM 0001
  unsigned int size;
  std::string form, type;
  total += base::readFormHeader( file, form, size, type );
  if( form != "FORM" || type != "0001" )
    {
      std::cout << "Expected Form of type 0001: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found 0001 form" << std::endl;

  // IHDR
  total += readIHDR( file, dbgStr );

  // DATA
  total += base::readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected record of type DATA: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found DATA record" << std::endl;

  total += base::read( file, u2 );
  total += base::read( file, u3 );
  total += base::read( file, u4 );

  std::cout << dbgStr << u2 << " " << u3 << " " << u4 << std::endl;

  if( ascnSize == total )
    {
      std::cout << debugString << "Finished reading ASCN" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading ASCN" << std::endl;
      std::cout << "Read " << total << " out of " << ascnSize
		<< std::endl;
    }
  return total;
}

//*****************************************************************************
// ASRP
affectorShaderReplace::affectorShaderReplace()
{
}

affectorShaderReplace::~affectorShaderReplace()
{
}

void affectorShaderReplace::apply( const float &currentX,
				   const float &currentY,
				   float &data) const
{
}

unsigned int affectorShaderReplace::read( std::istream &file,
					  const std::string &debugString )
{
  std::string dbgStr = debugString + "ASRP: ";
  unsigned int asrpSize;
  unsigned int total = base::readFormHeader( file, "ASRP", asrpSize );
  asrpSize += 8;
  std::cout << debugString << "Found ASRP form" << std::endl;

  unsigned int size;
  std::string form, type;
  total += base::readFormHeader( file, form, size, type );
  if( form != "FORM" || type != "0001" )
    {
      std::cout << "Expected Form of type 0001: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found 0001 form" << std::endl;

  total += readIHDR( file, dbgStr );

  // DATA record
  total += base::readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected DATA record: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found DATA record" << std::endl;

  total += base::read( file, u2 );
  total += base::read( file, u3 );
  total += base::read( file, u4 );
  total += base::read( file, u5 );

  std::cout << dbgStr << u2 << std::endl;
  std::cout << dbgStr << u3 << std::endl;
  std::cout << dbgStr << u4 << std::endl;
  std::cout << dbgStr << u5 << std::endl;

  if( asrpSize == total )
    {
      std::cout << debugString << "Finished reading ASRP" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading ASRP" << std::endl;
      std::cout << "Read " << total << " out of " << asrpSize
		<< std::endl;
    }
  return total;
}

//*****************************************************************************
// FDIR
affectorFilterDirection::affectorFilterDirection()
{
}

affectorFilterDirection::~affectorFilterDirection()
{
}

void affectorFilterDirection::apply( const float &currentX,
				     const float &currentY,
				     float &data) const
{
}

unsigned int affectorFilterDirection::read( std::istream &file,
					    const std::string &debugString )
{
  std::string dbgStr = debugString + "FDIR: ";
  unsigned int fdirSize;
  unsigned int total = base::readFormHeader( file, "FDIR", fdirSize );
  fdirSize += 8;
  std::cout << "Found FDIR form" << std::endl;

  total += base::readUnknown( file, fdirSize-total );

  if( fdirSize == total )
    {
      std::cout << debugString << "Finished reading FDIR" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading FDIR" << std::endl;
      std::cout << "Read " << total << " out of " << fdirSize
		<< std::endl;
    }
  return total;
}

//*****************************************************************************
// FFRA
affectorFilterFractal::affectorFilterFractal()
{
}

affectorFilterFractal::~affectorFilterFractal()
{
}

void affectorFilterFractal::apply( const float &currentX,
				   const float &currentY,
				   float &data) const
{
}

unsigned int affectorFilterFractal::read( std::istream &file,
					  const std::string &debugString )
{
  std::string dbgStr = debugString + "FFRA: ";
  unsigned int ffraSize;
  unsigned int total = base::readFormHeader( file, "FFRA", ffraSize );
  ffraSize += 8;
  std::cout << debugString << "Found FFRA form" << std::endl;

  unsigned int size;
  std::string form, type;
  total += base::readFormHeader( file, form, size, type );
  if( form != "FORM" || type != "0005" )
    {
      std::cout << "Expected Form of type 0005: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found 0005 form" << std::endl;

  total += readIHDR( file, dbgStr );

  total += base::readFormHeader( file, "DATA", size );
  std::cout << dbgStr << "Found DATA form" << std::endl;

  // PARM record
  total += base::readRecordHeader( file, type, size );
  if( type != "PARM" )
    {
      std::cout << "Expected PARM record: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found PARM record" << std::endl;

  total += base::read( file, fractalFamily );
  std::cout << dbgStr << "Fractal family: " << fractalFamily << std::endl;

  total += base::read( file, featherType );
  std::cout << dbgStr << featherType << std::endl;;

  total += base::read( file, filterSeed );
  std::cout << dbgStr << "Filter seed: " << filterSeed << std::endl;;

  total += base::read( file, filterLow );
  std::cout << dbgStr << "Filter low: " << filterLow << std::endl;;

  total += base::read( file, filterHigh );
  std::cout << dbgStr << "Filter high: " << filterHigh << std::endl;;

  total += base::read( file, featherWidth );
  std::cout << dbgStr << "Feathering width: " << featherWidth << std::endl;;

  if( ffraSize == total )
    {
      std::cout << debugString << "Finished reading FFRA" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading FFRA" << std::endl;
      std::cout << "Read " << total << " out of " << ffraSize
		<< std::endl;
    }
  return total;
}

//*****************************************************************************
// FHGT
affectorFilterHeight::affectorFilterHeight()
{
}

affectorFilterHeight::~affectorFilterHeight()
{
}

void affectorFilterHeight::apply( const float &currentX,
				  const float &currentY,
				  float &data) const
{
}

unsigned int affectorFilterHeight::read( std::istream &file,
					 const std::string &debugString )
{
  std::string dbgStr = debugString + "FHGT: ";
  unsigned int fhgtSize;
  unsigned int total = base::readFormHeader( file, "FHGT", fhgtSize );
  fhgtSize += 8;
  std::cout << debugString << "Found FHGT form" << std::endl;

  unsigned int size;
  std::string form, type;
  total += base::readFormHeader( file, form, size, type );
  if( form != "FORM" || type != "0002" )
    {
      std::cout << "Expected Form of type 0002: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found 0002 form" << std::endl;

  total += readIHDR( file, dbgStr );

  total += base::readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected record of type DATA: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found DATA record" << std::endl;

  total += base::read( file, minHeight );
  std::cout << dbgStr << "Min height: " << minHeight << std::endl;

  total += base::read( file, maxHeight );
  std::cout << dbgStr << "Max height: " << maxHeight << std::endl;

  total += base::read( file, featherType );
  std::cout << dbgStr << "Feathering type: " << featherType << std::endl;

  total += base::read( file, featherWidth );
  std::cout << dbgStr << "Feathering width: " << featherWidth << std::endl;

  if( fhgtSize == total )
    {
      std::cout << debugString << "Finished reading FHGT" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading FHGT" << std::endl;
      std::cout << "Read " << total << " out of " << fhgtSize
		<< std::endl;
    }
  return total;
}

//*****************************************************************************
// FSHD
affectorFilterShader::affectorFilterShader()
{
}

affectorFilterShader::~affectorFilterShader()
{
}

void affectorFilterShader::apply( const float &currentX,
				  const float &currentY,
				  float &data) const
{
}

unsigned int affectorFilterShader::read( std::istream &file,
					 const std::string &debugString )
{
  std::string dbgStr = debugString + "FSHD: ";
  unsigned int fshdSize;
  unsigned int total = base::readFormHeader( file, "FSHD", fshdSize );
  fshdSize += 8;
  std::cout << debugString << "Found FSHD form" << std::endl;

  unsigned int size;
  std::string form, type;
  total += base::readFormHeader( file, form, size, type );
  if( form != "FORM" || type != "0000" )
    {
      std::cout << "Expected Form of type 0000: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found 0000 form" << std::endl;

  total += readIHDR( file, dbgStr );

  // DATA record
  total += base::readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected DATA record: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found DATA record" << std::endl;

  total += base::read( file, u2 );
  std::cout << dbgStr << u2 << std::endl;;

  if( fshdSize == total )
    {
      std::cout << debugString << "Finished reading FSHD" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading FSHD" << std::endl;
      std::cout << "Read " << total << " out of " << fshdSize
		<< std::endl;
    }
  return total;
}

//*****************************************************************************
// FSLP
affectorFilterSlope::affectorFilterSlope()
{
}

affectorFilterSlope::~affectorFilterSlope()
{
}

void affectorFilterSlope::apply( const float &currentX,
				 const float &currentY,
				 float &data) const
{
}

unsigned int affectorFilterSlope::read( std::istream &file,
					const std::string &debugString )
{
  std::string dbgStr = debugString + "FSLP: ";
  unsigned int fslpSize;
  unsigned int total = base::readFormHeader( file, "FSLP", fslpSize );
  fslpSize += 8;
  std::cout << dbgStr << "Found FSLP form" << std::endl;

  unsigned int size;
  std::string form, type;
  total += base::readFormHeader( file, form, size, type );
  if( form != "FORM" || type != "0002" )
    {
      std::cout << "Expected Form of type 0002: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found 0002 form" << std::endl;

  total += readIHDR( file, dbgStr );

  // DATA record
  total += base::readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected DATA record: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found DATA record" << std::endl;

  total += base::read( file, u2 );
  std::cout << dbgStr << u2 << std::endl;;

  total += base::read( file, u3 );
  std::cout << dbgStr << u3 << std::endl;;

  total += base::read( file, u4 );
  std::cout << dbgStr << u4 << std::endl;;

  total += base::read( file, u5 );
  std::cout << dbgStr << u5 << std::endl;;

  if( fslpSize == total )
    {
      std::cout << debugString << "Finished reading FSLP" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading FSLP" << std::endl;
      std::cout << "Read " << total << " out of " << fslpSize
		<< std::endl;
    }
  return total;
}

//*****************************************************************************

unsigned int trnAffector::readIHDR( std::istream &file,
				    const std::string &debugString )
{
  std::string dbgStr = debugString + "IHDR: ";
  unsigned int ihdrSize;

  unsigned int total = base::readFormHeader( file, "IHDR", ihdrSize );
  ihdrSize += 8;
  std::cout << debugString << "Found IHDR form" << std::endl;

  unsigned int size;
  total += base::readFormHeader( file, "0001", size );
  std::cout << dbgStr << "Found 0001 form" << std::endl;

  std::string type;
  total += base::readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected record of type DATA: " << type << std::endl;
      exit( 0 );
    }
  std::cout << dbgStr << "Found DATA record" << std::endl;


  total += base::read( file, u1 );

  total += base::read( file, name );
  std::cout << dbgStr << u1 << " " << name << std::endl;

  if( ihdrSize == total )
    {
      std::cout << debugString << "Finished reading IHDR" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading IHDR" << std::endl;
      std::cout << "Read " << total << " out of " << ihdrSize
                << std::endl;
    }
  return total;
}



