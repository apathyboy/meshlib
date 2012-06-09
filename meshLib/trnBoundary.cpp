/** -*-c++-*-
 *  \class  trnBoundary
 *  \file   trnBoundary.cpp
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
#include <meshLib/trnBoundary.hpp>
#include <cstdlib>
#include <cmath>

using namespace ml;

trnBoundary::trnBoundary()
{
}

trnBoundary::~trnBoundary()
{
}

unsigned int trnBoundary::readIHDR( std::istream &file,
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
      throw std::exception();
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

//****************************************************************************

// Boundary Polygon
boundaryPolygon::boundaryPolygon()
{
}

boundaryPolygon::~boundaryPolygon()
{
}

bool boundaryPolygon::isInBounds( const float &X,
			      const float &Y ) const
{
  //int pnpoly(int nvert, float *vertx, float *verty, float testx, float testy)
  
  bool c = false;
  unsigned int numVerts = x.size();
  unsigned int i, j;
  for( i = 0, j = numVerts-1; i < numVerts; j = i++)
    {
      if ( ( ( y[i] > Y ) != ( y[j] > Y ) )
	   && ( X < ( x[j] - x[i] ) * ( Y - y[i] )
		/ ( y[j] - y[i] ) + x[i]) )
	{
	  c = !c;
	}
    }

  return c;
}

unsigned int boundaryPolygon::read( std::istream &file,
				    const std::string &debugString )
{
  std::string dbgStr = debugString + "BPOL: ";
  unsigned int bpolSize;
  unsigned int total = base::readFormHeader( file, "BPOL", bpolSize );
  bpolSize += 8;
  std::cout << debugString << "Found BPOL form" << std::endl;

  unsigned int size;
  total += base::readFormHeader( file, "0005", size );
  std::cout << dbgStr << "Found 0005 form" << std::endl;

  total += readIHDR( file, dbgStr );

  std::string type;
  total += base::readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected record of type DATA: " << type << std::endl;
      throw std::exception();
    }
  std::cout << dbgStr << "Found DATA record" << std::endl;

  unsigned int num;
  total += base::read( file, num );
  std::cout << dbgStr << num << std::endl;

  float newX, newY;
  for( unsigned int i = 0; i < num; ++i )
    {
      total += base::read( file, newX );
      total += base::read( file, newY );
      x.push_back( newX );
      y.push_back( newY );

      std::cout << dbgStr << newX << ", " << newY << std::endl;
    }
  total += base::read( file, u2 );
  std::cout << dbgStr << u2 << std::endl;

  total += base::read( file, u3 );
  std::cout << dbgStr << u3 << std::endl;

  total += base::read( file, u4 );
  std::cout << dbgStr << u4 << std::endl;

  total += base::read( file, altitude );
  std::cout << dbgStr << "Altitude: " << altitude << std::endl;

  total += base::read( file, u6 );
  std::cout << dbgStr << u6 << std::endl;

  std::string tempName;
  total += base::read( file, tempName );
  if( !tempName.empty() )
    {
      shaderName = "shader/" + tempName;
    }
  else
    {
      shaderName = tempName;
    }
  std::cout << dbgStr << "'" << shaderName << "'" << std::endl;

  if( bpolSize == total )
    {
      std::cout << debugString << "Finished reading BPOL" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading BPOL" << std::endl;
      std::cout << "Read " << total << " out of " << bpolSize
                << std::endl;
    }

  return total;
}

//****************************************************************************

// Boundary Polyline
boundaryPolyline::boundaryPolyline()
{
}

boundaryPolyline::~boundaryPolyline()
{
}

unsigned int boundaryPolyline::read( std::istream &file,
				     const std::string &debugString )
{
  std::string dbgStr = debugString + "BPLN: ";
  unsigned int bplnSize;
  unsigned int total = base::readFormHeader( file, "BPLN", bplnSize );
  bplnSize += 8;
  std::cout << debugString << "Found BPLN form" << std::endl;
  
  unsigned int size;
  total += base::readFormHeader( file, "0001", size );
  std::cout << dbgStr << "Found 0001 form" << std::endl;
  
  total += readIHDR( file, dbgStr );
  
  std::string type;
  total += base::readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected record of type DATA: " << type << std::endl;
      throw std::exception();
    }
  std::cout << dbgStr << "Found DATA record" << std::endl;
  
  unsigned int num;
  total += base::read( file, num );
  std::cout << dbgStr << num << std::endl;

  float newX, newY;
  for( unsigned int i = 0; i < num; ++i )
    {
      total += base::read( file, newX );
      total += base::read( file, newY );
      x.push_back( newX );
      y.push_back( newY );
      
      std::cout << dbgStr << newX << ", " << newY << std::endl;
    }

  total += base::read( file, u2 );
  std::cout << dbgStr << u2 << std::endl;

  total += base::read( file, u3 );
  std::cout << dbgStr << u3 << std::endl;

  total += base::read( file, u4 );
  std::cout << dbgStr << u4 << std::endl;

  if( bplnSize == total )
    {
      std::cout << debugString << "Finished reading BPLN" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading BPLN" << std::endl;
      std::cout << "Read " << total << " out of " << bplnSize
                << std::endl;
    }

  return total;
}

//****************************************************************************

// Boundary Circle.
boundaryCircle::boundaryCircle()
{
}

boundaryCircle::~boundaryCircle()
{
}

bool boundaryCircle::isInBounds( const float &X,
				 const float &Y ) const
{
  return ( radiusSqrd > (std::pow( X-x, 2.0f ) + std::pow( Y-y, 2.0f )));
}

unsigned int boundaryCircle::read( std::istream &file,
				   const std::string &debugString )
{
  std::string dbgStr = debugString + "BCIR: ";
  unsigned int bcirSize;
  unsigned int total = base::readFormHeader( file, "BCIR", bcirSize );
  bcirSize += 8;
  std::cout << debugString << "Found BCIR form" << std::endl;

  unsigned int size;
  total += base::readFormHeader( file, "0002", size );
  std::cout << dbgStr << "Found 0002 form" << std::endl;

  total += readIHDR( file, dbgStr );

  std::string type;
  total += base::readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected record of type DATA: " << type << std::endl;
      throw std::exception();
    }
  std::cout << dbgStr << "Found DATA record" << std::endl;

  total += base::read( file, x );
  total += base::read( file, y );
  std::cout << dbgStr << "Center: "
            << x << ", "
            << y << std::endl;

  total += base::read( file, radius );
  radiusSqrd = std::pow( radius, 2.0f );
  std::cout << dbgStr << "Radius: " << radius << std::endl;

  total += base::read( file, featherType );
  std::cout << dbgStr << "Feather type: " << featherType << std::endl;

  total += base::read( file, featherWidth );
  std::cout << dbgStr << "Feather width: " << featherWidth << std::endl;

  if( bcirSize == total )
    {
      std::cout << debugString << "Finished reading BCIR" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading BCIR" << std::endl;
      std::cout << "Read " << total << " out of " << bcirSize
                << std::endl;
    }
  return total;
}

//****************************************************************************

// Boundary Rectangle.
boundaryRectangle::boundaryRectangle()
{
}

boundaryRectangle::~boundaryRectangle()
{
}

bool boundaryRectangle::isInBounds( const float &X,
				    const float &Y ) const
{
  return( (X >= x1) & (X <= x2) && (Y >= y1) && (Y <= y2) );
}

unsigned int boundaryRectangle::read( std::istream &file,
				      const std::string &debugString )
{
  std::string dbgStr = debugString + "BREC: ";
  unsigned int brecSize;
  unsigned int total = base::readFormHeader( file, "BREC", brecSize );
  brecSize += 8;
  std::cout << debugString << "Found BREC form" << std::endl;

  unsigned int size;
  std::string form, brecType;
  total += base::readFormHeader( file, form, size, brecType );
  if( "FORM" != form )
    {
      std::cout << "Expected FORM" << std::endl;
      throw std::exception();
    }
  std::cout << dbgStr << "Found " << brecType << " form" << std::endl;

  total += readIHDR( file, dbgStr );

  std::string type;
  total += base::readRecordHeader( file, type, size );
  if( type != "DATA" )
    {
      std::cout << "Expected record of type DATA: " << type << std::endl;
      throw std::exception();
    }
  std::cout << dbgStr << "Found DATA record" << std::endl;

      total += base::read( file, x1 );
      total += base::read( file, y1 );
      total += base::read( file, x2 );
      total += base::read( file, y2 );
      
      std::cout << dbgStr << x1 << ", "
		<< y1 << "..."
		<< x2 << ", "
		<< y2 << std::endl;
      
      total += base::read( file, u2 );
      std::cout << dbgStr << u2 << std::endl;
      
      total += base::read( file, u3 );
      std::cout << dbgStr << u3 << std::endl;
      
  if( "0003" == brecType )
    {
      total += base::read( file, u4 );
      std::cout << dbgStr << u4 << std::endl;
      
      total += base::read( file, u5 );
      std::cout << dbgStr << u5 << std::endl;
      
      total += base::read( file, u6 );
      std::cout << dbgStr << u6 << std::endl;
      
      total += base::read( file, u7 );
      std::cout << dbgStr << u7 << std::endl;
      
      total += base::read( file, name2 );
      std::cout << dbgStr << "'" << name2 << "'" << std::endl;
    }

  if( brecSize == total )
    {
      std::cout << debugString << "Finished reading BREC" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading BREC" << std::endl;
      std::cout << "Read " << total << " out of " << brecSize
                << std::endl;
    }
  return total;

}

