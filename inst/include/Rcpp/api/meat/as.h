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

#ifndef Rcpp_api_meat_as_h
#define Rcpp_api_meat_as_h

namespace Rcpp{
namespace internal{

    template <typename T> T* as_module_object(SEXP x) {
        Environment env(x) ;
        SEXP xp = env.get(".pointer") ;
        return reinterpret_cast<T*>( R_ExternalPtrAddr(xp) );
    }
       
    template <> inline Rcpp::String as<Rcpp::String>(SEXP x, ::Rcpp::traits::r_type_string_tag ) {
        if( ! ::Rf_isString(x) ){
            throw ::Rcpp::not_compatible( "expecting a string" ) ;
        }
        if (Rf_length(x) != 1) {
            throw ::Rcpp::not_compatible( "expecting a single value");
        }
        return STRING_ELT( x, 0 ) ;
    }
    
}
}
#endif
