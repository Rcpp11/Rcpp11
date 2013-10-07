// caster.h:  
//
// Copyright (C) 2010 - 2011 Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp__internal__caster__h
#define Rcpp__internal__caster__h

namespace Rcpp{
namespace internal{

template <typename FROM, typename TO> TO caster(FROM from){
	return static_cast<TO>(from) ;
}
template<> inline Rcomplex caster<std::complex<double>, Rcomplex>( std::complex<double> from){
    	Rcomplex cx ;
	cx.r = from.real() ; 
	cx.i = from.imag() ;
	return cx ;
} 
template<> inline Rcomplex caster<std::complex<float>, Rcomplex>( std::complex<float> from){
	Rcomplex cx ;
	cx.r = static_cast<double>( from.real() ); 
	cx.i = static_cast<double>( from.imag() );
	return cx ;
}

template<> inline std::complex<double> caster<Rcomplex,std::complex<double> >( Rcomplex from){
    return std::complex<double>(from.r, from.i ) ;    
}
template<> inline std::complex<float>  caster<Rcomplex,std::complex<float>  >( Rcomplex from){
    return std::complex<float>(static_cast<float>(from.r), static_cast<float>(from.i) ) ;    
}

template<> SEXP caster<String,SEXP>( String from ); 

}
}

#endif

