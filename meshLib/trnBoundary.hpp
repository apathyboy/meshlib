/** -*-c++-*-
 *  \class  trnBoundary
 *  \file   trnBoundary.hpp
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
#include <meshLib/base.hpp>

#include <fstream>
#include <string>
#include <vector>
#include <map>

#ifndef TRNBOUNDARY_HPP
#define TRNBOUNDARY_HPP

namespace ml
{
  class trnBoundary
  {
  public:
    trnBoundary();
    virtual ~trnBoundary();

    virtual bool isInBounds( const float &X, const float &Y ) const
    {
      return false;
    }
    virtual unsigned int read( std::istream &file,
			       const std::string &debugString )
    {
      return 0;
    }
    unsigned int readIHDR( std::istream &file,
			   const std::string &debugString );

  protected:
    unsigned int u1;
    std::string name;

  };

  // Boundary Polygon
  class boundaryPolygon: public trnBoundary
  {
  public:
    boundaryPolygon();
    ~boundaryPolygon();
    bool isInBounds( const float &X, const float &Y ) const;
    unsigned int read( std::istream &file, const std::string &debugString );
    
  protected:
    std::vector<float> x;
    std::vector<float> y;

    unsigned int u2;
    float u3;
    unsigned int u4;
    float altitude;
    float u6;
    std::string shaderName;
  };

  // Boundary Polyline
  class boundaryPolyline : public trnBoundary
  {
  public:
    boundaryPolyline();
    ~boundaryPolyline();

    unsigned int read( std::istream &file, const std::string &debugString );

  protected:
    std::vector< float > x;
    std::vector< float > y;
    
    unsigned int u2;
    float u3;
    float u4;
  };

  // Boundary Circle.
  class boundaryCircle : public trnBoundary
  {
  public:
    boundaryCircle();
    ~boundaryCircle();
    bool isInBounds( const float &X,
		     const float &Y ) const;

    unsigned int read( std::istream &file, const std::string &debugString );

  protected:
    float x;
    float y;
    float radius;
    float radiusSqrd;
    
    unsigned int featherType;
    float featherWidth;
  };

  // Boundary Rectangle.
  class boundaryRectangle : public trnBoundary
  {
  public:
    boundaryRectangle();
    ~boundaryRectangle();
    bool isInBounds( const float &X,
		     const float &Y ) const;

    unsigned int read( std::istream &file, const std::string &debugString );

  protected:
    float x1;
    float y1;
    float x2;
    float y2;
    
    unsigned int u2;
    float u3;
    unsigned int u4;
    unsigned int u5;
    float u6;
    float u7;
    std::string name2;
  };


}
#endif
