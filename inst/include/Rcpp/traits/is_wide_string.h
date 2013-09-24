// is_wide_string.h:  traits to help wrap
//
// Copyright (C) 2013 Dirk Eddelbuettel and Romain Francois
// Copyright (C) 2013 Rice University
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

#ifndef Rcpp__traits__is_wide_string__h
#define Rcpp__traits__is_wide_string__h

namespace Rcpp{
namespace traits{

    template <typename T>
    struct is_wide_string : public std::is_same< typename T::value_type, wchar_t > {} ;
	
    template <> struct is_wide_string< const wchar_t* > : public std::true_type{} ;
    template <> struct is_wide_string< const char* > : public std::false_type{} ;
    
    template <> struct is_wide_string< wchar_t > : public std::true_type{} ;
    template <> struct is_wide_string< char > : public std::false_type{} ;
    
} // traits
} // Rcpp

#endif
