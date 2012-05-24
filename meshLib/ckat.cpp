/** -*-c++-*-
 *  \class  ckat
 *  \file   ckat.cpp
 *  \author Kenneth R. Sewell III

 meshLib is used for the parsing and exporting .msh models.
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
#include <meshLib/ckat.hpp>

#include <iostream>
#include <cstdlib>

using namespace ml;

ckat::ckat()
{
}

ckat::~ckat()
{
}

unsigned int ckat::readCKAT( std::istream &file, std::string path )
{
  basePath = path;
  unsigned int ckatSize;
  unsigned int total = readFormHeader( file, "CKAT", ckatSize );
  ckatSize += 8;
  std::cout << "Found CKAT form"
	    << ": " << ckatSize-12 << " bytes"
	    << std::endl;

  unsigned int size;
  std::string form, type;
  total += readFormHeader( file, form, size, type );
  if( form != "FORM" )
    {
      std::cout << "Expected FORM: " << form << std::endl;
      exit( 0 );
    }
  std::cout << "Found " << form << " " << type
	    << ": " << size-4 << " bytes"
	    << std::endl;

  total += readINFO( file );
  total += readXFRM( file );
  if( numQCHN > 0 )
    {
      total += readAROT( file );
    }
  total += readSROT( file );
  total += readATRN( file );
  total += readSTRN( file );
  if( ckatSize > total )
    {
      total += readMSGS( file );
    }

  if( ckatSize > total )
    {
      total += readLOCT( file );
    }

  if( ckatSize == total )
    {
      std::cout << "Finished reading CKAT" << std::endl;
    }
  else
    {
      std::cout << "FAILED in reading CKAT" << std::endl;
      std::cout << "Read " << total << " out of " << ckatSize
		<< std::endl;
    }
    
  return total;
}

unsigned int ckat::readINFO( std::istream &file )
{
    std::string type;
    unsigned int infoSize;
    unsigned int total = readRecordHeader( file, type, infoSize );
    infoSize += 8;
    if( type != "INFO" )
    {
        std::cout << "Expected record of type INFO: " << type << std::endl;
        exit( 0 );
    }
    std::cout << "Found " << type << std::endl;

    float u1;
    short u2;
    total += base::read( file, u1 );
    total += base::read( file, u2 );
    total += base::read( file, numXFIN );
    total += base::read( file, numQCHN );
    total += base::read( file, numSROT );
    total += base::read( file, numCHNL );
    total += base::read( file, numSTRN );
    
    std::cout << std::fixed << u1 << std::endl;
	      std::cout << u2 << std::endl;
	      std::cout << "Num XFIN: " << numXFIN << std::endl;
	      std::cout << "Num QCHN: " << numQCHN << std::endl;
	      std::cout << "Num SROT: " << numSROT << std::endl;
	      std::cout << "Num CHNL: " << numCHNL << std::endl;
	      std::cout << "Num STRN: " << numSTRN << std::endl;

    if( infoSize == total )
    {
        std::cout << "Finished reading INFO" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading INFO" << std::endl;
        std::cout << "Read " << total << " out of " << infoSize
                  << std::endl;
     }

    return total;
}

unsigned int ckat::readXFRM( std::istream &file )
{
    std::string type;
    unsigned int xfrmSize;
    unsigned int total = readFormHeader( file, "XFRM", xfrmSize );
    xfrmSize += 8;
    std::cout << "Found XFRM form"
	      << ": " << xfrmSize-12 << " bytes"
	      << std::endl;

    for( unsigned short i = 0; i < numXFIN; ++i )
      {
	total += readXFIN( file );
      }
    //total += readUnknown( file, xfrmSize - total );
    
    if( xfrmSize == total )
    {
        std::cout << "Finished reading XFRM" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading XFRM" << std::endl;
        std::cout << "Read " << total << " out of " << xfrmSize
                  << std::endl;
     }

    return total;
}

unsigned int ckat::readAROT( std::istream &file )
{
    std::string type;
    unsigned int arotSize;
    unsigned int total = readFormHeader( file, "AROT", arotSize );
    arotSize += 8;
    std::cout << "Found AROT form"
	      << ": " << arotSize-12 << " bytes"
	      << std::endl;

    for( unsigned short i = 0; i < numQCHN; ++i )
      {
	total += readQCHN( file );
      }
    
    if( arotSize == total )
    {
        std::cout << "Finished reading AROT" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading AROT" << std::endl;
        std::cout << "Read " << total << " out of " << arotSize
                  << std::endl;
     }

    return total;
}

unsigned int ckat::readSROT( std::istream &file )
{
    std::string type;
    unsigned int srotSize;
    unsigned int total = readRecordHeader( file, type, srotSize );
    srotSize += 8;
    if( type != "SROT" )
    {
        std::cout << "Expected record of type SROT: " << type << std::endl;
        exit( 0 );
    }
    std::cout << "Found " << type << ": " << srotSize-8 << " bytes"
	      << std::endl;

    for( unsigned int i = 0; i < numSROT; ++i )
      {
	unsigned char u3;
	total += base::read( file, u3 );
	std::cout << (u3/255.0) << " ";

	total += base::read( file, u3 );
	std::cout << (u3/255.0) << " ";

	total += base::read( file, u3 );
	std::cout << (u3/255.0) << " ";

	float u1;
	total += base::read( file, u1 );
	std::cout << u1 << std::endl;

      }

    //total += readUnknown( file, srotSize - total );

    if( srotSize == total )
    {
        std::cout << "Finished reading SROT" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading SROT" << std::endl;
        std::cout << "Read " << total << " out of " << srotSize
                  << std::endl;
     }

    return total;
}

unsigned int ckat::readATRN( std::istream &file )
{
    std::string type;
    unsigned int atrnSize;
    unsigned int total = readFormHeader( file, "ATRN", atrnSize );
    atrnSize += 8;
    std::cout << "Found ATRN form"
	      << ": " << atrnSize-12 << " bytes"
	      << std::endl;

    for( unsigned int i = 0; i < numCHNL; ++i )
      {
	total += readCHNL( file );
      }
    //total += readUnknown( file, atrnSize - total );
    
    if( atrnSize == total )
    {
        std::cout << "Finished reading ATRN" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading ATRN" << std::endl;
        std::cout << "Read " << total << " out of " << atrnSize
                  << std::endl;
     }

    return total;
}

unsigned int ckat::readSTRN( std::istream &file )
{
    std::string type;
    unsigned int strnSize;
    unsigned int total = readRecordHeader( file, type, strnSize );
    strnSize += 8;
    if( type != "STRN" )
    {
        std::cout << "Expected record of type STRN: " << type << std::endl;
        exit( 0 );
    }
    std::cout << "Found " << type << ": " << strnSize-8 << " bytes"
	      << std::endl;

    float u1;
    for( unsigned int i = 0; i < numSTRN; ++i )
      {
	total += base::read( file, u1 );
	std::cout << u1 << std::endl;
      }

    total += readUnknown( file, strnSize - total );

    if( strnSize == total )
    {
        std::cout << "Finished reading STRN" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading STRN" << std::endl;
        std::cout << "Read " << total << " out of " << strnSize
                  << std::endl;
     }

    return total;
}

unsigned int ckat::readXFIN( std::istream &file )
{
    std::string type;
    unsigned int xfinSize;
    unsigned int total = readRecordHeader( file, type, xfinSize );
    xfinSize += 8;
    if( type != "XFIN" )
    {
        std::cout << "Expected record of type XFIN: " << type << std::endl;
        exit( 0 );
    }
    std::cout << "Found " << type << ": " << xfinSize-8 << " bytes"
	      << std::endl;

    std::string name;
    total += base::read( file, name );
    std::cout << "Name: " << name << std::endl;

    char u2;
    total += base::read( file, u2 );
    std::cout << (int)u2 << std::endl;

    total += base::read( file, u2 );
    std::cout << (int)u2 << std::endl;

    total += base::read( file, u2 );
    std::cout << (int)u2 << std::endl;

    total += base::read( file, u2 );
    std::cout << (int)u2 << std::endl;

    short u1;
    total += base::read( file, u1 );
    std::cout << "STRN index: " << u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << "STRN index: " << u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << "STRN index: " << u1 << std::endl;

    if( xfinSize == total )
    {
        std::cout << "Finished reading XFIN" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading XFIN" << std::endl;
        std::cout << "Read " << total << " out of " << xfinSize
                  << std::endl;
     }

    return total;
}

unsigned int ckat::readQCHN( std::istream &file )
{
    std::string type;
    unsigned int qchnSize;
    unsigned int total = readRecordHeader( file, type, qchnSize );
    qchnSize += 8;
    if( type != "QCHN" )
    {
        std::cout << "Expected record of type QCHN: " << type << std::endl;
        exit( 0 );
    }
    std::cout << "Found " << type << ": " << qchnSize-8 << " bytes"
	      << std::endl;

    unsigned char num;
    total += base::read( file, num );
    std::cout << (int)num << std::endl;

    unsigned char u1;
    total += base::read( file, u1 );
    std::cout << (int)u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << (int)u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << (int)u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << (int)u1 << std::endl;

    keyframe newKey;

    unsigned short bone;
    unsigned char x, y, z, w;
    for( unsigned char i = 0; i < num; ++i )
      {
	total += base::read( file, bone );
	total += base::read( file, x );
	total += base::read( file, y );
	total += base::read( file, z );
	total += base::read( file, w );

	//quat newQuat( x/128.0f, y/128.0f, z/128.0f, w/128.0f );
	quat newQuat( x/255.0f, y/255.0f, z/255.0f, w/255.0f );
	newKey.quatMap[bone] = newQuat;
#if 0
	std::cout << "Bone " << bone << ": ";
#if 1
	std::cout << (x/255.0) << ", ";
	std::cout << (y/255.0) << ", ";
	std::cout << (z/255.0) << ", ";
	std::cout << (w/255.0) << std::endl;
#else
	std::cout << (x/128.0) << ", ";
	std::cout << (y/128.0) << ", ";
	std::cout << (z/128.0) << ", ";
	std::cout << (w/128.0) << std::endl;
#endif
#else
	std::cout << "Bone ";
	std::cout.width( 2 );
	std::cout << bone << ": ";
	std::cout.width( 4 );
	std::cout << (int)x << ", ";
	std::cout.width( 4 );
	std::cout << (int)y << ", ";
	std::cout.width( 4 );
	std::cout << (int)z << ", ";
	std::cout.width( 4 );
	std::cout << (int)w << std::endl;
#endif
      }
    keyframeList.push_back( newKey );

    //total += readUnknown( file, qchnSize - total );

    if( qchnSize == total )
    {
        std::cout << "Finished reading QCHN" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading QCHN" << std::endl;
        std::cout << "Read " << total << " out of " << qchnSize
                  << std::endl;
     }

    return total;
}

unsigned int ckat::readMSGS( std::istream &file )
{
    std::string type;
    unsigned int msgsSize;
    unsigned int total = readFormHeader( file, "MSGS", msgsSize );
    msgsSize += 8;
    std::cout << "Found MSGS form"
	      << ": " << msgsSize-12 << " bytes"
	      << std::endl;

    unsigned int infoSize;
    total += readRecordHeader( file, type, infoSize );
    infoSize += 8;
    if( type != "INFO" )
    {
        std::cout << "Expected record of type INFO: " << type << std::endl;
        exit( 0 );
    }
    std::cout << "Found " << type << ": " << infoSize-8 << " bytes"
	      << std::endl;

    unsigned short numMESG;
    total += base::read( file, numMESG );
    std::cout << "Num MESG: " << numMESG << std::endl;

    for( unsigned short i = 0; i < numMESG; ++i )
      {
	total += readMESG( file );
      }

    if( msgsSize == total )
    {
        std::cout << "Finished reading MSGS" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading MSGS" << std::endl;
        std::cout << "Read " << total << " out of " << msgsSize
                  << std::endl;
     }

    return total;
}

unsigned int ckat::readMESG( std::istream &file )
{
    std::string type;
    unsigned int mesgSize;
    unsigned int total = readRecordHeader( file, type, mesgSize );
    mesgSize += 8;
    if( type != "MESG" )
    {
        std::cout << "Expected record of type MESG: " << type << std::endl;
        exit( 0 );
    }
    std::cout << "Found " << type << ": " << mesgSize-8 << " bytes"
	      << std::endl;

    unsigned short u1;
    total += base::read( file, u1 );
    std::cout << u1 << " ";

    std::string name;
    total += base::read( file, name );
    std::cout << name << " ";

    total += base::read( file, u1 );
    std::cout << u1 << " ";

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    if( mesgSize == total )
    {
        std::cout << "Finished reading MESG" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading MESG" << std::endl;
        std::cout << "Read " << total << " out of " << mesgSize
                  << std::endl;
     }

    return total;
}

unsigned int ckat::readLOCT( std::istream &file )
{
    std::string type;
    unsigned int loctSize;
    unsigned int total = readRecordHeader( file, type, loctSize );
    loctSize += 8;
    if( type != "LOCT" )
    {
        std::cout << "Expected record of type LOCT: " << type << std::endl;
        exit( 0 );
    }
    std::cout << "Found " << type << ": " << loctSize-8 << " bytes"
	      << std::endl;

    short u1;
    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    for( unsigned int i = 0; i < 82; ++i )
      {
      }
    total += readUnknown( file, loctSize - total );

    if( loctSize == total )
    {
        std::cout << "Finished reading LOCT" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading LOCT" << std::endl;
        std::cout << "Read " << total << " out of " << loctSize
                  << std::endl;
     }

    return total;
}

unsigned int ckat::readCHNL( std::istream &file )
{
    std::string type;
    unsigned int chnlSize;
    unsigned int total = readRecordHeader( file, type, chnlSize );
    chnlSize += 8;
    if( type != "CHNL" )
    {
        std::cout << "Expected record of type CHNL: " << type << std::endl;
        exit( 0 );
    }
    std::cout << "Found " << type << ": " << chnlSize-8 << " bytes"
	      << std::endl;

    unsigned short num;
    total += base::read( file, num );
    std::cout << "Num: " << num << std::endl;
    unsigned char u1;
    short u2;
    for( unsigned int i = 0; i < num; ++i )
      {
	total += base::read( file, u2 );
	std::cout << u2 << " ";

	total += base::read( file, u1 );
	std::cout << (u1/255.0) << " ";

	total += base::read( file, u1 );
	std::cout << (u1/255.0) << " ";

	total += base::read( file, u1 );
	std::cout << (u1/255.0) << " ";

	total += base::read( file, u1 );
	std::cout << (u1/255.0) << " ";

	std::cout << std::endl;
      }

    //total += readUnknown( file, chnlSize - total );

    if( chnlSize == total )
    {
        std::cout << "Finished reading CHNL" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading CHNL" << std::endl;
        std::cout << "Read " << total << " out of " << chnlSize
                  << std::endl;
     }

    return total;
}

