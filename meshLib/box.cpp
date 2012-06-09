/** -*-c++-*-
 *  \class  box
 *  \file   box.cpp
 *  \author Kenneth R. Sewell III

 meshLib is used for the parsing and exporting .msh models.
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

#include <meshLib/box.hpp>
#include <meshLib/base.hpp>
#include <cstdlib>

using namespace ml;

unsigned int box::readBOX( std::istream &file )
{
  unsigned int size;
  std::string type;

  unsigned int total = base::readRecordHeader( file, type, size );
  size += 8; // Size of header
  if( type != "BOX " )
    {
      std::cout << "Expected record of type BOX: " << type << std::endl;
      throw std::exception();
    }
  std::cout << "Found BOX record" << std::endl;

  // Read center and radius of bounding sphere
  total += base::read( file, x1 );
  total += base::read( file, y1 );
  total += base::read( file, z1 );
  total += base::read( file, x2 );
  total += base::read( file, y2 );
  total += base::read( file, z2 );

  std::cout << "Bounding box corners: " << std::endl;
  std::cout << "   " << x1 << ", " << y1 << ", " << z1 << std::endl;
  std::cout << "   " << x2 << ", " << y2 << ", " << z2 << std::endl;

  if( total == size )
    {
      std::cout << "Finished reading BOX." << std::endl;
    }
  else
    {
      std::cout << "Error reading BOX!" << std::endl;
      std::cout << "Read " << total << " out of " << size
		<< std::endl;
    }

  return total;
}

unsigned int box::writeBOX( std::ostream &file ) const
{
  std::streampos recordStart = file.tellp();

  unsigned int total = base::writeRecordHeader( file, "BOX ", 0 );

  // Read center and radius of bounding sphere
  total += base::write( file, x1 );
  total += base::write( file, y1 );
  total += base::write( file, z1 );
  total += base::write( file, x2 );
  total += base::write( file, y2 );
  total += base::write( file, z2 );

  std::streampos recordEnd = file.tellp();

  file.seekp( recordStart );
  base::writeRecordHeader( file, "BOX ", total );

  file.seekp( recordEnd );

  return total;
}
