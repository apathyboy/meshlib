/** -*-c++-*-
 *  \class  base
 *  \file   base.hpp
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

#include <fstream>
#include <istream>
#include <ostream>
#include <string>
#include <vector>

#include <meshLib/box.hpp>
#include <meshLib/vector3.hpp>
#include <meshLib/matrix3.hpp>

#ifndef BASE_HPP
#define BASE_HPP

namespace ml
{
  class base
  {
  public:
    base() {};
    virtual ~base() {};
    virtual bool isRightType(){ return false; }
    static std::string getType( std::istream &file );
    unsigned int readBASE(){ return 0; }
    virtual bool canWrite() const { return false; }

    static unsigned int readUnknown( std::istream &file,
				     const unsigned int size );

    static unsigned int read(  std::istream &file, char &data );
    static unsigned int write( std::ostream &file, const char &data );
    static unsigned int read(  std::istream &file, unsigned char &data );
    static unsigned int write( std::ostream &file, const unsigned char &data );
    static unsigned int read(  std::istream &file, short &data );
    static unsigned int write( std::ostream &file, const short &data );
    static unsigned int read(  std::istream &file, unsigned short &data );
    static unsigned int write( std::ostream &file, const unsigned short &data );
    static unsigned int read(  std::istream &file, int &data );
    static unsigned int write( std::ostream &file, const int &data );
    static unsigned int read(  std::istream &file, unsigned int &data );
    static unsigned int write( std::ostream &file, const unsigned int &data );
    static unsigned int read(  std::istream &file, float &data );
    static unsigned int write( std::ostream &file, const float &data );
    static unsigned int read(  std::istream &file, std::string &data );
    static unsigned int write( std::ostream &file, const std::string &data );

    static void peekHeader( std::istream &file,
			    std::string &form,
			    unsigned int &size,
			    std::string &type );
      
    static unsigned int readFormHeader( std::istream &file,
					std::string &form,
					unsigned int &size,
					std::string &type );

    static unsigned int readFormHeader( std::istream &file,
					const std::string &expectedType,
					unsigned int &size );

    static unsigned int writeFormHeader( std::ostream &file,
					 const unsigned int &size,
					 const std::string &type );
    
    static unsigned int readRecordHeader( std::istream &file,
					  std::string &type,
					  unsigned int &size);
    
    static unsigned int writeRecordHeader( std::ostream &file,
					   const std::string &type,
					   const unsigned int &size);
    
    static unsigned char readBigEndian( std::istream &file,
					const unsigned int &size,
					char *buffer);
    
    static unsigned char writeBigEndian( std::ostream &file,
					 const unsigned int &size,
					 char *buffer);
    
    static bool fixSlash( std::string &filename );

  protected:
    bool isOfType( std::istream &file, const std::string &Type );

    std::string basePath;
					  
  private:
  };
}
#endif
