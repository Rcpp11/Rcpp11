//
// sprintf.h:  string formatting
//
// Copyright (C) 2010 - 2011 Dirk Eddelbuettel and Romain Francois
//
// This file is part of Rcpp11.
//
// Rcpp11 is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Rcpp11 is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Rcpp11.  If not, see <http://www.gnu.org/licenses/>.

#include <cstdio>
#include <cstdarg>

namespace Rcpp{

template <int MAX_SIZE>
std::string sprintf( const char *format, ...) {
    static char buffer[MAX_SIZE]; 
    va_list(ap);
    va_start(ap, format);
    vsnprintf( buffer, MAX_SIZE, format, ap);
    va_end(ap);
    return buffer ;
}

}

