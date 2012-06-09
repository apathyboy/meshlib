/** -*-c++-*-
 *  \class  skmg
 *  \file   skmg.cpp
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

/**
   This class still needs work.
 */

#include <meshLib/base.hpp>
#include <meshLib/skmg.hpp>

#include <iostream>
#include <cstdlib>

using namespace ml;

skmg::skmg()
{
}

skmg::~skmg()
{
}

unsigned int skmg::readSKMG( std::istream &file )
{
    unsigned int skmgSize;
    unsigned int total = readFormHeader( file, "SKMG", skmgSize );
    skmgSize += 8;
    std::cout << "Found SKMG form" << std::endl;

    unsigned int size;
    std::string form, type;
    total += readFormHeader( file, form, size, type );
    if( form != "FORM" )
    {
	std::cout << "Expected Form" << std::endl;
	throw std::exception();
    }
    std::cout << "Found form of type: " << type<< std::endl;

    total += readINFO( file );
    total += readSKTM( file );

    while( total < skmgSize )
      {
	// Peek at next record, but keep file at same place.
	peekHeader( file, form, size, type );

	if( form == "FORM" )
	  {
	    if( type == "PSDT" )
	      {
		psdt newPsdt( this );
		psdtList.push_back( newPsdt );
		total += readPSDT( file, psdtList.back() );
	      }
	    else if( type == "BLTS" )
	      {
		total += readBLTS( file );
	      }
	    else if( type == "HPTS" )
	      {
		//total += readHPTS( file );
			  total += readUnknown( file, size+8 );
	      }
	    else if( type == "TRTS" )
	      {
		total += readTRTS( file );
	      }
	    else
	      {
		std::cout << "Unexpected form: " << type << std::endl;
		throw std::exception();
	      }
	  }
	else if( form == "XFNM" )
	  {
	    total += readXFNM( file );
	  }
	else if( form == "POSN" )
	  {
	    total += readPOSN( file );
	  }
	else if( form == "TWHD" )
	  {
	    total += readTWHD( file );
	  }
	else if( form == "TWDT" )
	  {
	    total += readTWDT( file );
	  }
	else if( form == "NORM" )
	  {
	    total += readNORM( file );
	  }
	else if( form == "DOT3" )
	  {
	    total += readDOT3( file );
	  }
	else if( form == "OZN " )
	  {
	    total += readOZN( file );
	  }
	else if( form == "FOZC" )
	  {
	    total += readFOZC( file );
	  }
	else if( form == "OZC " )
	  {
	    total += readOZC( file );
	  }
	else if( form == "ZTO " )
	  {
	    total += readZTO( file );
	  }
	else
	  {
	    std::cout << "Unexpected record: " << form << std::endl;
	    throw std::exception();
	  }
      }

    if( skmgSize == total )
    {
	std::cout << "Finished reading SKMG" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading SKMG" << std::endl;
	std::cout << "Read " << total << " out of " << skmgSize
                  << std::endl;
     }

    return total;
}

unsigned int skmg::readPSDT( std::istream &file, psdt &newPsdt )
{
    unsigned int psdtSize;
    std::string type;

    unsigned int total = readFormHeader( file, "PSDT", psdtSize );
    psdtSize += 8;
    std::cout << "Found PSDT form" << std::endl;

    unsigned int size;
    std::string form;
    while( total < psdtSize )
      {
	// Peek at next record, but keep file at same place.
	peekHeader( file, form, size, type );

	if( form == "FORM" )
	  {
	    if( type == "TCSF" )
	      {
		total += readTCSF( file, newPsdt );
	      }
	    else if( type == "PRIM" )
	      {
		total += readPRIM( file, newPsdt );
	      }
	    else
	      {
		std::cout << "Unexpected form: " << type << std::endl;
		throw std::exception();
	      }
	  }
	else if( form == "NAME" )
	  {
	    total += readNAME( file, newPsdt );
	  }
	else if( form == "PIDX" )
	  {
	    total += readPIDX( file, newPsdt );
	  }
	else if( form == "NIDX" )
	  {
	    total += readNIDX( file, newPsdt );
	  }
	else if( form == "VDCL" )
	  {
	    total += readVDCL( file, newPsdt );
	  }
	else if( form == "TXCI" )
	  {
	    total += readTXCI( file, newPsdt );
	  }
	else if( form == "DOT3" )
	  {
	    total += readDOT3Index( file, newPsdt );
	  }
	else
	  {
	    std::cout << "Unexpected record: " << form << std::endl;
	    throw std::exception();
	  }
      }

    if( psdtSize == total )
    {
	std::cout << "Finished reading PSDT" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading PSDT" << std::endl;
	std::cout << "Read " << total << " out of " << psdtSize
                  << std::endl;
     }

    return total;
}

