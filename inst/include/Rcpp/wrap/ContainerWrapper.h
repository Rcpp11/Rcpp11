// Copyright (C) 2013  Romain Francois
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

#ifndef Rcpp_wrap_ContainerWrapper_h
#define Rcpp_wrap_ContainerWrapper_h
 
namespace Rcpp{
namespace internal{
    
    template <typename T>
    inline SEXP wrap_dispatch_unknown_iterable__logical( const T& object, std::true_type){
        RCPP_DEBUG( "wrap_dispatch_unknown_iterable__logical<%s>(., true  )", DEMANGLE(T) )
        size_t size = object.size() ;
        Scoped<SEXP> x = Rf_allocVector( LGLSXP, size );
        std::copy( object.begin(), object.end(), LOGICAL(x) ) ; 
        return x ;
    }
    
    template <typename T>
    inline SEXP wrap_dispatch_unknown_iterable__logical( const T& object, std::false_type){
        RCPP_DEBUG( "wrap_dispatch_unknown_iterable__logical<%s>(., false  )", DEMANGLE(T) )
        return range_wrap( object.begin(), object.end() ) ;
    }
    
}
    
    template <typename T> struct ContainerWrapper {
        static inline SEXP wrap(const T& object) { 
            RCPP_DEBUG( "ContainerWrapper<%s>::wrap() ", DEMANGLE(T) ) 
            return internal::range_wrap( object.begin(), object.end() ) ;    
        }
    } ;
    
}

#endif
