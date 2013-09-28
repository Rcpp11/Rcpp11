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

#ifndef Rcpp_wrap_MatrixWrapper_h
#define Rcpp_wrap_MatrixWrapper_h
 
namespace Rcpp{
namespace internal{
    
    template <typename T>
    inline SEXP wrap_dispatch_matrix_logical( const T& object, std::true_type ){
        int nr = object.nrow(), nc = object.ncol() ;
        SEXP res = PROTECT( Rf_allocVector( LGLSXP, nr * nc ) ) ;
        int k=0 ;
        int* p = LOGICAL(res) ;
        for( int j=0; j<nc; j++)
            for( int i=0; i<nr; i++, k++)
                p[k] = object(i,j) ;
        SEXP dim = PROTECT( Rf_allocVector( INTSXP, 2) ) ;
        INTEGER(dim)[0] = nr ;
        INTEGER(dim)[1] = nc ;
        Rf_setAttrib( res, R_DimSymbol , dim ) ;
        UNPROTECT(2) ;
        return res ;
    }
    
    template <typename T, typename STORAGE>
    inline SEXP wrap_dispatch_matrix_primitive( const T& object ){
        const int RTYPE = ::Rcpp::traits::r_sexptype_traits<STORAGE>::rtype ;
        int nr = object.nrow(), nc = object.ncol() ;
        SEXP res = PROTECT( Rf_allocVector( RTYPE, nr*nc ) );
        
        int k=0 ;
        STORAGE* p = r_vector_start< RTYPE>(res) ;
        for( int j=0; j<nc; j++)
            for( int i=0; i<nr; i++, k++)
                p[k] = object(i,j) ;
        SEXP dim = PROTECT( Rf_allocVector( INTSXP, 2) ) ;
        INTEGER(dim)[0] = nr ;
        INTEGER(dim)[1] = nc ;
        Rf_setAttrib( res, R_DimSymbol , dim ) ;
        UNPROTECT(2) ;
        return res ;
    }
    
    template <typename T>
    inline SEXP wrap_dispatch_matrix_not_logical( const T& object, ::Rcpp::traits::r_type_primitive_tag ){
        return wrap_dispatch_matrix_primitive<T, typename T::stored_type>( object ) ;
    }
    
    template <typename T>
    inline SEXP wrap_dispatch_matrix_not_logical( const T& object, ::Rcpp::traits::r_type_string_tag ){
        int nr = object.nrow(), nc = object.ncol() ;
        SEXP res = PROTECT( Rf_allocVector( STRSXP, nr*nc ) ) ;
        
        int k=0 ;
        for( int j=0; j<nc; j++)
            for( int i=0; i<nr; i++, k++)
                SET_STRING_ELT( res, k, make_charsexp(object(i,j)) ) ;
        SEXP dim = PROTECT( Rf_allocVector( INTSXP, 2) ) ;
        INTEGER(dim)[0] = nr ;
        INTEGER(dim)[1] = nc ;
        Rf_setAttrib( res, R_DimSymbol , dim ) ;
        UNPROTECT(2) ;
        return res ;
    }
    
    template <typename T>
    inline SEXP wrap_dispatch_matrix_not_logical( const T& object, ::Rcpp::traits::r_type_generic_tag ){
        int nr = object.nrow(), nc = object.ncol() ;
        SEXP res = PROTECT( Rf_allocVector( VECSXP, nr*nc ) );
        
        int k=0 ;
        for( int j=0; j<nc; j++)
            for( int i=0; i<nr; i++, k++)
        	       SET_VECTOR_ELT( res, k, ::Rcpp::wrap( object(i,j) ) ) ;
        SEXP dim = PROTECT( Rf_allocVector( INTSXP, 2) ) ;
        INTEGER(dim)[0] = nr ;
        INTEGER(dim)[1] = nc ;
        Rf_setAttrib( res, R_DimSymbol , dim ) ;
        UNPROTECT(2) ;
        return res ;
    }
    
    template <typename T>
    inline SEXP wrap_dispatch_matrix_logical( const T& object, std::false_type ){
        return wrap_dispatch_matrix_not_logical<T>( object, typename ::Rcpp::traits::r_type_traits<typename T::stored_type>::r_category() ) ;
    }
    
    
}

    template <typename T> struct MatrixWrapper {
        static inline SEXP wrap(const T& object) { 
            RCPP_DEBUG( "MatrixWrapper<%s>::process(const T& object) ", DEMANGLE(T) ) 
            return internal::wrap_dispatch_matrix_logical( object, typename ::Rcpp::traits::expands_to_logical<T>::type() ) ;    
        }
    } ;
    
}

#endif