unsigned int skmg::readTRTS( std::istream &file )
{
    unsigned int trtsSize;
    unsigned int total = readFormHeader( file, "TRTS", trtsSize );
    trtsSize += 8;
    std::cout << "Found TRTS form" << std::endl;

    total += readUnknown( file, trtsSize - total );

    if( trtsSize == total )
    {
	std::cout << "Finished reading TRTS" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading TRTS" << std::endl;
	std::cout << "Read " << total << " out of " << trtsSize
                  << std::endl;
     }

    return total;
}

unsigned int skmg::readBLTS( std::istream &file )
{
    unsigned int bltsSize;
    unsigned int total = readFormHeader( file, "BLTS", bltsSize );
    bltsSize += 8;
    std::cout << "Found BLTS form" << std::endl;

    std::cout << "Num BLT: " << numBLT << std::endl;
    for( unsigned int i = 0; i < numBLT; ++i )
      {
	blt newBlt;
	total += readBLT( file, newBlt );
	bltList.push_back( newBlt );
      }

    if( bltsSize == total )
    {
	std::cout << "Finished reading BLTS" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading BLTS" << std::endl;
	std::cout << "Read " << total << " out of " << bltsSize
                  << std::endl;
     }

    return total;
}

unsigned int skmg::readBLT( std::istream &file, blt &newBlt )
{
    unsigned int bltSize;
    unsigned int total = readFormHeader( file, "BLT ", bltSize);
    bltSize += 8;
    std::cout << "Found BLT form" << std::endl;


    total += readBLTINFO( file, newBlt );

	std::string peekType, peekForm;
	unsigned int peekSize;
	peekHeader(file, peekForm, peekSize, peekType);

	if (peekForm == "POSN") {
		total += readBLTPOSN( file, newBlt.numPos );

		peekHeader(file, peekForm, peekSize, peekType);
	}

	if (peekForm == "NORM") {
		total += readBLTNORM( file, newBlt.numNorm );
	}

    if( total < bltSize )
      {
	total += readDOT3( file );
      }

    if( total < bltSize )
      {
	total += readBLTHPTS( file );
      }

    if( bltSize == total )
    {
	std::cout << "Finished reading BLT" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading BLT" << std::endl;
	std::cout << "Read " << total << " out of " << bltSize
                  << std::endl;
     }

    return total;
}

