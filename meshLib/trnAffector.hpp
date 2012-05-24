/** -*-c++-*-
 *  \class  trnAffector
 *  \file   trnAffector.hpp
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

#ifndef TRNAFFECTOR_HPP
#define TRNAFFECTOR_HPP

namespace ml
{
  class trnAffector
  {
  public:
    trnAffector();
    virtual ~trnAffector();
    virtual void apply( const float &currentX,
			const float &currentY,
			float &data) const;
    virtual unsigned int read( std::istream &file,
			       const std::string &debugString );
  protected:
    unsigned int readIHDR( std::istream &file, const std::string &debugString );

    unsigned int u1;
    std::string name;

  };

  // ACCN
  class affectorColorConstant : public trnAffector
  {
  public:
    affectorColorConstant();
    ~affectorColorConstant();
    void apply( const float &currentX,
		const float &currentY,
		float &data) const;
    unsigned int read( std::istream &file,
		       const std::string &debugString );

  protected:
    unsigned int u2;
    char u3;
    char u4;
    char u5;
  };

  // ACRF
  class affectorColorRampFractal : public trnAffector
  {
  public:
    affectorColorRampFractal();
    ~affectorColorRampFractal();
    void apply( const float &currentX,
		const float &currentY,
		float &data) const;
    unsigned int read( std::istream &file,
		       const std::string &debugString );
  protected:
    unsigned int u2;
    unsigned int u3;
    std::string name2;
  };

  // ACRH
  class affectorColorRampHeight : public trnAffector
  {
  public:
    affectorColorRampHeight();
    ~affectorColorRampHeight();
    void apply( const float &currentX,
		const float &currentY,
		float &data) const;
    unsigned int read( std::istream &file,
		       const std::string &debugString );
  protected:
    unsigned int u2;
    float u3;
    float u4;
    std::string name2;
    
  };

  // AENV
  class affectorEnvironment : public trnAffector
  {
  public:
    affectorEnvironment();
    ~affectorEnvironment();
    void apply( const float &currentX,
		const float &currentY,
		float &data) const;
    unsigned int read( std::istream &file,
		       const std::string &debugString );
  protected:
    unsigned int u2;
    unsigned int u3;
    float u4;
  };

  // AEXC
  class affectorExclude : public trnAffector
  {
  public:
    affectorExclude();
    ~affectorExclude();
    void apply( const float &currentX,
		const float &currentY,
		float &data) const;
    unsigned int read( std::istream &file,
		       const std::string &debugString );
  };

  // AFDF
  class affectorRadialFarConstant : public trnAffector
  {
  public:
    affectorRadialFarConstant();
    ~affectorRadialFarConstant();
    void apply( const float &currentX,
		const float &currentY,
		float &data) const;
    unsigned int read( std::istream &file,
		       const std::string &debugString );
  protected:
    unsigned int u2;
    unsigned int u3;
    unsigned int u4;
    unsigned int u5;
    float u6;
  };

  // AFDN
  class affectorRadialConstant : public trnAffector
  {
  public:
    affectorRadialConstant();
    ~affectorRadialConstant();
    void apply( const float &currentX,
		const float &currentY,
		float &data) const;
    unsigned int read( std::istream &file,
		       const std::string &debugString );

  protected:
    unsigned int u2;
    unsigned int u3;
    unsigned int u4;
    unsigned int u5;
    float u6;
  };

  // AFSC
  class affectorFloraConstant : public trnAffector
  {
  public:
    affectorFloraConstant();
    ~affectorFloraConstant();
    void apply( const float &currentX,
		const float &currentY,
		float &data) const;
    unsigned int read( std::istream &file,
		       const std::string &debugString );
  protected:
    unsigned int u2;
    unsigned int u3;
    unsigned int u4;
    unsigned int u5;
    float u6;
  };

  // AFSN
  class affectorFloraNonCollidableConstant : public trnAffector
  {
  public:
    affectorFloraNonCollidableConstant();
    ~affectorFloraNonCollidableConstant();
    void apply( const float &currentX,
		const float &currentY,
		float &data) const;
    unsigned int read( std::istream &file,
		       const std::string &debugString );
  protected:
    unsigned int u2;
    unsigned int u3;
    unsigned int u4;
    unsigned int u5;
    float u6;
  };

  // AHCN
  class affectorHeightConstant : public trnAffector
  {
  public:
    affectorHeightConstant();
    ~affectorHeightConstant();
    void apply( const float &currentX,
		const float &currentY,
		float &data) const;
    unsigned int read( std::istream &file,
		       const std::string &debugString );
  protected:
    unsigned int u2;
    float height;
  };

  // AHFR
  class affectorHeightFractal : public trnAffector
  {
  public:
    affectorHeightFractal();
    ~affectorHeightFractal();
    void apply( const float &currentX,
		const float &currentY,
		float &data) const;

    unsigned int read( std::istream &file,
		       const std::string &debugString );

    void setFractalIndex( const unsigned int &index )
    {
      fractalIndex = index;
    }

    unsigned int &getFractalIndex()
    {
      return fractalIndex;
    }

    void setUnknown1( const unsigned int &unknown )
    {
      u1 = unknown;
    }

    unsigned int &getUnknown1()
    {
      return u1;
    }

    void setHeight( const float &h )
    {
      height = h;
    }

    float & getHeight()
    {
      return height;
    }

  protected:
    unsigned int fractalIndex;
    unsigned int u2;
    float height;
    
  };

  // AHTR
  class affectorHeightTerrace : public trnAffector
  {
  public:
    affectorHeightTerrace();
    ~affectorHeightTerrace();
    void apply( const float &currentX,
		const float &currentY,
		float &data) const;
    unsigned int read( std::istream &file,
		       const std::string &debugString );
  protected:
    float u2;
    float u3;
  };

  // ARIV
  class affectorRiver : public trnAffector
  {
  public:
    affectorRiver();
    ~affectorRiver();
    void apply( const float &currentX,
		const float &currentY,
		float &data) const;
    unsigned int read( std::istream &file,
		       const std::string &debugString );
  protected:
    
  };

  // AROA
  class affectorRoad : public trnAffector
  {
  public:
    affectorRoad();
    ~affectorRoad();
    void apply( const float &currentX,
		const float &currentY,
		float &data) const;
    unsigned int read( std::istream &file,
		       const std::string &debugString );
  protected:
    
  };

  // ASCN
  class affectorShaderConstant : public trnAffector
  {
  public:
    affectorShaderConstant();
    ~affectorShaderConstant();
    void apply( const float &currentX,
		const float &currentY,
		float &data) const;
    unsigned int read( std::istream &file,
		       const std::string &debugString );
  protected:
    unsigned int u2;
    unsigned int u3;
    float u4;
  };

  // ASRP
  class affectorShaderReplace : public trnAffector
  {
  public:
    affectorShaderReplace();
    ~affectorShaderReplace();
    void apply( const float &currentX,
		const float &currentY,
		float &data) const;
    unsigned int read( std::istream &file,
		       const std::string &debugString );
  protected:
    unsigned int u2;
    unsigned int u3;
    unsigned int u4;
    float u5;
  };

  // FDIR
  class affectorFilterDirection : public trnAffector
  {
  public:
    affectorFilterDirection();
    ~affectorFilterDirection();
    void apply( const float &currentX,
		const float &currentY,
		float &data) const;
    unsigned int read( std::istream &file,
		       const std::string &debugString );
  };

  // FFRA
  class affectorFilterFractal : public trnAffector
  {
  public:
    affectorFilterFractal();
    ~affectorFilterFractal();
    void apply( const float &currentX,
		const float &currentY,
		float &data) const;
    unsigned int read( std::istream &file,
		       const std::string &debugString );
  protected:
    unsigned int fractalFamily;
    unsigned int featherType;
    float filterSeed;
    float filterLow;
    float filterHigh;
    float featherWidth;
    
  };

  // FHGT
  class affectorFilterHeight : public trnAffector
  {
  public:
    affectorFilterHeight();
    ~affectorFilterHeight();
    void apply( const float &currentX,
		const float &currentY,
		float &data) const;
    unsigned int read( std::istream &file,
		       const std::string &debugString );
  protected:
    float minHeight;
    float maxHeight;
    unsigned int featherType;
    float featherWidth;

  };

  // FSHD
  class affectorFilterShader : public trnAffector
  {
  public:
    affectorFilterShader();
    ~affectorFilterShader();
    void apply( const float &currentX,
		const float &currentY,
		float &data) const;
    unsigned int read( std::istream &file,
		       const std::string &debugString );
  protected:
    unsigned int u2;
  };

  // FSLP
  class affectorFilterSlope : public trnAffector
  {
  public:
    affectorFilterSlope();
    ~affectorFilterSlope();
    void apply( const float &currentX,
		const float &currentY,
		float &data) const;
    unsigned int read( std::istream &file,
		       const std::string &debugString );
  protected:
    float u2;
    float u3;
    unsigned int u4;
    unsigned int u5;
  };

}
#endif
