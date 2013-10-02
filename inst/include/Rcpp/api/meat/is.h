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
        
    template <>
    struct Is<RObject> {
        inline bool test(SEXP /* x */){ return true; }    
    } ;
    template <>
    struct Is<DataFrame> {
        inline bool test(SEXP x ){ 
            if( TYPEOF(x) != VECSXP ) return false ;
            return Rf_inherits( x, "data.frame" ) ; 
        }    
    } ;
    template <>
    struct Is<S4> {
        inline bool test(SEXP x ){ 
            return  ::Rf_isS4(x); 
        }    
    } ;
    template <>
    struct Is<Reference> {
        inline bool test(SEXP x ){ 
            if( ! ::Rf_isS4(x) ) return false ;
            return ::Rf_inherits(x, "envRefClass" ) ; 
        }    
    } ;
    template <>
    struct Is<Formula> {
        inline bool test(SEXP x ){ 
            if( TYPEOF(x) != LANGSXP ) return false ; 
            return Rf_inherits( x, "formula" ) ; 
        }    
    } ;
    template <>
    struct Is<Function> {
        inline bool test(SEXP x ){ 
            return TYPEOF(x) == CLOSXP || TYPEOF(x) == SPECIALSXP || TYPEOF(x) == BUILTINSXP ; 
        }    
    } ;
    
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
            return TYPEOF(x) == RTYPE && Rf_isMatrix(x) ;  
        }
    } ;
        
    
} // namespace internal
} // namespace Rcpp

#endif
