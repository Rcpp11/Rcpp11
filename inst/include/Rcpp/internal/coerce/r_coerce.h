// Copyright (C) 2013 Romain Francois
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

namespace Rcpp{
namespace internal{
        
template <> inline int r_coerce<INTSXP,INTSXP>(int from) { return from ; }
template <> inline int r_coerce<LGLSXP,LGLSXP>(int from) { return from ; }
template <> inline double r_coerce<REALSXP,REALSXP>(double from) { return from ; }
template <> inline Rcomplex r_coerce<CPLXSXP,CPLXSXP>(Rcomplex from) { return from ; }
template <> inline Rbyte r_coerce<RAWSXP,RAWSXP>(Rbyte from) { return from ; }

// -> INTSXP
template <> inline int r_coerce<LGLSXP,INTSXP>(int from){
	return (from==NA_LOGICAL) ? NA_INTEGER : from ;
}
template <> inline int r_coerce<REALSXP,INTSXP>(double from){
	if (Rcpp::internal::Rcpp_IsNaN(from)) return NA_INTEGER;
	else if (from > INT_MAX || from <= INT_MIN ) {
		return NA_INTEGER;
	}
	return static_cast<int>(from);

}
template <> inline int r_coerce<CPLXSXP,INTSXP>(Rcomplex from){
	return r_coerce<REALSXP,INTSXP>(from.r) ;
}
template <> inline int r_coerce<RAWSXP,INTSXP>(Rbyte from){
	return static_cast<int>(from);
}

// -> REALSXP
template <> inline double r_coerce<LGLSXP,REALSXP>(int from){
	return from == NA_LOGICAL ? NA_REAL : static_cast<double>(from) ;
}
template <> inline double r_coerce<INTSXP,REALSXP>(int from){
	return from == NA_INTEGER ? NA_REAL : static_cast<double>(from) ; 
}
template <> inline double r_coerce<CPLXSXP,REALSXP>(Rcomplex from){
	return from.r ;
}
template <> inline double r_coerce<RAWSXP,REALSXP>(Rbyte from){
	return static_cast<double>(from) ;
}

// -> LGLSXP
template <> inline int r_coerce<REALSXP,LGLSXP>(double from){
	return ( from == NA_REAL ) ? NA_LOGICAL : (from!=0.0);
}
template <> inline int r_coerce<INTSXP,LGLSXP>(int from){
	return ( from == NA_INTEGER ) ? NA_LOGICAL : (from!=0);
}
template <> inline int r_coerce<CPLXSXP,LGLSXP>(Rcomplex from){
	if( from.r == NA_REAL ) return NA_LOGICAL ;
	if( from.r == 0.0 || from.i == 0.0 ) return FALSE ;
	return TRUE ;
}
template <> inline int r_coerce<RAWSXP,LGLSXP>(Rbyte from){
	if( from != static_cast<Rbyte>(0) ) return TRUE ;
	return FALSE ;
}

// -> RAWSXP
template <> inline Rbyte r_coerce<REALSXP,RAWSXP>(double from){
	if( from == NA_REAL) return static_cast<Rbyte>(0) ; 
	return r_coerce<INTSXP,RAWSXP>(static_cast<int>(from)) ;
}
template <> inline Rbyte r_coerce<INTSXP,RAWSXP>(int from){
	return (from < 0 || from > 255) ? static_cast<Rbyte>(0) : static_cast<Rbyte>(from) ;
}
template <> inline Rbyte r_coerce<CPLXSXP,RAWSXP>(Rcomplex from){
	return r_coerce<REALSXP,RAWSXP>(from.r) ;
}
template <> inline Rbyte r_coerce<LGLSXP,RAWSXP>(int from){
	return static_cast<Rbyte>(from == TRUE) ;
}

// -> CPLXSXP
template <> inline Rcomplex r_coerce<REALSXP,CPLXSXP>(double from){
	Rcomplex c ;
	if( from == NA_REAL ){
		c.r = NA_REAL; 
		c.i = NA_REAL;
	} else{
		c.r = from ;
		c.i = 0.0 ;
	}
	return c ;
}
template <> inline Rcomplex r_coerce<INTSXP,CPLXSXP>(int from){
	Rcomplex c ;
	if( from == NA_INTEGER ){
		c.r = NA_REAL; 
		c.i = NA_REAL;
	} else{
		c.r = static_cast<double>(from) ;
		c.i = 0.0 ;
	}
	return c ;
}
template <> inline Rcomplex r_coerce<RAWSXP,CPLXSXP>(Rbyte from){
	Rcomplex c ;
	c.r = static_cast<double>(from);
	c.i = 0.0 ;
	return c ;
}
template <> inline Rcomplex r_coerce<LGLSXP,CPLXSXP>(int from){
	Rcomplex c ;
	if( from == TRUE ){
		c.r = 1.0 ; c.i = 0.0 ;
	} else if( from == FALSE ){
		c.r = c.i = 0.0 ;
	} else { /* NA */
		c.r = c.i = NA_REAL;
	}
	return c ;
}

}
}
