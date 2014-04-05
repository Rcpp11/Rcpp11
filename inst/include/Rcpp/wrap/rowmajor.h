#ifndef Rcpp_wrap_rowmajor_h
#define Rcpp_wrap_rowmajor_h
 
namespace Rcpp{        
namespace internal{

    template <typename value_type, typename InputIterator> 
    inline SEXP rowmajor_wrap__dispatch( InputIterator first, int nrow, int ncol, ::Rcpp::traits::r_type_generic_tag ){
        Shield<SEXP> out = ::Rf_allocVector( VECSXP, nrow * ncol);
        int i=0, j=0 ;
        for( j=0; j<ncol; j++){
            for( i=0; i<nrow; i++, ++first ){
                SET_VECTOR_ELT( out, j + ncol*i, ::Rcpp::wrap( *first) ) ;
            }
        }
        Shield<SEXP> dims = ::Rf_allocVector( INTSXP, 2); 
        INTEGER(dims)[0] = nrow; 
        INTEGER(dims)[1] = ncol; 
        ::Rf_setAttrib( out, R_DimSymbol, dims) ;
        return out ;
    }
    
    template <typename value_type, typename InputIterator> 
    inline SEXP rowmajor_wrap__dispatch( InputIterator first, int nrow, int ncol, ::Rcpp::traits::r_type_string_tag ){
        Shield<SEXP> out = ::Rf_allocVector( STRSXP, nrow * ncol);
        int i=0, j=0 ;
        for( j=0; j<ncol; j++){
            for( i=0; i<nrow; i++, ++first ){
               SET_STRING_ELT( out, j + ncol*i, make_charsexp(*first) ) ;
            }
        }
        Shield<SEXP> dims = ::Rf_allocVector( INTSXP, 2); 
        INTEGER(dims)[0] = nrow; 
        INTEGER(dims)[1] = ncol; 
        ::Rf_setAttrib( out, R_DimSymbol, dims) ;
        return out ;
    }
    
    template <typename value_type, typename InputIterator> 
    inline SEXP primitive_rowmajor_wrap__dispatch( InputIterator first, int nrow, int ncol, std::false_type ){
        const int RTYPE = ::Rcpp::traits::r_sexptype_traits<value_type>::rtype ;
        Shield<SEXP> out = ::Rf_allocVector( RTYPE, nrow * ncol ) ;
        value_type* ptr = r_vector_start<RTYPE>( out );
        int i=0, j=0 ;
        for( j=0; j<ncol; j++){
           for( i=0; i<nrow; i++, ++first ){
               ptr[ j + ncol*i ] = *first ;
           }
        }
        Shield<SEXP> dims = ::Rf_allocVector( INTSXP, 2); 
        INTEGER(dims)[0] = nrow; 
        INTEGER(dims)[1] = ncol; 
        ::Rf_setAttrib( out, R_DimSymbol, dims) ;
        return out ;
    }
    template <typename value_type, typename InputIterator> 
    inline SEXP primitive_rowmajor_wrap__dispatch( InputIterator first, int nrow, int ncol, std::true_type ){
        const int RTYPE = ::Rcpp::traits::r_sexptype_traits<value_type>::rtype ;
        typedef typename ::Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
        Shield<SEXP> out = ::Rf_allocVector( RTYPE, nrow * ncol );
        STORAGE* ptr = r_vector_start<RTYPE>( out );
        int i=0, j=0 ;
        for( j=0; j<ncol; j++){
            for( i=0; i<nrow; i++, ++first ){
                ptr[ j + ncol*i ] = caster<value_type,STORAGE>( *first );
            }
        }
        Shield<SEXP> dims = ::Rf_allocVector( INTSXP, 2); 
        INTEGER(dims)[0] = nrow; 
        INTEGER(dims)[1] = ncol; 
        ::Rf_setAttrib( out, R_DimSymbol, dims) ;
        return out ;
    	
    }
    
    template <typename value_type, typename InputIterator> 
    inline SEXP rowmajor_wrap__dispatch( InputIterator first, int nrow, int ncol, ::Rcpp::traits::r_type_primitive_tag ){
        return primitive_rowmajor_wrap__dispatch<value_type,InputIterator>( first, nrow, ncol, typename ::Rcpp::traits::r_sexptype_needscast<value_type>() ) ;
    }
    
    template <typename InputIterator> 
    inline SEXP rowmajor_wrap(InputIterator first, int nrow, int ncol){
        typedef typename std::iterator_traits<InputIterator>::value_type VALUE_TYPE ;
        return rowmajor_wrap__dispatch<VALUE_TYPE,InputIterator>( first, nrow, ncol, typename ::Rcpp::traits::r_type_traits<VALUE_TYPE>::r_category() );
    }	

    
}
}

#endif
