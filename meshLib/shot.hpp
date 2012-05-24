/** -*-c++-*-
 *  \class  shot
 *  \file   shot.hpp
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

#ifndef SHOT_HPP
#define SHOT_HPP

namespace ml
{
  class shot : public base
  {
  public:
    shot();
    ~shot();
    bool isRightType( std::istream &file )
    {
      return isOfType( file, "SHOT" );
    }
    unsigned int readSHOT( std::istream &file );
    void print() const;
  
    void setAppearanceFilename( const std::string &filename )
    {
      appearanceFilename = filename;
    }
  
    const std::string &getAppearanceFilename() const
    {
      return appearanceFilename;
    }
  
    void setPortalLayoutFilename( const std::string &filename )
    {
      portalLayoutFilename = filename;
    }
  
    const std::string &getPortalLayoutFilename() const
    {
      return portalLayoutFilename;
    }
  
  protected:
    unsigned int readDERV( std::istream &file, std::string &filename );
    unsigned int readPCNT( std::istream &file, unsigned int &num );
    unsigned int readXXXX( std::istream &file );
  
    unsigned int numAttributes;
    std::string shotBaseObjectFilename;

    std::vector<std::string> objectName;
    std::vector<std::string> detailedDescription;
    std::vector<std::string> lookAtText;
    unsigned char snapToTerrain;
    unsigned char containerType;
    unsigned char containerVolumeLimit;
    unsigned char tintPalette;
    std::string slotDescriptorFilename;
    std::string arrangementDescriptorFilename;
    std::string appearanceFilename;
    std::string portalLayoutFilename;
    std::string clientDataFile;
    unsigned short collisionMaterialFlags;
    unsigned short collisionMaterialPassFlags;
    unsigned short collisionMaterialBlockFlags;
    unsigned short collisionActionFlags;
    unsigned short collisionActionPassFlags;
    unsigned short collisionActionBlockFlags;
    unsigned short scale;
    unsigned short gameObjectType;
    unsigned char  sendToClient;
    unsigned short scaleThresholdBeforeExtentTest;
    unsigned short clearFloraRadius;
    unsigned int   surfaceType;
    unsigned short noBuildRadius;
    unsigned char  onlyVisibleInTools;

  };
}
#endif
