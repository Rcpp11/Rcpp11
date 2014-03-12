#ifndef Rcpp_wrap_MatrixWrapper_h
#define Rcpp_wrap_MatrixWrapper_h
 
namespace Rcpp{
namespace internal{
    
    template <typename T, typename STORAGE>
    inline SEXP wrap_dispatch_matrix_primitive( const T& object ){
        const int RTYPE = ::Rcpp::traits::r_sexptype_traits<STORAGE>::rtype ;
        int nr = object.nrow(), nc = object.ncol() ;
        Shield<SEXP> res = Rf_allocVector( RTYPE, nr*nc );
        
        int k=0 ;
        STORAGE* p = r_vector_start< RTYPE>(res) ;
        for( int j=0; j<nc; j++)
            for( int i=0; i<nr; i++, k++)
                p[k] = object(i,j) ;
        Shield<SEXP> dim = Rf_allocVector( INTSXP, 2) ;
        INTEGER(dim)[0] = nr ;
        INTEGER(dim)[1] = nc ;
        Rf_setAttrib( res, R_DimSymbol , dim ) ;
        return res ;
    }
    
    template <typename T>
    inline SEXP wrap_dispatch_matrix_not_logical( const T& object, ::Rcpp::traits::r_type_primitive_tag ){
        return wrap_dispatch_matrix_primitive<T, typename T::stored_type>( object ) ;
    }
    
    template <typename T>
    inline SEXP wrap_dispatch_matrix_not_logical( const T& object, ::Rcpp::traits::r_type_string_tag ){
        int nr = object.nrow(), nc = object.ncol() ;
        Shield<SEXP> res = Rf_allocVector( STRSXP, nr*nc ) ;
        
        int k=0 ;
        for( int j=0; j<nc; j++)
            for( int i=0; i<nr; i++, k++)
                SET_STRING_ELT( res, k, make_charsexp(object(i,j)) ) ;
        Shield<SEXP> dim = Rf_allocVector( INTSXP, 2) ;
        INTEGER(dim)[0] = nr ;
        INTEGER(dim)[1] = nc ;
        Rf_setAttrib( res, R_DimSymbol , dim ) ;
        return res ;
    }
    
    template <typename T>
    inline SEXP wrap_dispatch_matrix_not_logical( const T& object, ::Rcpp::traits::r_type_generic_tag ){
        int nr = object.nrow(), nc = object.ncol() ;
        Shield<SEXP> res = Rf_allocVector( VECSXP, nr*nc );
        
        int k=0 ;
        for( int j=0; j<nc; j++)
            for( int i=0; i<nr; i++, k++)
        	       RCPP_SET_VECTOR_ELT( res, k, ::Rcpp::wrap( object(i,j) ) ) ;
        Shield<SEXP> dim = Rf_allocVector( INTSXP, 2) ;
        INTEGER(dim)[0] = nr ;
        INTEGER(dim)[1] = nc ;
        Rf_setAttrib( res, R_DimSymbol , dim ) ;
        return res ;
    }
    
}

    template <typename T> struct MatrixWrapper {
        static inline SEXP wrap(const T& object) {
            return internal::wrap_dispatch_matrix_not_logical<T>( object, typename ::Rcpp::traits::r_type_traits<typename T::stored_type>::r_category() ) ;    
        }
    } ;
    
}

#endif
