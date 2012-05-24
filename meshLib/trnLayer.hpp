/** -*-c++-*-
 *  \class  trnLayer
 *  \file   trnLayer.hpp
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
#include <string>
#include <list>
#include <memory>

#include <meshLib/trnBoundary.hpp>
#include <meshLib/trnAffector.hpp>

#ifndef TRNLAYER_HPP
#define TRNLAYER_HPP

namespace ml
{
  class trnLayer
  {
  public:
    trnLayer();
    virtual ~trnLayer();
    virtual bool isInBounds( const float &X, const float &Y ) const;
    virtual void apply( const float &currentX,
			const float &currentY,
			const float &spacingX,
			const float &spacingY,
			const unsigned int &numRows,
			const unsigned int &numCols,
			float *data) const;
    unsigned int read( std::istream &file,
		       const std::string &debugString );

  protected:
    unsigned int readIHDR( std::istream &file, const std::string &debugString );
    unsigned int readADTA( std::istream &file, const std::string &debugString );

    bool isBounded;
    unsigned int u1;
    std::string name;

    std::list< std::shared_ptr<trnAffector> > affectorList;
    std::list< std::shared_ptr<trnLayer> > layerList;
    std::list< std::shared_ptr<trnBoundary> > boundaryList;
  };
}
#endif
