/** -*-c++-*-
 *  \class  trn
 *  \file   trn.hpp
 *  \author Kenneth R. Sewell III

 meshLib is used for the parsing and exporting .trn models.
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

#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <memory>

#include <meshLib/trnAffector.hpp>
#include <meshLib/trnLayer.hpp>

#ifndef TRN_HPP
#define TRN_HPP

namespace ml
{
  class trn : public base
  {
  public:
    class sfam
    {
    public:
      unsigned int familyNumber;
      std::string name;
      std::string abstract;
      unsigned char rgb[3];
      float u1;
      float u2;

      std::map< std::string, float > shaderMap;
      
    };

    trn();
    ~trn();
    bool isRightType( std::istream &file )
    {
      return isOfType( file, "PTAT" );
    }
    unsigned int readTRN( std::istream &file,
			  const std::string &debugString = "" );

    const float &getTerrainSize() const
    {
      return terrainSize;
    }

    const float &getWaterTableHeight() const
    {
      return globalWaterTableHeight;
    }

    bool applyLayers( const float &originX,
		      const float &originY,
		      const float &spacingX,
		      const float &spacingY,
		      const unsigned int &numRows,
		      const unsigned int &numCols,
		      float *data) const;

  protected:
    unsigned int readTGEN( std::istream &file, const std::string & );
    unsigned int readTRNDATA( std::istream &file, const std::string & );
    unsigned int readMapDATA( std::istream &file, const std::string & );
    unsigned int readWMAP( std::istream &file, const std::string & );
    unsigned int readSMAP( std::istream &file, const std::string & );
    unsigned int readSGRP( std::istream &file, const std::string & );
    unsigned int readFGRP( std::istream &file, const std::string & );
    unsigned int readRGRP( std::istream &file, const std::string & );
    unsigned int readEGRP( std::istream &file, const std::string & );
    unsigned int readMGRP( std::istream &file, const std::string & );
    unsigned int readLYRS( std::istream &file, const std::string & );
    unsigned int readFFAM( std::istream &file, const std::string & );
    unsigned int readRFAM( std::istream &file, const std::string &rgrpType,
			   const std::string & );
    unsigned int readEFAM( std::istream &file, const std::string & );
    unsigned int readMFAM( std::istream &file, const std::string & );
    unsigned int readMFRC( std::istream &file, const std::string & );
    unsigned int readADTA( std::istream &file, const std::string & );
    unsigned int readSFAM( std::istream &file, const std::string &,
			   sfam &newSFAM );

  private:
    float terrainSize;
    float chunkWidth;
    unsigned int tilesPerChunk;

    float globalWaterTableHeight;
    float globalWaterTableShaderSize;
    std::string globalWaterTableShader;

    float tileSize;

    float collidableFloraMinDistance;
    float collidableFloraMaxDistance;
    float collidableFloraTileSize;
    float collidableFloraTileBorder;
    float collidableFloraSeed;

    float nonCollidableFloraMinDistance;
    float nonCollidableFloraMaxDistance;
    float nonCollidableFloraTileSize;
    float nonCollidableFloraTileBorder;
    float nonCollidableFloraSeed;

    float nearRadialFloraMinDistance;
    float nearRadialFloraMaxDistance;
    float nearRadialFloraTileSize;
    float nearRadialFloraTileBorder;
    float nearRadialFloraSeed;

    float farRadialFloraMinDistance;
    float farRadialFloraMaxDistance;
    float farRadialFloraTileSize;
    float farRadialFloraTileBorder;
    float farRadialFloraSeed;


    unsigned int mapHeight;
    unsigned int mapWidth;

    std::map<unsigned int, sfam> sfamMap;
    std::list<std::shared_ptr<trnLayer> > layerList;

  };
}
#endif
