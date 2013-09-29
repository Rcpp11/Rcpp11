// wrap_impl.h:  wrap implementations
//
// Copyright (C) 2010 - 2013  Dirk Eddelbuettel and Romain Francois
// Copyright (C) 2013  Rice University
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

#ifndef Rcpp_wrap_wrap_impl_h
#define Rcpp_wrap_wrap_impl_h
 
namespace Rcpp{

template <typename T>
inline SEXP wrap( std::initializer_list<T> init ){ return internal::range_wrap( init.begin(), init.end() ) ; } 

// this also handles char[] 
inline SEXP wrap(const char* const v ){ 
    if (v == NULL)
	return R_NilValue;
    else
	return Rf_mkString(v) ;
}

/**
 * Range based version of wrap
 */
template <typename InputIterator>
inline SEXP wrap(InputIterator first, InputIterator last){ 
	return internal::range_wrap( first, last ) ;
}


} // Rcpp

#endif
