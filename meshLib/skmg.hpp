/** -*-c++-*-
 *  \class  skmg
 *  \file   skmg.hpp
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

#include <fstream>
#include <string>
#include <vector>
#include <map>

#ifndef SKMG_HPP
#define SKMG_HPP

namespace ml
{
  class skmg : public model
  {
  public:
    
    class psdt
    {
    public:
      psdt( const skmg *newSkmg ):
	parentSkmg( newSkmg )
      {
      }

      const std::vector<unsigned int> &getTriangles() const;
      const std::vector<unsigned int> &getOTriangles( short group ) const;
      unsigned int getNumVertex() const;

      void getVertex( unsigned int index, float &X, float &Y, float &Z ) const;
      void getNormal( unsigned int index, float &NX, float &NY, float &NZ ) const;
      void getTexCoord( unsigned int index, float &U, float &V ) const;

      const std::string &getShader() const
      {
	return shaderFilename;
      }

      std::string shaderFilename;
      unsigned int numPos;
      unsigned int numNorm;
      std::vector<unsigned int> pidx;
      std::vector<unsigned int> nidx;
      std::vector<float> u;
      std::vector<float> v;
      std::map< short, std::vector<unsigned int> > oitl;
      std::vector<unsigned int> itl;
      const skmg *parentSkmg;
    };

    class blt
    {
    public:
      std::string name;
      unsigned int numPos;
      unsigned int numNorm;

      
    };

    skmg();
    ~skmg();
    bool isRightType( std::istream &file )
    {
      return isOfType( file, "SKMG" );
    }
    unsigned int readSKMG( std::istream &file );
    void print() const;

    const std::string &getShader() const
    {
      return shaderFilename;
    }

    unsigned int getNumSkeletons() const
    {
      return skeletonFilenameList.size();
    }

    const std::string &getSkeleton( unsigned int index ) const
    {
      return skeletonFilenameList[index];
    }

    unsigned int getNumGroups() const
    {
      return numBones;
    }

    unsigned int getNumPsdt() const
    {
      return psdtList.size();
    }

    const psdt &getPsdt( unsigned int index ) const
    {
      return psdtList[index];
    }
    
    const std::vector<float> &getXVector() const { return x; }
    const std::vector<float> &getYVector() const { return y; }
    const std::vector<float> &getZVector() const { return z; }

    const std::vector<float> &getNXVector() const { return nx; }
    const std::vector<float> &getNYVector() const { return ny; }
    const std::vector<float> &getNZVector() const { return nz; }

  protected:
    unsigned int readINFO( std::istream &file );

    unsigned int readSKTM( std::istream &file );
    unsigned int readXFNM( std::istream &file );
    unsigned int readPOSN( std::istream &file );
    unsigned int readTWHD( std::istream &file );
    unsigned int readTWDT( std::istream &file );
    unsigned int readNORM( std::istream &file );
    unsigned int readDOT3( std::istream &file );
    unsigned int readPSDT( std::istream &file, psdt &newPsdt );
    unsigned int readNAME( std::istream &file, psdt &newPsdt );
    unsigned int readBLTS( std::istream &file );
    unsigned int readBLT( std::istream &file, blt &newBlt );
    unsigned int readBLTPOSN( std::istream &file, unsigned int num );
    unsigned int readBLTNORM( std::istream &file, unsigned int num );
    unsigned int readBLTHPTS( std::istream &file );
    unsigned int readOZN( std::istream &file );
    unsigned int readFOZC( std::istream &file );
    unsigned int readOZC( std::istream &file );
    unsigned int readZTO( std::istream &file );
    unsigned int readTRTS( std::istream &file );
    unsigned int readBLTINFO( std::istream &file, blt &newBlt );
    unsigned int readDOT3Index( std::istream &file, psdt &newPsdt );

    unsigned int readPIDX( std::istream &file, psdt &newPsdt );
    unsigned int readNIDX( std::istream &file, psdt &newPsdt );
    unsigned int readVDCL( std::istream &file, psdt &newPsdt );
    unsigned int readTXCI( std::istream &file, psdt &newPsdt );
    unsigned int readTCSF( std::istream &file, psdt &newPsdt );
    unsigned int readTCSD( std::istream &file, psdt &newPsdt );
    unsigned int readPRIM( std::istream &file, psdt &newPsdt );
    unsigned int readPRIMINFO( std::istream &file, psdt &newPsdt );
    unsigned int readITL( std::istream &file, psdt &newPsdt );
    unsigned int readOITL( std::istream &file, psdt &newPsdt );

  private:
    std::vector<std::string> skeletonFilenameList;
    std::string shaderFilename;

    std::vector< std::string > boneNames;

    unsigned int numSkeletons;
    unsigned int numBones;
    unsigned int numPoints;
    unsigned int numNorm;
    unsigned int numPSDT;
    unsigned int numDot3;
    unsigned int numTwdt;
    unsigned int numIndex;
    unsigned int numBLT;

    std::vector<float> x;
    std::vector<float> y;
    std::vector<float> z;

    std::vector<float> nx;
    std::vector<float> ny;
    std::vector<float> nz;

    std::vector<unsigned int> numVertexWeights;
    std::vector< std::map<unsigned int, float> > vertexWeights;

    std::vector<blt> bltList;
    std::vector<psdt> psdtList;

  };
}
#endif
