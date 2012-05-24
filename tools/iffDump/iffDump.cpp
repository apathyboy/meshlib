/** -*-c++-*-
 *  \file   iffDump.cpp
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

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <cstdlib>

unsigned int numCols = 0;
unsigned int numRows = 0;

// Temp variable
unsigned int geodeCount = 0;

unsigned int readUnknown( std::ifstream &file,
		  const unsigned int size )
{
    for( unsigned int i = 0; i < size; ++i )
    {
        unsigned char data;
        file.read( (char*)&data, 1 );
        if(
	   ( data >= '.' && data <= '9' ) ||
	   ( data >= 'A' && data <= 'Z' ) ||
	   ( data >= 'a' && data <= 'z' ) ||
	   ( data == '\\' ) ||
	   ( data == '_' )
            )
        {
            std::cout << data;
        }
        else
        {
	  std::cout<< std::hex << "0x" << std::setw( 2 )
		   << std::setfill('0')
		   << (unsigned int)data
		   <<" " << std::dec;
        }
    }
    std::cout << std::endl;
    return size;
}

unsigned char readBigEndian( std::ifstream &file,
			     const unsigned int &size,
			     char *buffer
    )
{
#if BYTE_ORDER == LITTLE_ENDIAN
    for( unsigned int i=0; i<size; ++i )
    {
        file.read( &(buffer[size -1 - i]), 1 );
    }
#else
    file.read( buffer, size );
#endif
    
    return size;
}


int readGeometryDATA( std::ifstream &file,
		      unsigned int size,
		      unsigned int numVerts
    )
{
    unsigned int bytesPerVertex = size/numVerts;

    std::cout << std::fixed;
    std::cout << "Bytes per vertex: " << bytesPerVertex << std::endl;
    if( 32 == bytesPerVertex )
    {
	unsigned int numData = size/32;
	std::cout << "Num vertices: " << numData << std::endl;


	float x, y, z;
	float nx, ny, nz;
	float s, t;
	for( unsigned int i = 0; i < numData; ++i )
	{
	    file.read( (char *)&x, sizeof( x ) );
	    file.read( (char *)&y, sizeof( y ) );
	    file.read( (char *)&z, sizeof( z ) );
	    std::cout << x << " " << y << " " << z << " ";

	    file.read( (char *)&nx, sizeof( nx ) );
	    file.read( (char *)&ny, sizeof( ny ) );
	    file.read( (char *)&nz, sizeof( nz ) );
	    std::cout << nx << " " << ny << " " << nz << " ";

	    // Tex coords 0
	    // Tex coords 0
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << std::endl;
	}
    }
    else if( 36 == bytesPerVertex )
    {
	float x, y, z;
	float nx, ny, nz;
	float s, t;
	for( unsigned int i = 0; i < numVerts; ++i )
	{
	    file.read( (char *)&x, sizeof( x ) );
	    file.read( (char *)&y, sizeof( y ) );
	    file.read( (char *)&z, sizeof( z ) );
	    std::cout << x << " " << y << " " << z << " ";

	    file.read( (char *)&nx, sizeof( nx ) );
	    file.read( (char *)&ny, sizeof( ny ) );
	    file.read( (char *)&nz, sizeof( nz ) );
	    std::cout << nx << " " << ny << " " << nz << " ";

	    unsigned char color[4];
	    file.read( (char *)color, 4 );
	    std::cout << (unsigned int)color[0] << " "
		      << (unsigned int)color[1] << " "
		      << (unsigned int)color[2] << " "
		      << (unsigned int)color[3] << " ";


	    // Tex coords 0
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << std::endl;
	}
    }
    else if( 40 == bytesPerVertex )
    {
	float x, y, z;
	float nx, ny, nz;
	float s, t;
	for( unsigned int i = 0; i < numVerts; ++i )
	{
	    file.read( (char *)&x, sizeof( x ) );
	    file.read( (char *)&y, sizeof( y ) );
	    file.read( (char *)&z, sizeof( z ) );
	    std::cout << x << " " << y << " " << z << " ";

	    file.read( (char *)&nx, sizeof( nx ) );
	    file.read( (char *)&ny, sizeof( ny ) );
	    file.read( (char *)&nz, sizeof( nz ) );
	    std::cout << nx << " " << ny << " " << nz << " ";

	    // Tex coords 0
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << " ";

	    // Tex coords 1
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << std::endl;
	}
    }
    else if( bytesPerVertex == 44 )
    {
	float x, y, z;
	float nx, ny, nz;
	float s, t;
	for( unsigned int i = 0; i < numVerts; ++i )
	{
	    file.read( (char *)&x, sizeof( x ) );
	    file.read( (char *)&y, sizeof( y ) );
	    file.read( (char *)&z, sizeof( z ) );
	    std::cout << x << " " << y << " " << z << " ";

	    file.read( (char *)&nx, sizeof( nx ) );
	    file.read( (char *)&ny, sizeof( ny ) );
	    file.read( (char *)&nz, sizeof( nz ) );
	    std::cout << nx << " " << ny << " " << nz << " ";

	    unsigned char color[4];
	    file.read( (char *)color, 4 );
	    std::cout << (unsigned int)color[0] << " "
		      << (unsigned int)color[1] << " "
		      << (unsigned int)color[2] << " "
		      << (unsigned int)color[3] << " ";

	    // Tex coords 0
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << " ";

	    // Tex coords 1
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << std::endl;
	}
    }
    else if( 48 == bytesPerVertex )
    {
	float x, y, z;
	float nx, ny, nz;
	float s, t;
	for( unsigned int i = 0; i < numVerts; ++i )
	{
	    file.read( (char *)&x, sizeof( x ) );
	    file.read( (char *)&y, sizeof( y ) );
	    file.read( (char *)&z, sizeof( z ) );
	    std::cout << x << " " << y << " " << z << " ";

	    file.read( (char *)&nx, sizeof( nx ) );
	    file.read( (char *)&ny, sizeof( ny ) );
	    file.read( (char *)&nz, sizeof( nz ) );
	    std::cout << nx << " " << ny << " " << nz << " ";

	    // Tex coords 0
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << " ";

	    // Tex coords 1
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << " ";

	    // Tex coords 2
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << std::endl;
	}
    }
    else if( 52 == bytesPerVertex )
    {
	float x, y, z;
	float nx, ny, nz;
	float s, t;
	for( unsigned int i = 0; i < numVerts; ++i )
	{
	    file.read( (char *)&x, sizeof( x ) );
	    file.read( (char *)&y, sizeof( y ) );
	    file.read( (char *)&z, sizeof( z ) );
	    std::cout << x << " " << y << " " << z << " ";

	    file.read( (char *)&nx, sizeof( nx ) );
	    file.read( (char *)&ny, sizeof( ny ) );
	    file.read( (char *)&nz, sizeof( nz ) );
	    std::cout << nx << " " << ny << " " << nz << " ";

	    unsigned char color[4];
	    file.read( (char *)color, 4 );
	    std::cout << (unsigned int)color[0] << " "
		      << (unsigned int)color[1] << " "
		      << (unsigned int)color[2] << " "
		      << (unsigned int)color[3] << " ";

	    // Tex coords 0
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << " ";

	    // Tex coords 1
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << " ";

	    // Tex coords 2
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << std::endl;
	}
    }
    else if( 56 == bytesPerVertex )
    {
	float x, y, z;
	float nx, ny, nz;
	float s, t;
	for( unsigned int i = 0; i < numVerts; ++i )
	{
	    file.read( (char *)&x, sizeof( x ) );
	    file.read( (char *)&y, sizeof( y ) );
	    file.read( (char *)&z, sizeof( z ) );
	    std::cout << x << " " << y << " " << z << " ";

	    file.read( (char *)&nx, sizeof( nx ) );
	    file.read( (char *)&ny, sizeof( ny ) );
	    file.read( (char *)&nz, sizeof( nz ) );
	    std::cout << nx << " " << ny << " " << nz << " ";

	    // Tex coords 0
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << " ";

	    // Tex coords 1
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << " ";

	    // Tex coords 2
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << " ";

	    // Tex coords 3
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << std::endl;
	}
    }
    else if( 60 == bytesPerVertex )
    {
	float x, y, z;
	float nx, ny, nz;
	float s, t;
	for( unsigned int i = 0; i < numVerts; ++i )
	{
	    file.read( (char *)&x, sizeof( x ) );
	    file.read( (char *)&y, sizeof( y ) );
	    file.read( (char *)&z, sizeof( z ) );
	    std::cout << x << " " << y << " " << z << " ";

	    file.read( (char *)&nx, sizeof( nx ) );
	    file.read( (char *)&ny, sizeof( ny ) );
	    file.read( (char *)&nz, sizeof( nz ) );
	    std::cout << nx << " " << ny << " " << nz << " ";

	    unsigned char color[4];
	    file.read( (char *)color, 4 );
	    std::cout << (unsigned int)color[0] << " "
		      << (unsigned int)color[1] << " "
		      << (unsigned int)color[2] << " "
		      << (unsigned int)color[3] << " ";

	    // Tex coords 0
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << " ";

	    // Tex coords 1
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << " ";

	    // Tex coords 2
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << " ";

	    // Tex coords 3
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << std::endl;
	}
    }
    else if( 64 == bytesPerVertex )
    {
	float x, y, z;
	float nx, ny, nz;
	float s, t;
	for( unsigned int i = 0; i < numVerts; ++i )
	{
	    file.read( (char *)&x, sizeof( x ) );
	    file.read( (char *)&y, sizeof( y ) );
	    file.read( (char *)&z, sizeof( z ) );
	    std::cout << x << " " << y << " " << z << " ";

	    file.read( (char *)&nx, sizeof( nx ) );
	    file.read( (char *)&ny, sizeof( ny ) );
	    file.read( (char *)&nz, sizeof( nz ) );
	    std::cout << nx << " " << ny << " " << nz << " ";

	    // Tex coords 0
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << " ";

	    // Tex coords 1
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << " ";

	    // Tex coords 2
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << " ";

	    // Tex coords 3
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << " ";

	    // Tex coords 4
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << std::endl;
	}
    }
    else if( 68 == bytesPerVertex )
    {
	float x, y, z;
	float nx, ny, nz;
	float s, t;
	for( unsigned int i = 0; i < numVerts; ++i )
	{
	    file.read( (char *)&x, sizeof( x ) );
	    file.read( (char *)&y, sizeof( y ) );
	    file.read( (char *)&z, sizeof( z ) );
	    std::cout << x << " " << y << " " << z << " ";

	    file.read( (char *)&nx, sizeof( nx ) );
	    file.read( (char *)&ny, sizeof( ny ) );
	    file.read( (char *)&nz, sizeof( nz ) );
	    std::cout << nx << " " << ny << " " << nz << " ";

	    unsigned char color[4];
	    file.read( (char *)color, 4 );
	    std::cout << (unsigned int)color[0] << " "
		      << (unsigned int)color[1] << " "
		      << (unsigned int)color[2] << " "
		      << (unsigned int)color[3] << " ";

	    // Tex coords 0
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << " ";

	    // Tex coords 1
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << " ";

	    // Tex coords 2
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << " ";

	    // Tex coords 3
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << " ";

	    // Tex coords 4
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << std::endl;
	}
    }
    else if( 72 == bytesPerVertex )
    {
	float x, y, z;
	float nx, ny, nz;
	float s, t;
	for( unsigned int i = 0; i < numVerts; ++i )
	{
	    file.read( (char *)&x, sizeof( x ) );
	    file.read( (char *)&y, sizeof( y ) );
	    file.read( (char *)&z, sizeof( z ) );
	    std::cout << x << " " << y << " " << z << " ";

	    file.read( (char *)&nx, sizeof( nx ) );
	    file.read( (char *)&ny, sizeof( ny ) );
	    file.read( (char *)&nz, sizeof( nz ) );
	    std::cout << nx << " " << ny << " " << nz << " ";

	    // Tex coords 0
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << " ";

	    // Tex coords 1
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << " ";

	    // Tex coords 2
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << " ";

	    // Tex coords 3
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << " ";

	    // Tex coords 4
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << std::endl;

	    // Tex coords 4
	    file.read( (char *)&s, sizeof( s ) );
	    std::cout << s << " ";
	    file.read( (char *)&t, sizeof( t ) );
	    std::cout << t << std::endl;
	}
    }
    else
    {
	file.seekg( size, std::ios_base::cur );
    }

    return size;
}

int readGeometryINDX( std::ifstream &file, unsigned int size )
{
    unsigned int numIndex;
    file.read( (char *)&numIndex, sizeof( numIndex ) );
    std::cout << "Num index: " << numIndex << std::endl;
    std::cout << "Num triangles: " << numIndex/3 << std::endl;

    unsigned int bytesPerIndex = (size-4)/numIndex;

    if( bytesPerIndex == 2 )
    {
	unsigned short index;
	for( unsigned int i = 0; i < numIndex; ++i )
	{
	    file.read( (char *)&index, sizeof( index ) );
	}
    }
    else
    {
	unsigned int index;
	for( unsigned int i = 0; i < numIndex; ++i )
	{
	    file.read( (char *)&index, sizeof( index ) );
	}
    }

    return size;
}


int readRecord(
    std::ifstream &file,
    unsigned int level,
    std::deque<std::string> parentForms
    )
{
    static unsigned int numVerts = 0;

    bool isMainTexture = false;

    std::cout << std::endl;
    char buffer[10000];
    char temp[5];
    std::string group;

    file.read( temp, 4 );
    if( file.eof() )
    {
	return 0;
    }
    temp[4] = 0;
    group = temp;
    std::cout << "***** LEVEL " << level << " *****" << std::endl;

    std::cout << "Group: '" << group << "'" << std::endl;
    
    unsigned int size = 0;
    readBigEndian(
	file,
	sizeof( size ),
	(char *)&size
	);
    std::cout << "Size: " << size << std::endl;

    if( "FORM" == group )
    {
	std::string type;
	file.read( temp, 4 );
	temp[4] = 0;
	type = temp;
	if( type == "0001" )
	{
	    std::cout << "Type: 0001" << std::endl;
	}
	else if( type == "0003" )
	{
	    std::cout << "Type: 0003" << std::endl;
	}
	else if( type == "EXBX" )
	{
	    std::cout << "Type: " << type << " (Bounding Box)" << std::endl;
	}
	else if( type == "EXSP" )
	{
	    std::cout << "Type: " << type << " (Bounding Sphere)" << std::endl;
	}
	else if( type == "HPNT" )
	{
	    std::cout << "Type: " << type << " (Hardpoint)" << std::endl;
	}
	else if( type == "CPIT" )
	{
	    std::cout << "Type: " << type << " (Cockpit)" << std::endl;
	}
	else if( type == "FCHS" )
	{
	    std::cout << "Type: " << type << " (Free chase camera)"
		      << std::endl;
	}
	else if( type == "TXMS" )
	{
	    std::cout << "Type: " << type << " (Texture maps)" << std::endl;
	}
	else if( type == "TXM " )
	{
	    std::cout << "Type: " << type << " (Texture map)" << std::endl;
	}
	else if( type == "CACH" )
	{
	    std::cout << "Type: " << type << " (Cache)" << std::endl;
	}
	else if( type == "SD2D" )
	{
	    std::cout << "Type: " << type << " (2-D Sound)" << std::endl;
	}
	else
	{
	    std::cout << "Type: '" << type << "'" << std::endl;
	}
	size -= 4;

	unsigned int sizeLeft = size;
	unsigned int sizeRead;
	parentForms.push_back( type );
	while( 0 != sizeLeft )
	{
	    sizeRead = readRecord( file, level+1, parentForms );
	    if( sizeRead > sizeLeft )
	    {
		std::cout << "Error size mismatch!" << std::endl;
		exit( 0 );
	    }
	    sizeLeft -= sizeRead;
	    std::cout << type << " sizeLeft: " << sizeLeft << std::endl;
	}
	// Size of data plus 12 bytes of FORM header
	return size+12;
    }
    else if( "SPHR" == group )
    {
	float X, Y, Z, R;
	
	file.read( (char *)&X, sizeof( X ) );
	file.read( (char *)&Y, sizeof( Y ) );
	file.read( (char *)&Z, sizeof( Z ) );
	file.read( (char *)&R, sizeof( R ) );
	
	std::cout << "X: " << X << std::endl;
	std::cout << "Y: " << Y << std::endl;
	std::cout << "Z: " << Z << std::endl;
	std::cout << "R: " << R << std::endl;
    }
    else if( "BOX " == group )
    {
	float x1, x2, y1, y2, z1, z2;

	file.read( (char *)&x1, sizeof( x1 ) );
	file.read( (char *)&y1, sizeof( y1 ) );
	file.read( (char *)&z1, sizeof( z1 ) );
	file.read( (char *)&x2, sizeof( x2 ) );
	file.read( (char *)&y2, sizeof( y2 ) );
	file.read( (char *)&z2, sizeof( z2 ) );

	std::cout << "X1: " << x1 << std::endl;
	std::cout << "Y1: " << y1 << std::endl;
	std::cout << "Z1: " << z1 << std::endl;
	std::cout << "X2: " << x2 << std::endl;
	std::cout << "Y2: " << y2 << std::endl;
	std::cout << "Z2: " << z2 << std::endl;
    }
    else if( "DATA" == group )
    {
	for( unsigned int i = 0; i < parentForms.size(); ++i )
	{
	    std::cout << parentForms[i] << "-";
	}
	std::cout << std::endl;

	if( "TXM " == parentForms[parentForms.size()-2] )
	{
	    char tempType[5];
	    tempType[4] = 0;
	    file.read( tempType, 4 );
	    std::string textureType( tempType );

	    isMainTexture = false;
	    if( "PUKL" == textureType  )
	    {
		std::cout << "Specular lookup texture ";
	    }
	    else if( "EBUC" == textureType  )
	    {
		std::cout << "Cube map texture ";
	    }
	    else if( "NIAM" == textureType  )
	    {
		std::cout << "Main texture ";
		isMainTexture = true;
	    }
	    else if( "LMRN" == textureType  )
	    {
		std::cout << "Normal map texture ";
	    }
	    else
	    {
		std::cout << textureType << " ";
	    }


	    // Data is a filename
	    unsigned char data;
	    for( unsigned int i = 0; i < size-4; ++i )
	    {
		file.read( (char*)&data, sizeof( data ) );
		std::cout << (unsigned int)data << " ";
	    }
	    std::cout << std::endl;
	}
	else if( "0001" == parentForms.back() )
	{
	    readUnknown( file, size );
	}
	else if( "0004" == parentForms.back() )
	{
	    readUnknown( file, size );
	}
	else if( "0008" == parentForms.back() )
	{
	    unsigned short data2;
	    file.read( (char*)&data2, sizeof( data2 ) );
	    std::cout << data2 << std::endl;
	    file.read( (char*)&data2, sizeof( data2 ) );
	    std::cout << data2 << std::endl;
	    file.read( (char*)&data2, sizeof( data2 ) );
	    std::cout << data2 << std::endl;
	    file.read( (char*)&data2, sizeof( data2 ) );
	    std::cout << data2 << std::endl;
	    file.read( (char*)&data2, sizeof( data2 ) );
	    std::cout << data2 << std::endl;
	    file.read( (char*)&data2, sizeof( data2 ) );
	    std::cout << data2 << std::endl;

	    // Data is a filename
	    unsigned char data;
	    for( unsigned int i = 0; i < size-12; ++i )
	    {
		file.read( (char*)&data, sizeof( data ) );
		if( i < 4 )
		{
		    std::cout << data << " ";
		}
		else
		{
		    std::cout << (unsigned int)data << " ";
		}
	    }
	    std::cout << std::endl;
	}
	else
	{
	    if( numVerts != 0 )
	    {
		readGeometryDATA( file, size, numVerts );
		numVerts = 0;
	    }
	    else
	    {
		readUnknown( file, size );
	    }
	}
    }
    else if( "CNT " == group )
    {
	unsigned int data;
	file.read( (char *)&data, sizeof( data ) );
	std::cout << "data: " << data << std::endl;
    }
    else if( "NAME" == group )
    {
	file.read( buffer, size );
	buffer[size] = 0;
	std::string name( buffer );
	std::cout << name << std::endl;
    }
    else if( "INFO" == group )
    {
	if( 8 == size )
	{
	    unsigned int data;
	    file.read( (char *)&data, sizeof( data ) );
	    std::cout << "Unknown: " << data << std::endl;
	    file.read( (char *)&numVerts, sizeof( numVerts ) );
	    std::cout << "numVerts: " << numVerts << std::endl;
	}
	else
	{
	    readUnknown( file, size );
	}
    }
    else if( "INDX" == group )
    {
#if 0
      readUnknown( file, size );
#else
      readGeometryINDX( file, size );
#endif
    }
    else if( "MATL" == group )
    {
	if( 68 != size )
	{
	    std::cout << "Expected MATL to be 68bytes!!!!!!!!!" << std::endl;
	    exit( 0 );
	}

	// Data in abgr?
	float data;
	std::cout << "Ambient: ";
	for( unsigned int i = 0; i < 4; ++i )
	{
	    file.read( (char *)&data, sizeof( data ) );
	    std::cout << (unsigned int)data << " ";
	}
	std::cout << std::endl;

	std::cout << "Diffuse: ";
	for( int i = 0; i < 4; ++i )
	{
	    file.read( (char *)&data, sizeof( data ) );
	    std::cout << (unsigned int)data << " ";
	}
	std::cout << std::endl;

	std::cout << "Specular: ";
	for( int i = 0; i < 4; ++i )
	{
	    file.read( (char *)&data, sizeof( data ) );
	    std::cout << (unsigned int)data << " ";
	}
	std::cout << std::endl;
	
	std::cout << "Emissive: ";
	for( int i = 0; i < 4; ++i )
	{
	    file.read( (char *)&data, sizeof( data ) );
	    std::cout << (unsigned int)data << " ";
	}
	std::cout << std::endl;

	std::cout << "Shininess: ";
	file.read( (char *)&data, sizeof( data ) );
	std::cout << (unsigned int)data << std::endl;
	
    }
    else if( "NIAM" == group )
    {
	file.seekg( size, std::ios_base::cur );
    }
    else if( "0000" == group )
    {

	if( "TCSS" == parentForms.back() ||
	    "ARVS" == parentForms.back() )
	{
	    unsigned int numEntry = size/5;
	    
	    for( unsigned int j = 0; j < numEntry; ++j )
	    {
		unsigned char data;
		for( int i = 0; i < 4; ++i )
		{
		    file.read( (char *)&data, sizeof( data ) );
		    std::cout << data;
		}
		
		file.read( (char *)&data, sizeof( data ) );
		std::cout << (unsigned int)data << std::endl;
	    }
	}
	else if( "TFNS" == parentForms.back() )
	{
	    unsigned int numColors = size/8;
	    for( unsigned int j = 0; j < numColors; ++j )
	    {
		char tempColor[5];
		file.read( tempColor, 4 );
		tempColor[4] = 0;
		std::string color( tempColor );
		std::cout << "color: " << color << " "; 
		
		unsigned char data;
		for( int i = 0; i < 4; ++i )
		{
		    file.read( (char *)&data, sizeof( data ) );
		    std::cout << (unsigned int)data << " ";
		}
		std::cout << std::endl;
	    }
	}
	else if( "STAG" == parentForms.back() )
	{
	    unsigned short data1;
	    for( unsigned int i = 0; i < 9; ++i )
	    {
		file.read( (char *)&data1, sizeof( data1 ) );
		std::cout << (unsigned int)data1 << " ";
	    }

	    unsigned char data;
	    for( unsigned int i = 0; i < 8; ++i )
	    {
		file.read( (char *)&data, sizeof( data ) );
		std::cout << data << " ";
	    }

	    for( unsigned int i = 0; i < 7; ++i )
	    {
		file.read( (char *)&data, sizeof( data ) );
		std::cout << (unsigned int)data << " ";
	    }
	    std::cout << std::endl;
	}
	else
	{
	    readUnknown( file, size );
	}
    }
    else if( "0001" == group )
    {
 	readUnknown( file, size );
    }
    else if( "0002" == group )
    {
 	readUnknown( file, size );
    }
    else if( "0003" == group )
    {
 	readUnknown( file, size );
    }
    else if( "0005" == group )
    {
 	readUnknown( file, size );
    }
    else if( "TAG " == group )
    {
	file.read( buffer, size );
	buffer[size] = 0;
	std::string tag( buffer );
	std::cout << tag << std::endl;
    }
    else if( "SCAP" == group )
    {
 	readUnknown( file, size );
    }
    else if( "OPTN" == group )
    {
 	readUnknown( file, size );
    }
    else if( "XFIN" == group )
    {
 	readUnknown( file, size );
    }
    else if( "LINK" == group )
    {
 	readUnknown( file, size );
    }
    else if( "QCHN" == group )
    {
 	readUnknown( file, size );
    }
    else if( "SROT" == group )
    {
 	readUnknown( file, size );
    }
    else if( "CHNL" == group )
    {
	readUnknown( file, size );
    }
    else if( "STRN" == group )
    {
	readUnknown( file, size );
    }
    else if( "SFAM" == group )
    {
#if 0
	char temp[255];
	unsigned int num;
	file.read( (char *)&num, sizeof( num ) );
	std::cout << "Num: " << num << std::endl;

	std::string name;
	file.getline( temp, 255, 0 );
	name = temp;
	std::cout << "Name: " << name << std::endl;

	std::string name2;
	file.getline( temp, 255, 0 );
	name2 = temp;
	std::cout << "Name2: " << name2 << std::endl;

	float f;
	unsigned int i;
	unsigned char c;

	file.read( (char *)&c, sizeof( c ) );
	std::cout << (unsigned int)c << " ";

	file.read( (char *)&c, sizeof( c ) );
	std::cout << (unsigned int)c << " ";

	file.read( (char *)&c, sizeof( c ) );
	std::cout << (unsigned int)c << " ";

	file.read( (char *)&f, sizeof( f ) );
	std::cout << f << " ";

	file.read( (char *)&f, sizeof( f ) );
	std::cout << f << " ";

	file.read( (char *)&i, sizeof( i ) );
	std::cout << i << " ";
	std::cout << std::endl;
	
	std::string name3;
	file.getline( temp, 255, 0 );
	name3 = temp;
	std::cout << "Name3: " << name3 << std::endl;

	file.read( (char *)&f, sizeof( f ) );
	std::cout << f << std::endl;
#else
	readUnknown( file, size );
#endif
    }
    else if( "FFAM" == group )
    {
	readUnknown( file, size );
    }
    else if( "RFAM" == group )
    {
	readUnknown( file, size );
    }
    else if( "ADTA" == group )
    {
	readUnknown( file, size );
    }
    else if( "PARM" == group )
    {
	readUnknown( file, size );
    }
    else if( "SGMT" == group )
    {
	readUnknown( file, size );
    }
    else if( "WMAP" == group )
    {
	readUnknown( file, size );
    }
    else if( "SMAP" == group )
    {
	readUnknown( file, size );
    }
    else if( "XXXX" == group )
    {
	readUnknown( file, size );
    }
    else if( "PCNT" == group )
    {
	if( 4 == size )
	{
	    int data;
	    file.read( (char*)&data, sizeof( data ) );
	    std::cout << "Sibling Nodes: " << data << std::endl;
	}
	else
	{
	    readUnknown( file, size );
	}
    }
    else if( "NODE" == group )
    {
	std::string name;
	file.width( size - 52 );
	file >> name;
	std::cout << name << std::endl;

	std::string r;
	file.width( 4 );
	file >> r;
	std::cout << r << std::endl;

	float data;
	std::cout << std::fixed;
	for( unsigned int i = 0; i < 12; ++i )
	{
	    file.read( (char*)&data, sizeof( data ) );
	    std::cout << data << " ";
	    if( ((i+1) % 4) == 0 )
	    {
		std::cout << std::endl;
	    }
	}
	std::cout << std::endl;
    }
    else if( "CSND" == group )
    {
	readUnknown( file, size );
    }
    else if( "CEFT" == group )
    {
	readUnknown( file, size );
    }
    else if( "MESH" == group )
    {
	readUnknown( file, size );
    }
    else if( "PALV" == group )
    {
	readUnknown( file, size );
    }
    else if( "VERT" == group )
    {
	readUnknown( file, size );
    }
    else if( "TRIS" == group )
    {
	readUnknown( file, size );
    }
    else if( "NODS" == group )
    {
	readUnknown( file, size );
    }
    else if( "BEDG" == group )
    {
	readUnknown( file, size );
    }
    else if( "PEDG" == group )
    {
	readUnknown( file, size );
    }
    else if( "META" == group )
    {
 	readUnknown( file, size );
   }
    else if( "PNOD" == group )
    {
	readUnknown( file, size );
    }
    else if( "ECNT" == group )
    {
	readUnknown( file, size );
    }
    else if( "ESTR" == group )
    {
	readUnknown( file, size );
    }
    else if( "HPNT" == group ) // Lightsource?
    {
	float data1;
	file.read( (char *)&data1, sizeof( data1 ) );
	std::cout << data1 << " ";
	file.read( (char *)&data1, sizeof( data1 ) );
	std::cout << data1 << " ";
	file.read( (char *)&data1, sizeof( data1 ) );
	std::cout << data1 << " ";
	file.read( (char *)&data1, sizeof( data1 ) );
	std::cout << data1 << std::endl;
	file.read( (char *)&data1, sizeof( data1 ) );
	std::cout << data1 << " ";
	file.read( (char *)&data1, sizeof( data1 ) );
	std::cout << data1 << " ";
	file.read( (char *)&data1, sizeof( data1 ) );
	std::cout << data1 << " ";
	file.read( (char *)&data1, sizeof( data1 ) );
	std::cout << data1 << std::endl;
	file.read( (char *)&data1, sizeof( data1 ) );
	std::cout << data1 << " ";
	file.read( (char *)&data1, sizeof( data1 ) );
	std::cout << data1 << " ";
	file.read( (char *)&data1, sizeof( data1 ) );
	std::cout << data1 << " ";
	file.read( (char *)&data1, sizeof( data1 ) );
	std::cout << data1 << std::endl;

	readUnknown( file, size-48 );
    }
    else if( "SIDX" == group )
    {
	unsigned int num;
	file.read( (char *)&num, sizeof( num ) );
	std::cout << "Num: " << num << std::endl;

	for( unsigned int j = 0; j < num; ++j )
	{
	    float x1;
	    file.read( (char *)&x1, sizeof( x1 ) );
	    std::cout << "Unknown: " << x1 << std::endl;
	    file.read( (char *)&x1, sizeof( x1 ) );
	    std::cout << "Unknown: " << x1 << std::endl;
	    file.read( (char *)&x1, sizeof( x1 ) );
	    std::cout << "Unknown: " << x1 << std::endl;
	    unsigned int numIndex;
	    file.read( (char *)&numIndex, sizeof( numIndex ) );
	    std::cout << "Num index: " << numIndex << std::endl;
	    
	    unsigned short data;
	    for( unsigned int i = 0; i < numIndex; ++i )
	    {
		file.read( (char *)&data, sizeof( data ) );
		std::cout << data << " ";
	    }
	    std::cout << std::endl;
	}
    }
    else if( "MSGN" == group )
    {
	readUnknown( file, size );
    }
    else if( "SKTI" == group )
    {
	readUnknown( file, size );
    }
    else if( "PIVT" == group )
    {
	readUnknown( file, size );
    }
    else if( "CHLD" == group )
    {
#if 0
	unsigned int lodNum;
	file.read( (char *)&lodNum, sizeof( lodNum ) );
	std::cout << "LOD" << lodNum << ": ";
	unsigned char data;
	for( int i = 0; i < size-4; ++i )
	{
	    file.read( (char *)&data, sizeof( data ) );
	    std::cout << data;
	}
	std::cout << std::endl;
#else
	readUnknown( file, size );
#endif
    }
    else if( "PAL " == group )
    {
	readUnknown( file, size );
    }
    else if( "ASND" == group )
    {
	readUnknown( file, size );
    }
    else if( "HOBJ" == group )
    {
	readUnknown( file, size );
    }
    else if( "TEXT" == group )
    {
	readUnknown( file, size );
    }
    else if( "TYPS" == group )
    {
	readUnknown( file, size );
    }
    else if( "VOLT" == group )
    {
	readUnknown( file, size );
    }
    else if( "PRVT" == group )
    {
	readUnknown( file, size );
    }
    else if( "SKCT" == group )
    {
	readUnknown( file, size );
    }
    else if( "PSND" == group )
    {
	readUnknown( file, size );
    }
    else if( "FRAM" == group )
    {
	readUnknown( file, size );
    }
    else if( "ZOOM" == group )
    {
	readUnknown( file, size );
    }
    else if( "FRST" == group )
    {
	readUnknown( file, size );
    }
    else if( "3OFF" == group )
    {
	readUnknown( file, size );
    }
    else if( "1OFF" == group )
    {
	readUnknown( file, size );
    }
    else if( "DEFH" == group )
    {
	readUnknown( file, size );
    }
    else if( "PUNF" == group )
    {
	readUnknown( file, size );
    }
    else if( "ACTN" == group )
    {
	readUnknown( file, size );
    }
    else if( "PRNT" == group )
    {
	readUnknown( file, size );
    }
    else if( "RPRE" == group )
    {
	readUnknown( file, size );
    }
    else if( "RPST" == group )
    {
	readUnknown( file, size );
    }
    else if( "BPTR" == group )
    {
	readUnknown( file, size );
    }
    else if( "BPRO" == group )
    {
	readUnknown( file, size );
    }
    else if( "JROR" == group )
    {
	readUnknown( file, size );
    }
    else if( "KEY " == group )
    {
	readUnknown( file, size );
    }
    else if( "DISP" == group )
    {
	readUnknown( file, size );
    }
    else if( "POST" == group )
    {
	readUnknown( file, size );
    }
    else if( "INT " == group )
    {
	readUnknown( file, size );
    }
    else if( "FLOT" == group )
    {
	readUnknown( file, size );
    }
    else if( "PROB" == group )
    {
	readUnknown( file, size );
    }
    else if( "SKIL" == group )
    {
	readUnknown( file, size );
    }
    else if( "ITEM" == group )
    {
	readUnknown( file, size );
    }
    else if( "CODE" == group )
    {
	readUnknown( file, size );
    }
    else if( "COLS" == group )
    {
	file.read( (char*)&numCols, sizeof( numCols ) );

	std::cout << "Num columns: " << numCols << std::endl;

	char temp[255];
	for( unsigned int i = 0; i < numCols; ++i )
	{
	    file.getline( temp, 255, 0 );
	    std::string name( temp );
	    std::cout << i << ": " << name << std::endl;
	}
    }
    else if( "TYPE" == group )
    {
	char temp[255];
	for( unsigned int i = 0; i < numCols; ++i )
	{
	    file.getline( temp, 255, 0 );
	    std::string name( temp );
	    std::cout << i << ": " << name << std::endl;
	}
    }
    else if( "ROWS" == group )
    {
#if 0
	file.read( (char*)&numRows, sizeof( numRows ) );

	std::cout << "Num rows: " << numRows << std::endl;

	char temp[255];
	for( unsigned int i = 0; i < numRows; ++i )
	{
	    file.getline( temp, 255, 0 );
	    std::string name = temp;
	    std::cout << i << ": " << name << std::endl;
	}
#else
	readUnknown( file, size );
#endif
    }
    else if( "PSTR" == group )
    {
	readUnknown( file, size );
    }
    else if( "OTNL" == group )
    {
	unsigned int num;
	file.read( (char*)&num, sizeof( num ) );
	std::cout << num << std::endl;
	char temp[512];

	for( unsigned int i = 0; i < num; ++i )
	{
	    file.getline( temp, 512, 0 );
	    std::cout << temp << std::endl;
	}
	//readUnknown( file, size-4 );
    }
    else if( "NSKY" == group ) // Night sky?
    {
	readUnknown( file, size );
    }
    else if( "STAR" == group )
    {
	readUnknown( file, size );
    }
    else if( "SUN " == group )
    {
	readUnknown( file, size );
    }
    else if( "SSUN" == group )
    {
	readUnknown( file, size );
    }
    else if( "MOON" == group )
    {
	readUnknown( file, size );
    }
    else if( "SMOO" == group )
    {
	readUnknown( file, size );
    }
    else if( "CELS" == group )
    {
	readUnknown( file, size );
    }
    else if( "DEST" == group )
    {
	readUnknown( file, size );
    }
    else if( "PCAM" == group )
    {
	readUnknown( file, size );
    }
    else if( "RTFC" == group )
    {
	readUnknown( file, size );
    }
    else if( "SSTC" == group )
    {
	readUnknown( file, size );
    }
    else if( "STFP" == group )
    {
	readUnknown( file, size );
    }
    else if( "SST1" == group )
    {
	readUnknown( file, size );
    }
    else if( "SKTM" == group )
    {
	readUnknown( file, size );
    }
    else if( "XFNM" == group )
    {
	readUnknown( file, size );
    }
    else if( "POSN" == group )
    {
	readUnknown( file, size );
    }
    else if( "TWHD" == group )
    {
	readUnknown( file, size );
    }
    else if( "TWDT" == group )
    {
	readUnknown( file, size );
    }
    else if( "NORM" == group )
    {
	readUnknown( file, size );
    }
    else if( "DOT3" == group )
    {
	readUnknown( file, size );
    }
    else if( "OZN " == group )
    {
	readUnknown( file, size );
    }
    else if( "OZC " == group )
    {
	readUnknown( file, size );
    }
    else if( "FOZC" == group )
    {
	readUnknown( file, size );
    }
    else if( "ZTO " == group )
    {
	readUnknown( file, size );
    }
    else if( "PIDX" == group )
    {
	readUnknown( file, size );
    }
    else if( "NIDX" == group )
    {
	readUnknown( file, size );
    }
    else if( "TXCI" == group )
    {
	readUnknown( file, size );
    }
    else if( "TCSD" == group )
    {
	readUnknown( file, size );
    }
    else if( "OITL" == group )
    {
	readUnknown( file, size );
    }
    else if( "LATX" == group )
    {
	readUnknown( file, size );
    }
    else if( "CRCT" == group )
    {
	unsigned int numData = size/4;
	for( unsigned int i = 0; i < numData; ++i )
	{
	    unsigned int data;
	    file.read( (char*)&data, sizeof( data ) );
	    std::cout << i << ": " << data << std::endl;
	}
    }
    else if( "STRT" == group )
    {
	unsigned int numData = size/4;
	for( unsigned int i = 0; i < numData; ++i )
	{
	    unsigned int data;
	    file.read( (char*)&data, sizeof( data ) );
	    std::cout << i << ": " << data << std::endl;
	}
    }
    else if( "STNG" == group )
    {
	readUnknown( file, size );
    }
    else if( "TX1D" == group )
    {
	readUnknown( file, size );
    }
    else if( "LOCT" == group )
    {
	readUnknown( file, size );
    }
    else if( "PRTL" == group )
    {
	readUnknown( file, size );
    }
    else if( "0004" == group )
    {
	readUnknown( file, size );
    }
    else if( "LGHT" == group )
    {
	readUnknown( file, size );
    }
    else if( "CRC " == group )
    {
	readUnknown( file, size );
    }
    else if( "CYLN" == group )
    {
	readUnknown( file, size );
    }
    else if( "ITL " == group )
    {
	readUnknown( file, size );
    }
    else if( "INGR" == group )
    {
	readUnknown( file, size );
    }
    else if( "VAL " == group )
    {
	readUnknown( file, size );
    }
    else if( "PPTR" == group )
    {
	readUnknown( file, size );
    }
    else if( "SKMG" == group )
    {
	readUnknown( file, size );
    }
    else if( "DFLT" == group )
    {
	readUnknown( file, size );
    }
    else if( "PSRC" == group )
    {
	readUnknown( file, size );
    }
    else if( "PEXE" == group )
    {
	readUnknown( file, size );
    }
    else if( "PART" == group )
    {
	readUnknown( file, size );
    }
    else if( "SHDR" == group )
    {
	readUnknown( file, size );
    }
    else if( "ENTR" == group )
    {
	readUnknown( file, size );
    }
    else if( "EXIT" == group )
    {
	readUnknown( file, size );
    }
    else if( "DETH" == group )
    {
	readUnknown( file, size );
    }
    else if( "INCP" == group )
    {
	readUnknown( file, size );
    }
    else if( "WATR" == group )
    {
	readUnknown( file, size );
    }
    else if( "PSHM" == group )
    {
	readUnknown( file, size );
    }
    else if( "PSTM" == group )
    {
	readUnknown( file, size );
    }
    else if( "CNCF" == group )
    {
	readUnknown( file, size );
    }
    else if( "MESG" == group )
    {
	readUnknown( file, size );
    }
    else if( "DYN " == group )
    {
	readUnknown( file, size );
    }
    else if( "TRTS" == group )
    {
	readUnknown( file, size );
    }
    else if( "TRT " == group )
    {
	readUnknown( file, size );
    }
    else if( "HPTS" == group )
    {
	readUnknown( file, size );
    }
    else
    {
	std::cout << "Unknown KEYWORD: " << group << std::endl;
	exit(0);
    }

    // Size of data plus 8 bytes of header
    return size+8;
}




int main( int argc, char **argv )
{

    if( 2 > argc )
    {
	std::cout << "iffDump <file>" << std::endl;
	return 0;
    }

    for( int i = 1; i < argc; ++i )
    {
	std::ifstream meshFile( argv[i] );
	
	if( !meshFile.is_open() )
	{
	    std::cout << "Unable to open file: " << argv[1] << std::endl;
	    exit( 0 );
	}
	
	std::deque<std::string> parentForms;
	readRecord( meshFile, 0, parentForms );
	meshFile.close();
    }

    return 0;
}
