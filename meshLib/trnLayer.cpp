/** -*-c++-*-
 *  \class  trnLayer
 *  \file   trnLayer.cpp
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
#include <meshLib/trnLayer.hpp>

using namespace ml;

trnLayer::trnLayer()
{
}

trnLayer::~trnLayer()
{
}

void trnLayer::apply( const float &originX,
		      const float &originY,
		      const float &spacingX,
		      const float &spacingY,
		      const unsigned int &numRows,
		      const unsigned int &numCols,
		      float *data) const
{
  for( unsigned int row = 0; row < numRows; ++row )
    {
      float currentY = originY + ( spacingY * row );
      for( unsigned int col = 0; col < numCols; ++col )
	{
	  float currentX = originX + ( spacingX * col );
	  
	  if( isBounded && !isInBounds( currentX, currentY ) )
	    {
	      continue;
	    }
	  
	  unsigned int offset = (numCols * row)+col;
	  
	  for( std::list< std::shared_ptr<trnAffector> >::const_iterator
		 affector = affectorList.begin();
	       affector != affectorList.end();
	       ++affector )
	    {
	      (*affector)->apply( currentX, currentY, data[offset] );
	    }
	}
    }
  
  for( std::list< std::shared_ptr<trnLayer> >::const_iterator
	 currentLayer = layerList.begin();
       currentLayer != layerList.end();
       ++currentLayer )
    {
      (*currentLayer)->apply( originX,
			      originY,
			      spacingX,
			      spacingY,
			      numRows,
			      numCols,
			      data ) ;
    }
}

unsigned int trnLayer::read( std::istream &file,
			     const std::string &debugString )
{
  std::string dbgStr = debugString + "LAYR: ";
  unsigned int layrSize;

  unsigned int total = base::readFormHeader( file, "LAYR", layrSize );
  layrSize += 8;
  std::cout << debugString << "Found LAYR form" << std::endl;

  unsigned int size;
  total += base::readFormHeader( file, "0003", size );
  std::cout << dbgStr << "Found 0003 form" << std::endl;

  total += readIHDR( file, dbgStr  );
  total += readADTA( file, dbgStr );

  while( total < layrSize )
    {
      // Peek at next record, but keep file at same place.
      std::string form, type;
      base::peekHeader( file, form, size, type );

      if( form == "FORM" )
        {
          if( "ACCN" == type )
            {
	      std::shared_ptr<affectorColorConstant>
		newAffector(new affectorColorConstant);
	      total += newAffector->read( file, dbgStr );
	      affectorList.push_back( newAffector );
            }
          else if( "ACRF" == type )
            {
	      std::shared_ptr<affectorColorRampFractal>
		newAffector(new affectorColorRampFractal);
	      total += newAffector->read( file, dbgStr );
	      affectorList.push_back( newAffector );
            }
          else if( "ACRH" == type )
            {
	      std::shared_ptr<affectorColorRampHeight>
		newAffector(new affectorColorRampHeight);
	      total += newAffector->read( file, dbgStr );
	      affectorList.push_back( newAffector );
            }
          else if( "AENV" == type )
            {
	      std::shared_ptr<affectorEnvironment>
		newAffector(new affectorEnvironment);
	      total += newAffector->read( file, dbgStr );
	      affectorList.push_back( newAffector );
            }
          else if( "AEXC" == type )
            {
	      std::shared_ptr<affectorExclude>
		newAffector(new affectorExclude);
	      total += newAffector->read( file, dbgStr );
	      affectorList.push_back( newAffector );
            }
          else if( "AFDF" == type )
            {
	      std::shared_ptr<affectorRadialFarConstant>
		newAffector(new affectorRadialFarConstant);
	      total += newAffector->read( file, dbgStr );
	      affectorList.push_back( newAffector );
            }
          else if( "AFDN" == type )
            {
	      std::shared_ptr<affectorRadialConstant>
		newAffector(new affectorRadialConstant);
	      total += newAffector->read( file, dbgStr );
	      affectorList.push_back( newAffector );
            }
          else if( "AFSC" == type )
            {
	      std::shared_ptr<affectorFloraConstant>
		newAffector(new affectorFloraConstant);
	      total += newAffector->read( file, dbgStr );
	      affectorList.push_back( newAffector );
            }
          else if( "AFSN" == type )
            {
	      std::shared_ptr<affectorFloraNonCollidableConstant>
		newAffector(new affectorFloraNonCollidableConstant);
	      total += newAffector->read( file, dbgStr );
	      affectorList.push_back( newAffector );
            }
          else if( "AHCN" == type )
            {
	      std::shared_ptr<affectorHeightConstant>
		newAffector(new affectorHeightConstant);
	      total += newAffector->read( file, dbgStr );
	      affectorList.push_back( newAffector );
            }
          else if( "AHFR" == type )
            {
              std::shared_ptr<affectorHeightFractal>
                newAffector( new affectorHeightFractal );
	      total += newAffector->read( file, dbgStr );
	      affectorList.push_back( newAffector );
            }
          else if( "AHTR" == type )
            {
              std::shared_ptr<affectorHeightTerrace>
                newAffector( new affectorHeightTerrace );
	      total += newAffector->read( file, dbgStr );
	      affectorList.push_back( newAffector );
            }
          else if( "ARIV" == type )
            {
              std::shared_ptr<affectorRiver>
                newAffector( new affectorRiver );
	      total += newAffector->read( file, dbgStr );
	      affectorList.push_back( newAffector );
            }
          else if( "AROA" == type )
            {
              std::shared_ptr<affectorRoad>
                newAffector( new affectorRoad );
	      total += newAffector->read( file, dbgStr );
	      affectorList.push_back( newAffector );
            }
          else if( "ASCN" == type )
            {
              std::shared_ptr<affectorShaderConstant>
                newAffector( new affectorShaderConstant );
	      total += newAffector->read( file, dbgStr );
	      affectorList.push_back( newAffector );
            }
          else if( "ASRP" == type )
            {
              std::shared_ptr<affectorShaderReplace>
                newAffector( new affectorShaderReplace );
	      total += newAffector->read( file, dbgStr );
	      affectorList.push_back( newAffector );
            }
          else if( "BCIR" == type  )
            {
	      std::shared_ptr<boundaryCircle>
		newBoundary( new boundaryCircle );
	      total += newBoundary->read( file, dbgStr );
	      boundaryList.push_back( newBoundary );
              isBounded = true;
            }
          else if( "BPLN" == type  )
            {
	      std::shared_ptr<boundaryPolyline>
		newBoundary( new boundaryPolyline );
	      total += newBoundary->read( file, dbgStr );
	      boundaryList.push_back( newBoundary );
              isBounded = true;
            }
          else if( "BPOL" == type  )
            {
	      std::shared_ptr<boundaryPolygon>
		newBoundary( new boundaryPolygon );
	      total += newBoundary->read( file, dbgStr );
	      boundaryList.push_back( newBoundary );
              isBounded = true;
            }
          else if( "BREC" == type  )
            {
	      std::shared_ptr<boundaryRectangle>
		newBoundary( new boundaryRectangle );
	      total += newBoundary->read( file, dbgStr );
	      boundaryList.push_back( newBoundary );
              isBounded = true;
            }
          else if( "FDIR" == type  )
            {
              std::shared_ptr<affectorFilterDirection>
                newAffector( new affectorFilterDirection );
	      total += newAffector->read( file, dbgStr );
	      affectorList.push_back( newAffector );
            }
          else if( "FFRA" == type )
            {
              std::shared_ptr<affectorFilterFractal>
                newAffector( new affectorFilterFractal );
	      total += newAffector->read( file, dbgStr );
	      affectorList.push_back( newAffector );
            }
          else if( "FHGT" == type )
            {
              std::shared_ptr<affectorFilterHeight>
                newAffector( new affectorFilterHeight );
	      total += newAffector->read( file, dbgStr );
	      affectorList.push_back( newAffector );
            }
          else if( "FSHD" == type )
            {
              std::shared_ptr<affectorFilterShader>
                newAffector( new affectorFilterShader );
	      total += newAffector->read( file, dbgStr );
	      affectorList.push_back( newAffector );
            }
          else if( "FSLP" == type )
            {
              std::shared_ptr<affectorFilterSlope>
                newAffector( new affectorFilterSlope );
	      total += newAffector->read( file, dbgStr );
	      affectorList.push_back( newAffector );
            }
          else if( "LAYR" == type  )
            {
	      std::shared_ptr< trnLayer > subLayer( new trnLayer );
              layerList.push_back( subLayer );
              total += subLayer->read( file, dbgStr );
            }
          else
            {
              std::cout << "Unexpected form: " << type << std::endl;
              throw std::exception();
            }
        }
      else
        {
          std::cout << "Unexpected record: " << form << std::endl;
          throw std::exception();
        }
    }

  if( layrSize == total )
    {
      std::cout << debugString << "Finished reading LAYR" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading LAYR" << std::endl;
      std::cout << "Read " << total << " out of " << layrSize
                << std::endl;
    }
  return total;
}

bool trnLayer::isInBounds( const float &X, const float &Y ) const
{
  for( std::list< std::shared_ptr<trnBoundary> >::const_iterator
	 currentBoundary = boundaryList.begin();
       currentBoundary != boundaryList.end();
       ++currentBoundary )
    {
      if( (*currentBoundary)->isInBounds( X, Y ) )
	{
	  return true;
	}
    }

  return false;
}

unsigned int trnLayer::readIHDR( std::istream &file,
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

  file.read( (char *)&u1, sizeof( u1 ) );
  total += sizeof( u1 );

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

unsigned int trnLayer::readADTA( std::istream &file,
				 const std::string &debugString )
{
  std::string dbgStr = debugString + "ADTA: ";
  unsigned int adtaSize;
  std::string type;

  unsigned int total = base::readRecordHeader( file, type, adtaSize );
  if( type != "ADTA" )
    {
      std::cout << "Expected record of type ADTA: " << type << std::endl;
      throw std::exception();
    }
  std::cout << debugString << "Found ADTA record" << std::endl;

  unsigned int unknown1, unknown2, unknown3;
  total += base::read( file, unknown1 );
  total += base::read( file, unknown2 );
  total += base::read( file, unknown3 );

  std::string adtaName;
  total += base::read( file, adtaName );

  std::cout << dbgStr << unknown1 << " "
	    << unknown2 << " "
	    << unknown3 << " '"
	    << adtaName << "'" << std::endl;

  adtaSize += 8;
  if( adtaSize == total )
    {
      std::cout << debugString << "Finished reading ADTA" << std::endl;
    }
  else
    {
      std::cout << "Failed in reading ADTA" << std::endl;
      std::cout << "Read " << total << " out of " << adtaSize
		<< std::endl;
    }
  return total;
}

