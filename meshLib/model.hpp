/** -*-c++-*-
 *  \class  model
 *  \file   model.hpp
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

#include <meshLib/base.hpp>
#include <meshLib/box.hpp>
#include <meshLib/vector3.hpp>
#include <meshLib/matrix3.hpp>

#ifndef MODEL_HPP
#define MODEL_HPP

namespace ml
{
  class model : public base
  {
  public:
    model() {};
    ~model() {};

  protected:
    std::vector<box> bbox;
    float bsX, bsY, bsZ, bsRadius;

    static unsigned int readEXBX( std::istream &file,
				  float &cx, float &cy, float &cz,
				  float &radius,
				  box &box1
				  );
    static unsigned int readEXSP( std::istream &file,
				  float &cx, float &cy, float &cz,
				  float &radius
				  );
    static unsigned int readXCYL( std::istream &file,
				  float &u1, float &u2, float &u3,
				  float &u4, float &u5
				  );
    static unsigned int readSPHR( std::istream &file,
				  float &cx, float &cy, float &cz,
				  float &radius
				  );

    static unsigned int readCYLN( std::istream &file,
				  float &u1, float &u2, float &u3,
				  float &u4, float &u5
				  );

    static unsigned int readMatrixAndPosition( std::istream &file,
					       matrix3 &matrix,
					       vector3 &position
					       );

    static unsigned int readVERT( std::istream &file,
				  std::vector<vector3> &vec
				  );

    static unsigned int readINDX( std::istream &file,
				  std::vector<unsigned int> &index );

    static unsigned int readIDTL( std::istream &file,
				  std::vector<vector3> &vec,
				  std::vector<unsigned int> &index
				  );
    unsigned int readCMSH( std::istream &file );
    unsigned int readCMPT( std::istream &file );
    unsigned int readCPST( std::istream &file );
    unsigned int readDTAL( std::istream &file );

    unsigned int readAPPR( std::istream &file );

    unsigned int readNULL( std::istream &file );
    unsigned int readHPTS( std::istream &file );
    unsigned int readFLOR( std::istream &file );
    unsigned int readHPNT( std::istream &file );
    unsigned int readDYN( std::istream &file );

  private:
  };
}
#endif