unsigned int skmg::readOZN( std::istream &file )
{
    std::string type;
    unsigned int oznSize;
    unsigned int total = readRecordHeader( file, type, oznSize );
    oznSize += 8;
    if( type != "OZN " )
    {
        std::cout << "Expected record of type OZN: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    std::string name;
    while( total < oznSize )
      {
	total += base::read( file, name );
	std::cout << name << std::endl;
      }

    if( oznSize == total )
    {
        std::cout << "Finished reading OZN" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading OZN" << std::endl;
        std::cout << "Read " << total << " out of " << oznSize
                  << std::endl;
     }

    return total;
}

unsigned int skmg::readFOZC( std::istream &file )
{
    std::string type;
    unsigned int fozcSize;
    unsigned int total = readRecordHeader( file, type, fozcSize );
    fozcSize += 8;
    if( type != "FOZC" )
    {
        std::cout << "Expected record of type FOZC: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    unsigned short num;
    total += base::read( file, num );
    std::cout << "Num: " << num << std::endl;

    unsigned short u1;
    for( unsigned int i = 0; i < num; ++i )
      {
	total += base::read( file, u1 );
	std::cout << u1 << std::endl;
      }

    if( fozcSize == total )
    {
        std::cout << "Finished reading FOZC" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading FOZC" << std::endl;
        std::cout << "Read " << total << " out of " << fozcSize
                  << std::endl;
     }

    return total;
}

unsigned int skmg::readOZC( std::istream &file )
{
	 unsigned int xxxxSize;
    std::string type;
    unsigned int total = readRecordHeader( file, type, xxxxSize );

	base::readUnknown(file, xxxxSize);

	return xxxxSize + 8;

	/*
    std::string type;
    unsigned int ozcSize;
    unsigned int total = readRecordHeader( file, type, ozcSize );
    ozcSize += 8;
    if( type != "OZC " )
    {
        std::cout << "Expected record of type OZC: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    unsigned short u1;
    while( total < ozcSize )
      {
	total += base::read( file, u1 );
	std::cout << u1 << " ";

	total += base::read( file, u1 );
	std::cout << u1 << std::endl;
      }

    if( ozcSize == total )
    {
        std::cout << "Finished reading OZC" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading OZC" << std::endl;
        std::cout << "Read " << total << " out of " << ozcSize
                  << std::endl;
     }

    return total;*/
}

unsigned int skmg::readZTO( std::istream &file )
{
    std::string type;
    unsigned int ztoSize;
    unsigned int total = readRecordHeader( file, type, ztoSize );
    ztoSize += 8;
    if( type != "ZTO " )
    {
        std::cout << "Expected record of type ZTO: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    unsigned short u1;
    while( total < ztoSize )
      {
	total += base::read( file, u1 );
	std::cout << u1 << std::endl;
      }

    if( ztoSize == total )
    {
        std::cout << "Finished reading ZTO" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading ZTO" << std::endl;
        std::cout << "Read " << total << " out of " << ztoSize
                  << std::endl;
     }

    return total;
}

unsigned int skmg::readSKTM( std::istream &file )
{
    std::string type;
    unsigned int sktmSize;
    unsigned int total = readRecordHeader( file, type, sktmSize );
    sktmSize += 8;
    if( type != "SKTM" )
    {
        std::cout << "Expected record of type SKTM: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    for( unsigned int i = 0; i < numSkeletons; ++i )
      //while( total < sktmSize )
      {
	std::string skeletonFilename;
	total += base::read( file, skeletonFilename );
	std::cout << skeletonFilename << std::endl;
	
	skeletonFilenameList.push_back( skeletonFilename );
      }

    total += readUnknown( file, sktmSize-total );

    if( sktmSize == total )
    {
        std::cout << "Finished reading SKTM" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading SKTM" << std::endl;
        std::cout << "Read " << total << " out of " << sktmSize
                  << std::endl;
     }

    return total;
}

unsigned int skmg::readTXCI( std::istream &file, psdt &newPsdt )
{
    std::string type;
    unsigned int txciSize;
    unsigned int total = readRecordHeader( file, type, txciSize );
    txciSize += 8;
    if( type != "TXCI" )
    {
        std::cout << "Expected record of type TXCI: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    unsigned int u1;
    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    if( txciSize == total )
    {
        std::cout << "Finished reading TXCI" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading TXCI" << std::endl;
        std::cout << "Read " << total << " out of " << txciSize
                  << std::endl;
     }

    return total;
}

unsigned int skmg::readTCSF( std::istream &file, psdt &newPsdt )
{
    unsigned int tcsfSize;
    unsigned int total = readFormHeader( file, "TCSF", tcsfSize );
    tcsfSize += 8;
    std::cout << "Found TCSF form" << std::endl;

    total += readTCSD( file, newPsdt );

    if( tcsfSize == total )
    {
	std::cout << "Finished reading TCSF" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading TCSF" << std::endl;
	std::cout << "Read " << total << " out of " << tcsfSize
                  << std::endl;
     }

    return total;
}

unsigned int skmg::readPRIM( std::istream &file, psdt &newPsdt )
{
    unsigned int primSize;
    unsigned int total = readFormHeader( file, "PRIM", primSize );
    primSize += 8;
    std::cout << "Found PRIM form" << std::endl;

    total += readPRIMINFO( file, newPsdt );

    unsigned int size;
    std::string form, type;
    while( total < primSize )
      {
	// Peek at next record, but keep file at same place.
	peekHeader( file, form, size, type );

	if( form == "FORM" )
	  {
	    std::cout << "Unexpected form: " << type << std::endl;
	    throw std::exception();
	  }
	else if( form == "ITL " )
	  {
	    total += readITL( file, newPsdt );
	  }
	else if( form == "OITL" )
	  {
	    total += readOITL( file, newPsdt );
	  }
	else
	  {
	    std::cout << "Unexpected record: " << form << std::endl;
	    throw std::exception();
	  }
      }

    if( primSize == total )
    {
	std::cout << "Finished reading PRIM" << std::endl;
    }
    else
    {
	std::cout << "FAILED in reading PRIM" << std::endl;
	std::cout << "Read " << total << " out of " << primSize
                  << std::endl;
     }

    return total;
}

unsigned int skmg::readTCSD( std::istream &file, psdt &newPsdt )
{
    std::string type;
    unsigned int tcsdSize;
    unsigned int total = readRecordHeader( file, type, tcsdSize );
    tcsdSize += 8;
    if( type != "TCSD" )
    {
        std::cout << "Expected record of type TCSD: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    std::cout << "Num TCSD: " << numIndex << std::endl;
    // Texture coords?
    float tempU, tempV;
    for( unsigned int i = 0; i < numIndex; ++i )
      {
	total += base::read( file, tempU );
	total += base::read( file, tempV );
	
	newPsdt.u.push_back( tempU );
	newPsdt.v.push_back( tempV );

	std::cout << "UV: " << tempU << ", " << tempV << std::endl;;
      }

    if( tcsdSize == total )
    {
        std::cout << "Finished reading TCSD" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading TCSD" << std::endl;
        std::cout << "Read " << total << " out of " << tcsdSize
                  << std::endl;
     }

    return total;
}

// Index into Position/Normal/Texture index arrays.
unsigned int skmg::readITL( std::istream &file, psdt &newPsdt )
{
    std::string type;
    unsigned int itlSize;
    unsigned int total = readRecordHeader( file, type, itlSize );
    itlSize += 8;
    if( type != "ITL " )
    {
        std::cout << "Expected record of type ITL: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    unsigned int numITL;
    total += base::read( file, numITL );
    std::cout << "Num ITL: " << numITL << std::endl;;

    unsigned int i1, i2, i3;
    for( unsigned int i = 0; i < numITL; ++i )
      {
	total += base::read( file, i1 );
	total += base::read( file, i2 );
	total += base::read( file, i3 );

	newPsdt.itl.push_back( i1 );
	newPsdt.itl.push_back( i2 );
	newPsdt.itl.push_back( i3 );

	std::cout << i1 << ", " << i2 << ", " << i3 << std::endl;
      }

    if( itlSize == total )
    {
        std::cout << "Finished reading ITL" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading ITL" << std::endl;
        std::cout << "Read " << total << " out of " << itlSize
                  << std::endl;
     }

    return total;
}

// Index into Position/Normal/Texture index arrays.
unsigned int skmg::readOITL( std::istream &file, psdt &newPsdt )
{
    std::string type;
    unsigned int oitlSize;
    unsigned int total = readRecordHeader( file, type, oitlSize );
    oitlSize += 8;
    if( type != "OITL" )
    {
        std::cout << "Expected record of type OITL: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    unsigned int numOITL;
    total += base::read( file, numOITL );
    std::cout << "Num OITL: " << numOITL << std::endl;;

    short group;
    unsigned int i1, i2, i3;
    for( unsigned int i = 0; i < numOITL; ++i )
      {
	total += base::read( file, group );
	total += base::read( file, i1 );
	total += base::read( file, i2 );
	total += base::read( file, i3 );

	newPsdt.oitl[group].push_back( i1 );
	newPsdt.oitl[group].push_back( i2 );
	newPsdt.oitl[group].push_back( i3 );

	std::cout << "Group " << group << ": "
		  << i1 << ", "
		  << i2 << ", "
		  << i3 << std::endl;
      }

    if( oitlSize == total )
    {
        std::cout << "Finished reading OITL" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading OITL" << std::endl;
        std::cout << "Read " << total << " out of " << oitlSize
                  << std::endl;
     }

    return total;
}

unsigned int skmg::readINFO( std::istream &file )
{
    std::string type;
    unsigned int infoSize;
    unsigned int total = readRecordHeader( file, type, infoSize );
    infoSize += 8;
    if( type != "INFO" )
    {
        std::cout << "Expected record of type INFO: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    unsigned int u1;
    unsigned int u2;
    short u10;
    short u11;
    short u12;
    short u13;

    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    total += base::read( file, u2 );
    std::cout << u2 << std::endl;

    total += base::read( file, numSkeletons );
    std::cout << "Num skeletons: " << numSkeletons << std::endl;

    total += base::read( file, numBones);
    std::cout << "Num bones: " << numBones << std::endl;

    total += base::read( file, numPoints );
    std::cout << "Num points: " << numPoints << std::endl;

    total += base::read( file, numTwdt);
    std::cout << "Num twdt: " << numTwdt << std::endl;

    total += base::read( file, numNorm );
    std::cout << "Num normals: " << numNorm << std::endl;

    total += base::read( file, numPSDT );
    std::cout << "Num PSDT: " << numPSDT << std::endl;

    total += base::read( file, numBLT );
    std::cout << "Num blend tables: " << numBLT << std::endl;

    total += base::read( file, u10 );
    std::cout << u10 << std::endl;

    total += base::read( file, u11 );
    std::cout << u11 << std::endl;

    // Something to do with OITL
    total += base::read( file, u12 );
    std::cout << u12 << std::endl;

    total += base::read( file, u13 );
    std::cout << u13 << std::endl;

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

unsigned int skmg::readPRIMINFO( std::istream &file, psdt &newPsdt )
{
    std::string type;
    unsigned int priminfoSize;
    unsigned int total = readRecordHeader( file, type, priminfoSize );
    priminfoSize += 8;
    if( type != "INFO" )
    {
        std::cout << "Expected record of type PRIMINFO: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    unsigned int u1;
    total += base::read( file, u1 );
    std::cout << u1 << std::endl;

    if( priminfoSize == total )
    {
        std::cout << "Finished reading PRIMINFO" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading PRIMINFO" << std::endl;
        std::cout << "Read " << total << " out of " << priminfoSize
                  << std::endl;
     }

    return total;
}

unsigned int skmg::readBLTINFO( std::istream &file, blt &newBlt )
{
    std::string type;
    unsigned int bltinfoSize;
    unsigned int total = readRecordHeader( file, type, bltinfoSize );
    bltinfoSize += 8;
    if( type != "INFO" )
    {
        std::cout << "Expected record of type BLTINFO: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    total += base::read( file, newBlt.numPos );
    std::cout << "Num points: " << newBlt.numPos << std::endl;

    total += base::read( file, newBlt.numNorm );
    std::cout << "Num normals: " << newBlt.numNorm << std::endl;

    total += base::read( file, newBlt.name );
    std::cout << newBlt.name << std::endl;

    if( bltinfoSize == total )
    {
        std::cout << "Finished reading BLTINFO" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading BLTINFO" << std::endl;
        std::cout << "Read " << total << " out of " << bltinfoSize
                  << std::endl;
     }

    return total;
}

unsigned int skmg::readPOSN( std::istream &file )
{
    std::string type;
    unsigned int posnSize;
    unsigned int total = readRecordHeader( file, type, posnSize );
    posnSize += 8;
    if( type != "POSN" )
    {
        std::cout << "Expected record of type POSN: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found POSN: " << posnSize << std::endl;

    std::cout << "Num points: " << numPoints << std::endl;

    float tempX, tempY, tempZ;
    for( unsigned int i = 0; i < numPoints; ++i )
      {
	total += base::read( file, tempX );
	total += base::read( file, tempY );
	total += base::read( file, tempZ );
	std::cout << "Vertex " << i << ": "
		  << tempX << ",  " << tempY << ", " << tempZ << std::endl;
	x.push_back( tempX );
	y.push_back( tempY );
	z.push_back( tempZ );
      }

    if( posnSize == total )
    {
        std::cout << "Finished reading POSN" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading POSN" << std::endl;
        std::cout << "Read " << total << " out of " << posnSize
                  << std::endl;
     }

    return total;
}

unsigned int skmg::readNORM( std::istream &file )
{
    std::string type;
    unsigned int normSize;
    unsigned int total = readRecordHeader( file, type, normSize );
    normSize += 8;
    if( type != "NORM" )
    {
        std::cout << "Expected record of type NORM: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    std::cout << "Num Norm:  " << numNorm << std::endl;
    float tempX, tempY, tempZ;
    for( unsigned int i = 0; i < numNorm; ++i )
      {
	total += base::read( file, tempX );
	total += base::read( file, tempY );
	total += base::read( file, tempZ );
	//std::cout << tempX << ", " << tempY << ", " << tempZ << std::endl;

	nx.push_back( tempX );
	ny.push_back( tempY );
	nz.push_back( tempZ );
      }

    if( normSize == total )
    {
        std::cout << "Finished reading NORM" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading NORM" << std::endl;
        std::cout << "Read " << total << " out of " << normSize
                  << std::endl;
     }

    return total;
}

unsigned int skmg::readDOT3( std::istream &file )
{
    std::string type;
    unsigned int dot3Size;
    unsigned int total = readRecordHeader( file, type, dot3Size );
    dot3Size += 8;
    if( type != "DOT3" )
    {
        std::cout << "Expected record of type DOT3: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    total += base::read( file, numDot3 );

    std::cout << "Num DOT3: " << numDot3 << std::endl;
    float tempX;
    for( unsigned int i = 0; i < numDot3; ++i )
      {
	total += base::read( file, tempX );
	std::cout << tempX << " ";

	total += base::read( file, tempX );
	std::cout << tempX << " ";

	total += base::read( file, tempX );
	std::cout << tempX << " ";

	total += base::read( file, tempX );
	std::cout << tempX << std::endl;;
      }

    if( dot3Size == total )
    {
        std::cout << "Finished reading DOT3" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading DOT3" << std::endl;
        std::cout << "Read " << total << " out of " << dot3Size
                  << std::endl;
     }

    return total;
}

unsigned int skmg::readDOT3Index( std::istream &file, psdt &newPsdt  )
{
    std::string type;
    unsigned int dot3Size;
    unsigned int total = readRecordHeader( file, type, dot3Size );
    dot3Size += 8;
    if( type != "DOT3" )
    {
        std::cout << "Expected record of type DOT3: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    unsigned int index;
    while( total < dot3Size )
      {
	total += base::read( file, index );
	std::cout << index << std::endl;
      }

    if( dot3Size == total )
    {
        std::cout << "Finished reading DOT3" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading DOT3" << std::endl;
        std::cout << "Read " << total << " out of " << dot3Size
                  << std::endl;
     }

    return total;
}

unsigned int skmg::readBLTPOSN( std::istream &file, unsigned int num )
{
    std::string type;
    unsigned int posnSize;
    unsigned int total = readRecordHeader( file, type, posnSize );
    posnSize += 8;
    if( type != "POSN" )
    {
        std::cout << "Expected record of type POSN: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found POSN: " << posnSize << std::endl;
    std::cout << "Num points: " << num << std::endl;

    float tempX, tempY, tempZ, tempW;
    for( unsigned int i = 0; i < num; ++i )
      {
	total += base::read( file, tempX );
	total += base::read( file, tempY );
	total += base::read( file, tempZ );
	total += base::read( file, tempW );
	std::cout << tempX << ",  " << tempY << ", " << tempZ << ", " << tempW << std::endl;
      }

    if( posnSize == total )
    {
        std::cout << "Finished reading POSN" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading POSN" << std::endl;
        std::cout << "Read " << total << " out of " << posnSize
                  << std::endl;
     }

    return total;
}

unsigned int skmg::readBLTNORM( std::istream &file, unsigned int num )
{
    std::string type;
    unsigned int normSize;
    unsigned int total = readRecordHeader( file, type, normSize );
    normSize += 8;
    if( type != "NORM" )
    {
        std::cout << "Expected record of type NORM: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    std::cout << "Num Norm:  " << num << std::endl;
    float tempX, tempY, tempZ, tempW;
    for( unsigned int i = 0; i < num; ++i )
      {
	total += base::read( file, tempX );
	total += base::read( file, tempY );
	total += base::read( file, tempZ );
	total += base::read( file, tempW );
	std::cout << tempX << ", " << tempY << ", " << tempZ << ", " << tempW << std::endl;

	nx.push_back( tempX );
	ny.push_back( tempY );
	nz.push_back( tempZ );
      }

    if( normSize == total )
    {
        std::cout << "Finished reading NORM" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading NORM" << std::endl;
        std::cout << "Read " << total << " out of " << normSize
                  << std::endl;
     }

    return total;
}

// One entry for each point.  Each record is number of bones to which
// the point belongs.
unsigned int skmg::readTWHD( std::istream &file )
{
    std::string type;
    unsigned int twhdSize;
    unsigned int total = readRecordHeader( file, type, twhdSize );
    twhdSize += 8;
    if( type != "TWHD" )
    {
        std::cout << "Expected record of type TWHD: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    std::cout << "Num points: " << numPoints << std::endl;
    numVertexWeights.resize( numPoints );
    unsigned int vertexWeight;
    for( unsigned int i = 0; i < numPoints; ++i )
      {
	total += base::read( file, vertexWeight );
	std::cout << "Num weights for vertex "
		  << i << ": " << vertexWeight << std::endl;
	numVertexWeights[i] = vertexWeight;
      }

    if( twhdSize == total )
    {
        std::cout << "Finished reading TWHD" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading TWHD" << std::endl;
        std::cout << "Read " << total << " out of " << twhdSize
                  << std::endl;
     }

    return total;
}

// Each entry is a bone and weight factor
unsigned int skmg::readTWDT( std::istream &file )
{
    std::string type;
    unsigned int twdtSize;
    unsigned int total = readRecordHeader( file, type, twdtSize );
    twdtSize += 8;
    if( type != "TWDT" )
    {
        std::cout << "Expected record of type TWDT: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    std::cout << "Num TWDT:  " << numTwdt << std::endl;
    vertexWeights.resize( numPoints );
    unsigned int boneNum;
    float weight;
    for( unsigned int i = 0; i < numPoints; ++i )
      {
	std::cout << "Vertex " <<  i << ": ";
	for( unsigned int j = 0; j < numVertexWeights[i]; ++j )
	  {
	    total += base::read( file, boneNum );
	    std::cout << "(" << boneNames[boneNum] << ": ";
	    
	    total += base::read( file, weight );
	    std::cout << std::fixed << weight << ") ";

	    (vertexWeights[i])[boneNum] = weight;
	  }
	std::cout << std::endl;
      }

    if( twdtSize == total )
    {
        std::cout << "Finished reading TWDT" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading TWDT" << std::endl;
        std::cout << "Read " << total << " out of " << twdtSize
                  << std::endl;
     }

    return total;
}

// Index into points list
unsigned int skmg::readPIDX( std::istream &file, psdt &newPsdt )
{
    std::string type;
    unsigned int pidxSize;
    unsigned int total = readRecordHeader( file, type, pidxSize );
    pidxSize += 8;
    if( type != "PIDX" )
    {
        std::cout << "Expected record of type PIDX: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    total += base::read( file, numIndex );
    std::cout << "Num index: " << numIndex << std::endl;

    unsigned int index;
    for( unsigned int i = 0; i < numIndex; ++i )
      {
	total += base::read( file, index );
	newPsdt.pidx.push_back( index );
	std::cout << "Vertex index " << i << ": " << index << std::endl;
      }

    if( pidxSize == total )
    {
        std::cout << "Finished reading PIDX" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading PIDX" << std::endl;
        std::cout << "Read " << total << " out of " << pidxSize
                  << std::endl;
     }

    return total;
}

// Index into Normal array
unsigned int skmg::readNIDX( std::istream &file, psdt &newPsdt )
{
    std::string type;
    unsigned int nidxSize;
    unsigned int total = readRecordHeader( file, type, nidxSize );
    nidxSize += 8;
    if( type != "NIDX" )
    {
        std::cout << "Expected record of type NIDX: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    std::cout << "Num index: " << numIndex << std::endl;
    unsigned int index;
    for( unsigned int i = 0; i < numIndex; ++i )
      {
	total += base::read( file, index );
	newPsdt.nidx.push_back( index );
	std::cout << "Normal index " << i << ": " << index << std::endl;
      }

    if( nidxSize == total )
    {
        std::cout << "Finished reading NIDX" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading NIDX" << std::endl;
        std::cout << "Read " << total << " out of " << nidxSize
                  << std::endl;
     }

    return total;
}

unsigned int skmg::readVDCL( std::istream &file, psdt &newPsdt )
{
    std::string type;
    unsigned int vdclSize;
    unsigned int total = readRecordHeader( file, type, vdclSize );
    vdclSize += 8;
    if( type != "VDCL" )
    {
        std::cout << "Expected record of type VDCL: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << ": " << vdclSize-8 << " bytes"
              << std::endl;
    
    int index;
    for( unsigned int i = 0; i < numIndex; ++i )
      {
	total += base::read( file, index );
	std::cout << "?: " << index << std::endl;
      }

    if( vdclSize == total )
    {
        std::cout << "Finished reading VDCL" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading VDCL" << std::endl;
        std::cout << "Read " << total << " out of " << vdclSize
                  << std::endl;
     }

    return total;
}

unsigned int skmg::readNAME( std::istream &file, psdt &newPsdt )
{
    std::string type;
    unsigned int nameSize;
    unsigned int total = readRecordHeader( file, type, nameSize );
    nameSize += 8;
    if( type != "NAME" )
    {
        std::cout << "Expected record of type NAME: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    total += base::read( file, newPsdt.shaderFilename );
    std::cout << newPsdt.shaderFilename << std::endl;

    if( nameSize == total )
    {
        std::cout << "Finished reading NAME" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading NAME" << std::endl;
        std::cout << "Read " << total << " out of " << nameSize
                  << std::endl;
     }

    return total;
}

unsigned int skmg::readXFNM( std::istream &file )
{
    std::string type;
    unsigned int xfnmSize;
    unsigned int total = readRecordHeader( file, type, xfnmSize );
    xfnmSize += 8;
    if( type != "XFNM" )
    {
        std::cout << "Expected record of type XFNM: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    std::string boneName;
    for( unsigned int i = 0; i < numBones; ++i )
      {
	total += base::read( file, boneName );
	boneNames.push_back( boneName );
	std::cout << "Bone " << i << ": " << boneName << std::endl;
      }

    if( xfnmSize == total )
    {
        std::cout << "Finished reading XFNM" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading XFNM" << std::endl;
        std::cout << "Read " << total << " out of " << xfnmSize
                  << std::endl;
     }

    return total;
}

void skmg::print() const
{
}

unsigned int skmg::psdt::getNumVertex() const
{
  return pidx.size();
}

void skmg::psdt::getVertex( unsigned int index, float &X, float &Y, float &Z) const
{
  X = parentSkmg->getXVector()[pidx[index]];
  Y = parentSkmg->getYVector()[pidx[index]];
  Z = parentSkmg->getZVector()[pidx[index]];
}

void skmg::psdt::getNormal( unsigned int index, float &NX, float &NY, float &NZ) const
{
  NX = parentSkmg->getNXVector()[nidx[index]];
  NY = parentSkmg->getNYVector()[nidx[index]];
  NZ = parentSkmg->getNZVector()[nidx[index]];
}

void skmg::psdt::getTexCoord( unsigned int index, float &U, float &V ) const
{
  U = u[index];
  V = v[index];
}

const std::vector<unsigned int> &skmg::psdt::getTriangles() const
{
  return itl;
}

const std::vector<unsigned int> &skmg::psdt::getOTriangles( short group ) const
{
  static std::vector<unsigned int> emptyVec;

  std::map< short, std::vector<unsigned int> >
    ::const_iterator triangles = oitl.find( group );

  if( oitl.end() == triangles )
    {
      return emptyVec;
    }
  else
    {
      return triangles->second;
    }
}

unsigned int skmg::readBLTHPTS( std::istream &file )
{
    std::string type;
    unsigned int hptsSize;
    unsigned int total = readRecordHeader( file, type, hptsSize );
    hptsSize += 8;
    if( type != "HPTS" )
    {
        std::cout << "Expected record of type HPTS: " << type << std::endl;
        throw std::exception();
    }
    std::cout << "Found " << type << std::endl;

    total += readUnknown( file, hptsSize - total );

    if( hptsSize == total )
    {
        std::cout << "Finished reading HPTS" << std::endl;
    }
    else
    {
        std::cout << "FAILED in reading HPTS" << std::endl;
        std::cout << "Read " << total << " out of " << hptsSize
                  << std::endl;
     }

    return total;
}
