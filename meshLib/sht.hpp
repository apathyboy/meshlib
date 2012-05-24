/** -*-c++-*-
 *  \class  sht
 *  \file   sht.hpp
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

#ifndef SHT_HPP
#define SHT_HPP

namespace ml
{
  class sht : public base
  {
  public:
    sht();
    ~sht();
    bool isRightType( std::istream &file )
    {
      return isOfType( file, "SSHT" );
    }
    unsigned int readSHT( std::istream &file, std::string path="" );
  
#if 0
    bool hasNormalMap() const { return normalMap; }
    unsigned int getNormalMapTextureUnit() const { return normalMapUnit; }
    unsigned int getMainTextureUnit() const { return mainMapUnit; }
#endif
    void getAmbient( float &r, float &g, float &b, float &a ) const;
    void getDiffuse( float &r, float &g, float &b, float &a ) const;
    void getSpecular( float &r, float &g, float &b, float &a ) const;
    void getEmissive( float &r, float &g, float &b, float &a ) const;
    void getShininess( float &shiny ) const;
    std::string getMaterialName() const;
    void setMaterialName( const std::string newName );

#if 0
    std::string getDiffuseTextureName() const
    {
      return diffuseTextureName;
    }
#endif

    std::string getMainTextureName() const
    {
      return mainTextureName;
    }

    unsigned int getMainTextureUnit() const
    {
      return mainTextureUnit;
    }

    std::string getNormalTextureName() const
    {
      return normalTextureName;
    }

    std::vector<unsigned int> coordMapping;
  
  protected:
    unsigned int readMATS( std::istream &file );
    unsigned int readTXMS( std::istream &file );
    unsigned int readTXM( std::istream &file );
    unsigned int readTCSS( std::istream &file );
    unsigned int readTFNS( std::istream &file );
    unsigned int readTSNS( std::istream &file );
    unsigned int readARVS( std::istream &file );
    unsigned int readNAME( std::istream &file );
    unsigned int readEFCT( std::istream &file );
  
    std::vector<std::string> texTag;

    std::string materialName;
  
    std::string diffuseTextureTag;
    std::string diffuseTextureName;

    std::string mainTextureName;
    unsigned int mainTextureUnit;

    std::string normalTextureName;
    unsigned int normalTextureUnit;

    std::string specularTextureName;
    unsigned int specularTextureUnit;

    std::string hueTextureName;
    unsigned int hueTextureUnit;

    std::string environmentTextureName;
    unsigned int environmentTextureUnit;

    std::string dot3TextureName;
    unsigned int dot3TextureUnit;

    std::string lookupTextureName;
    unsigned int lookupTextureUnit;

    std::string maskTextureName;
    unsigned int maskTextureUnit;

    float ambient[4];
    float diffuse[4];
    float specular[4];
    float emissive[4];
    float shininess;

    bool normalMap;
    std::string effectName;
  
    unsigned int normalMapUnit;
    unsigned int mainMapUnit;

  private:

  };
}
#endif
