//
// is.h:  is implementations 
//
// Copyright (C) 2013    Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp_api_meat_is_h
#define Rcpp_api_meat_is_h

namespace Rcpp{ 
namespace internal{
        
    inline bool is_atomic( SEXP x){ return Rf_length(x) == 1 ; } 
    inline bool is_matrix(SEXP x){
        SEXP dim = Rf_getAttrib( x, R_DimSymbol) ;
        return dim != R_NilValue && Rf_length(dim) == 2 ;
    }
    
    template <> inline bool is__simple<int>( SEXP x ){
        return is_atomic(x) && TYPEOF(x) == INTSXP ;
    }

    template <> inline bool is__simple<double>( SEXP x ){
        return is_atomic(x) && TYPEOF(x) == REALSXP ;
    }
    
    template <> inline bool is__simple<bool>( SEXP x ){
        return is_atomic(x) && TYPEOF(x) == LGLSXP ;
    }
    
    template <> inline bool is__simple<std::string>( SEXP x ){
        return is_atomic(x) && TYPEOF(x) == STRSXP ;
    }
    
    template <> inline bool is__simple<String>( SEXP x ){
        return is_atomic(x) && TYPEOF(x) == STRSXP ;
    }
    
    template <> inline bool is__simple<RObject>( SEXP x ){
        return true ;
    }    
    template <> inline bool is__simple<DataFrame>( SEXP x ){
        if( TYPEOF(x) != VECSXP ) return false ;
        return Rf_inherits( x, "data.frame" ) ;
    }
    template <> inline bool is__simple<S4>( SEXP x ){
        return ::Rf_isS4(x);
    }
    template <> inline bool is__simple<Reference>( SEXP x ){
        if( ! ::Rf_isS4(x) ) return false ;
        return ::Rf_inherits(x, "envRefClass" ) ;
    }
    template <> inline bool is__simple<Formula>( SEXP x ){
        if( TYPEOF(x) != LANGSXP ) return false ; 
        return Rf_inherits( x, "formula" ) ;
    }
    template <> inline bool is__simple<Function>( SEXP x ){
        return TYPEOF(x) == CLOSXP || TYPEOF(x) == SPECIALSXP || TYPEOF(x) == BUILTINSXP ;
    }
    
    template <typename T>
    struct ModuleIs {
        inline bool test(SEXP x){
            typedef typename std::remove_pointer<T>::type CLASS ;
            Environment env(x) ;
            XPtr<class_Base> xp( env.get(".cppclass") );
            return xp->has_typeinfo_name( typeid(CLASS).name() ) ;
        }
    } ;
    
    template <int RTYPE> 
    struct Is< Matrix<RTYPE> > {
        inline bool test( SEXP x){
            return TYPEOF(x) == RTYPE && is_matrix(x) ;  
        }
    } ;
        
    
} // namespace internal
} // namespace Rcpp

#endif
