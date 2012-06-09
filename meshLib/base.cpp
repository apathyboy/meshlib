/** -*-c++-*-
 *  \class  base
 *  \file   base.cpp
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
#include <iostream>
#include <cstdlib>

using namespace ml;

std::string base::getType( std::istream &file )
{
  std::string form;
  unsigned int size;
  std::string type;
    
  // Peek at next record, but keep file at same place.
  peekHeader( file, form, size, type );
    
  if( "FORM" == form )
    {
      return type;
    }
  else
    {
      unsigned int x;
      read( file, x );

      // .str string file
      if( x == 0xabcd )
	{
	  return std::string("ABCD");
	}

      return std::string("");
    }
}

bool base::isOfType( std::istream &file, const std::string &Type )
{
  std::string form;
  unsigned int size;
  std::string type;

  // Get current file position...
  std::streampos position = file.tellg();

  // Read first FORM
  readFormHeader( file, form, size, type );

  // Reposition file to original location
  file.seekg( position, std::ios_base::beg );

  return( "FORM" == form && Type == type );
}

unsigned char base::readBigEndian( std::istream &file,
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

unsigned char base::writeBigEndian( std::ostream &file,
				    const unsigned int &size,
				    char *buffer
				    )
{
#if BYTE_ORDER == LITTLE_ENDIAN
  for( unsigned int i=0; i<size; ++i )
    {
      file.write( &(buffer[size -1 - i]), 1 );
    }
#else
  file.write( buffer, size );
#endif
    
  return size;
}

void base::peekHeader( std::istream &file,
		       std::string &form,
		       unsigned int &size,
		       std::string &type )
{
  // Peek at next record, but keep file at same place.
  std::streampos position = file.tellg();
  readFormHeader( file, form, size, type );
  file.seekg( position, std::ios_base::beg );
}

// **************************************************

unsigned int base::readRecordHeader( std::istream &file,
				     std::string &type,
				     unsigned int &size )
{
  char tempType[5];
  file.read( tempType, 4 );
  tempType[4] = 0;
  type = tempType;
  readBigEndian( file, sizeof( size ), (char *)&size );

  return 8;
}

unsigned int base::writeRecordHeader( std::ostream &file,
				      const std::string &type,
				      const unsigned int &size )
{
  file.write( type.c_str(), 4 );
  writeBigEndian( file, sizeof( size ), (char *)&size );

  return 8;
}

// **************************************************

unsigned int base::readFormHeader( std::istream &file,
				   std::string &form,
				   unsigned int &size,
				   std::string &type )
{
  unsigned total = readRecordHeader( file, form, size );
  char tempType[5];
  file.read( tempType, 4 );
  total += 4;

  tempType[4] = 0;
  type = tempType;

  return total;
}

unsigned int base::writeFormHeader( std::ostream &file,
				    const unsigned int &size,
				    const std::string &type )
{
  file.write( "FORM", 4 );
  writeBigEndian( file, sizeof( size ), (char *)&size );
  file.write( type.c_str(), 4 );

  return 12;
}

// **************************************************

unsigned int base::readFormHeader( std::istream &file,
				   const std::string &expectedType,
				   unsigned int &size )
{
  std::string form;
  unsigned total = readRecordHeader( file, form, size );
  if( "FORM" != form )
    {
      std::cout << "Expected FORM, found: " << form << std::endl;
      throw std::exception();
    }

  char tempType[5];
  file.read( tempType, 4 );
  total += 4;
  tempType[4] = 0;

  std::string type( tempType );
  if( expectedType != type )
    {
      std::cout << "Expected FORM of type " << expectedType
		<< ", found: " << type << std::endl;
      throw std::exception();
    }

  return total;
}

unsigned int base::readUnknown( std::istream &file,
				const unsigned int size )
{
  for( unsigned int i = 0; i < size; ++i )
    {
      unsigned char data;
      file.read( (char*)&data, 1 );
      if(
	 ( data >= '.' && data <= 'z' )
	 || ( data == '\\' ) || ( data == ' ' )
	 )
        {
	  std::cout << data;
        }
      else
        {
	  std::cout<<std::hex<<"0x"<<(unsigned int)data<<" "<< std::dec;
        }
    }
  std::cout << std::endl;
  return size;
}

// **************************************************

unsigned int base::read( std::istream &file, char &data )
{
  file.read( &data, sizeof( char ) );
  return sizeof( char );
}

unsigned int base::write( std::ostream &file, const char &data )
{
  file.write( &data, sizeof( char ) );
  return sizeof( char );
}

// **************************************************

unsigned int base::read( std::istream &file, unsigned char &data )
{
  file.read( (char*)&data, sizeof( unsigned char ) );
  return sizeof( unsigned char );
}

unsigned int base::write( std::ostream &file, const unsigned char &data )
{
  file.write( (char*)&data, sizeof( unsigned char ) );
  return sizeof( unsigned char );
}

// **************************************************

unsigned int base::read( std::istream &file, short &data )
{
  file.read( (char*)&data, sizeof( short ) );
  return sizeof( short );
}

unsigned int base::write( std::ostream &file, const short &data )
{
  file.write( (char*)&data, sizeof( short ) );
  return sizeof( short );
}

// **************************************************

unsigned int base::read( std::istream &file, unsigned short &data )
{
  file.read( (char*)&data, sizeof( unsigned short ) );
  return sizeof( unsigned short );
}

unsigned int base::write( std::ostream &file, const unsigned short &data )
{
  file.write( (char*)&data, sizeof( unsigned short ) );
  return sizeof( unsigned short );
}

// **************************************************

unsigned int base::read( std::istream &file, int &data )
{
  file.read( (char*)&data, sizeof( int ) );
  return sizeof( int );
}

unsigned int base::write( std::ostream &file, const int &data )
{
  file.write( (char*)&data, sizeof( int ) );
  return sizeof( int );
}

// **************************************************

unsigned int base::read( std::istream &file, unsigned int &data )
{
  file.read( (char*)&data, sizeof( unsigned int ) );
  return sizeof( unsigned int );
}

unsigned int base::write( std::ostream &file, const unsigned int &data )
{
  file.write( (char*)&data, sizeof( unsigned int ) );
  return sizeof( unsigned int );
}

// **************************************************

unsigned int base::read( std::istream &file, float &data )
{
  file.read( (char*)&data, sizeof( float ) );
  return sizeof( float );
}

unsigned int base::write( std::ostream &file, const float &data )
{
  file.write( (char*)&data, sizeof( float ) );
  return sizeof( float );
}

// **************************************************

unsigned int base::read( std::istream &file, std::string &data )
{
  char temp[255];
  file.getline( temp, 255, 0 );
  data = temp;
  return( data.size() + 1 );
}

unsigned int base::write( std::ostream &file, const std::string &data )
{
  file.write( data.c_str(), data.size()+1 );
  return( data.size() + 1 );
}

// **************************************************

bool base::fixSlash( std::string &filename )
{
  for( unsigned int i = 0; i < filename.size(); ++i )
    {
      if( filename[i] == '\\' )
	{
	  filename[i] = '/';
	}
    }

  return true;
}

