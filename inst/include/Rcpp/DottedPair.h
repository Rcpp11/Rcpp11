//
// DottedPair.h:  dotted pair list template
//
// Copyright (C) 2010 - 2013 Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp_DottedPair_h
#define Rcpp_DottedPair_h

#include <RcppCommon.h>
#include <Rcpp/Named.h>
#include <Rcpp/RObject.h>

namespace Rcpp{ 

class DottedPair : 
    RCPP_POLICIES(DottedPair), 
    public DottedPairProxyPolicy<DottedPair>, 
    public DottedPairImpl<DottedPair>
{
public:

	DottedPair(){} ;
	
	DottedPair(SEXP x){
	    set__(x) ;
	} 
	
	RCPP_GENERATE_CTOR_ASSIGN(DottedPair) 
	
	template<typename... Args> 
	DottedPair( const Args&... args) {
		set__( pairlist(args...) ) ;
	}

	void update(SEXP){}
};

} // namespace Rcpp

#endif
