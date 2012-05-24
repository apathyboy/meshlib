/** -*-c++-*-
 *  \class  cmp
 *  \file   cmp.hpp
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
#include <meshLib/vector3.hpp>
#include <meshLib/matrix3.hpp>

#include <fstream>
#include <string>
#include <vector>

#ifndef CMP_HPP
#define CMP_HPP

namespace ml
{
  
  class cmp : public model
  {
  public:
    cmp();
    ~cmp();
    bool isRightType( std::istream &file )
    {
      return isOfType( file, "CMPA" );
    }
    unsigned int readCMP( std::istream &file, std::string path="" );
    unsigned int getNumParts() const
    {
      return partFilenames.size();
    }
    
    bool getPart( unsigned int index, std::string &filename,
		  vector3 &partPosition,
		  matrix3 &partScaleRotate
		  ) const;
    
    void getBoundingSphere( float &centerX,
			    float &centerY,
			    float &centerZ,
			    float &sphereRadius
			    )
    {
      centerX = cx;
      centerY = cy;
      centerZ = cz;
      sphereRadius = radius;
    }
    
    void getBoundingBox( float &X1, float &Y1, float &Z1,
			 float &X2, float &Y2, float &Z2
			 )
    {
      X1 = x1;
      Y1 = y1;
      Z1 = z1;
      X2 = x2;
      Y2 = y2;
      Z2 = z2;
    }

  protected:
    unsigned int readRADR( std::istream &file );
    unsigned int readPART( std::istream &file );

  private:
    std::vector<std::string> partFilenames;
    std::vector<vector3> position;
    std::vector<matrix3> scaleRotate;

    std::vector<vector3> radrVert;
    std::vector<unsigned int>radrIndex;

    // Bounding sphere center and radius
    float cx, cy, cz, radius;

    // 2 xyz points defining bounding box
    float x1, y1, z1;
    float x2, y2, z2;

  };
}
#endif
