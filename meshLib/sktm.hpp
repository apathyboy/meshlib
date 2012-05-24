/** -*-c++-*-
 *  \class  sktm
 *  \file   sktm.hpp
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

#include <fstream>
#include <string>
#include <vector>

#ifndef SKTM_HPP
#define SKTM_HPP

namespace ml
{
  class sktm : public base
  {
  public:
    sktm();
    ~sktm();
    bool isRightType( std::istream &file )
    {
      return isOfType( file, "SKTM" );
    }
    unsigned int readSKTM( std::istream &file );
    void print() const;

    unsigned int getNumBones() const
    {
      return boneName.size();
    }

    const std::string &getBoneName( unsigned int i ) const
    {
      return boneName[i];
    }

    const int &getBoneParent( unsigned int i ) const
    {
      return boneParent[i];
    }

    const float &getBoneXOffset( unsigned int i ) const
    {
      return boneXOffset[i];
    }

    const float &getBoneYOffset( unsigned int i ) const
    {
      return boneYOffset[i];
    }

    const float &getBoneZOffset( unsigned int i ) const
    {
      return boneZOffset[i];
    }

    const float &getBonePostQuatX( unsigned int i ) const
    {
      return bonePostQuatX[i];
    }

    const float &getBonePostQuatY( unsigned int i ) const
    {
      return bonePostQuatY[i];
    }

    const float &getBonePostQuatZ( unsigned int i ) const
    {
      return bonePostQuatZ[i];
    }

    const float &getBonePostQuatW( unsigned int i ) const
    {
      return bonePostQuatW[i];
    }

    const float &getBonePreQuatX( unsigned int i ) const
    {
      return bonePreQuatX[i];
    }

    const float &getBonePreQuatY( unsigned int i ) const
    {
      return bonePreQuatY[i];
    }

    const float &getBonePreQuatZ( unsigned int i ) const
    {
      return bonePreQuatZ[i];
    }

    const float &getBonePreQuatW( unsigned int i ) const
    {
      return bonePreQuatW[i];
    }


  protected:
    unsigned int readINFO( std::istream &file );
    unsigned int readNAME( std::istream &file );
    unsigned int readPRNT( std::istream &file );
    unsigned int readRPRE( std::istream &file );
    unsigned int readRPST( std::istream &file );
    unsigned int readBPTR( std::istream &file );
    unsigned int readBPRO( std::istream &file );
    unsigned int readJROR( std::istream &file );

  private:
    unsigned int numBones;
    std::vector<std::string> boneName;
    std::vector<int> boneParent;
    
    std::vector< float > boneXOffset;
    std::vector< float > boneYOffset;
    std::vector< float > boneZOffset;

    std::vector< float > bonePostQuatX;
    std::vector< float > bonePostQuatY;
    std::vector< float > bonePostQuatZ;
    std::vector< float > bonePostQuatW;

    std::vector< float > bonePreQuatX;
    std::vector< float > bonePreQuatY;
    std::vector< float > bonePreQuatZ;
    std::vector< float > bonePreQuatW;

    std::vector< float > boneProQuatX;
    std::vector< float > boneProQuatY;
    std::vector< float > boneProQuatZ;
    std::vector< float > boneProQuatW;
  };
}
#endif
