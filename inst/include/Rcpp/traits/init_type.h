//
// init_type.h:  support traits for vector
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

#ifndef Rcpp__traits__init_type_h
#define Rcpp__traits__init_type_h

namespace Rcpp {
namespace traits {

	template<int RTYPE> struct init_type {
		typedef typename storage_type<RTYPE>::type type ;
	} ;
	template<> struct init_type<STRSXP>{
		typedef const char* type ;
	} ;
	template<> struct init_type<LGLSXP>{
		typedef bool type ;
	} ;
	
}
}

#endif
