/** -*-c++-*-
 *  \file   readTRN.cpp
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

#include <meshLib/trn.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int main( int argc, char **argv )
{

    if( 2 != argc )
    {
	std::cout << "readTRN <file>" << std::endl;
	return 0;
    }

    std::ifstream terrainFile( argv[1], std::ios_base::binary );

    if( !terrainFile.is_open() )
    {
	std::cout << "Unable to open file: " << argv[1] << std::endl;
	exit( 0 );
    }

    ml::trn terrain;
    terrain.readTRN( terrainFile );

    terrainFile.close();

    return 0;
}
