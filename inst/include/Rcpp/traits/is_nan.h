//
// is_nan.h:  is NaN
//                                                                      
// Copyright (C) 2013 Dirk Eddelbuettel, Romain Francois, and Kevin Ushey
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

#ifndef Rcpp__traits_is_nan_h
#define Rcpp__traits_is_nan_h

namespace Rcpp{
namespace traits{
	
	// default for most types 
	template <int RTYPE> 
	bool is_nan( typename storage_type<RTYPE>::type){
	    return false ;    
	}
	
	template <> 
	inline bool is_nan<REALSXP>( double x ){
		return Rcpp::internal::is_NaN(x) ;
	}
	
	template <> 
	inline bool is_nan<CPLXSXP>( Rcomplex x ){
		return Rcpp::internal::is_NaN(x.r) || Rcpp::internal::is_NaN(x.i) ;
	}
	
}
}

#endif
