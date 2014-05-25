#ifndef Rcpp__internal__export__h
#define Rcpp__internal__export__h

namespace Rcpp{
    namespace internal{

    
        template <typename T>
        std::wstring as_string_elt__impl( SEXP x, R_xlen_t i, std::true_type ){
            const char* y = CHAR(STRING_ELT(x, i)) ;
            return std::wstring(y, y+strlen(y) ) ;
        }
    
        template <typename T>
        std::string as_string_elt__impl( SEXP x, R_xlen_t i, std::false_type ){
            return CHAR(STRING_ELT( x, i )) ;
        }
    
        template <typename T>
        const std::basic_string< typename Rcpp::traits::char_type<T>::type > 
        as_string_elt( SEXP x, R_xlen_t i ){
            return as_string_elt__impl<T>( x, i, typename Rcpp::traits::is_wide_string<T>::type() ) ;
        }
    
        /* iterating */
        
        template <typename InputIterator, typename value_type>
            void export_range__impl( SEXP x, InputIterator first, std::false_type ) {
            const int RTYPE = ::Rcpp::traits::r_sexptype_traits<value_type>::rtype ;
            typedef typename ::Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
            Shield<SEXP> y = ::Rcpp::r_cast<RTYPE>(x) ;
            STORAGE* start = ::Rcpp::internal::r_vector_start<RTYPE>(y) ;
            std::copy( start, start + ::Rf_xlength(y), first ) ;
        }
        
        template <typename InputIterator, typename value_type>
        void export_range__impl( SEXP x, InputIterator first, std::true_type ) {
            const int RTYPE = ::Rcpp::traits::r_sexptype_traits<value_type>::rtype ;
            typedef typename ::Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
            Shield<SEXP> y = ::Rcpp::r_cast<RTYPE>(x) ;
            STORAGE* start = ::Rcpp::internal::r_vector_start<RTYPE>(y) ;
            std::transform( start, start + ::Rf_xlength(y) , first, caster<STORAGE,value_type> ) ;
    }
        
    template <typename InputIterator, typename value_type>
    void export_range__dispatch( SEXP x, InputIterator first, ::Rcpp::traits::r_type_generic_tag ) {
        R_xlen_t n = ::Rf_xlength(x) ;
        for( R_xlen_t i=0; i<n; i++, ++first ){
            *first = ::Rcpp::as<value_type>( VECTOR_ELT(x, i) ) ;
        }        
    }
    
    template <typename InputIterator, typename value_type>
    void export_range__dispatch( SEXP x, InputIterator first, ::Rcpp::traits::r_type_primitive_tag ) {
            export_range__impl<InputIterator,value_type>(
                x, 
                first,
                typename ::Rcpp::traits::r_sexptype_needscast<value_type>()
            );
        }
        
        template <typename InputIterator, typename value_type>
        void export_range__dispatch( SEXP x, InputIterator first, ::Rcpp::traits::r_type_string_tag ) {
            if( ! Rf_isString( x) ) throw ::Rcpp::not_compatible( "expecting a string vector" ) ;
            R_xlen_t n = ::Rf_xlength(x) ;
            for( R_xlen_t i=0; i<n; i++, ++first ){
                *first = as_string_elt<typename std::iterator_traits<InputIterator>::value_type> ( x, i ) ;
            }
        }
        
        template <typename InputIterator>
        void export_range( SEXP x, InputIterator first ) {
            export_range__dispatch<InputIterator,typename std::iterator_traits<InputIterator>::value_type>( 
                x, 
                first, 
                typename ::Rcpp::traits::r_type_traits<typename std::iterator_traits<InputIterator>::value_type>::r_category() 
            );
        }
        
        
        /* indexing */
        
        template <typename T, typename value_type>
        void export_indexing__impl( SEXP x, T& res, std::false_type ) {
            const int RTYPE = ::Rcpp::traits::r_sexptype_traits<value_type>::rtype ;
            typedef typename ::Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
            Shield<SEXP> y = ::Rcpp::r_cast<RTYPE>(x) ;
            STORAGE* start = ::Rcpp::internal::r_vector_start<RTYPE>(y) ;
            R_xlen_t size = ::Rf_xlength(y)  ;
            for( R_xlen_t i=0; i<size; i++){
                res[i] =  start[i] ;
            }
        }
        
        template <typename T, typename value_type>
        void export_indexing__impl( SEXP x, T& res, std::true_type ) {
            const int RTYPE = ::Rcpp::traits::r_sexptype_traits<value_type>::rtype ;
            typedef typename ::Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
            Shield<SEXP> y = ::Rcpp::r_cast<RTYPE>(x) ;
            STORAGE* start = ::Rcpp::internal::r_vector_start<RTYPE>(y) ;
            R_xlen_t size = ::Rf_xlength(y)  ;
            for( R_xlen_t i=0; i<size; i++){
                res[i] = caster<STORAGE,value_type>(start[i]) ;
            }
        }

        template <typename T, typename value_type>
        void export_indexing__dispatch( SEXP x, T& res, ::Rcpp::traits::r_type_primitive_tag ) {
            export_indexing__impl<T,value_type>(
                x, 
                res,
                typename ::Rcpp::traits::r_sexptype_needscast<value_type>()
            );
        }
        
        template <typename T, typename value_type>
        void export_indexing__dispatch( SEXP x, T& res, ::Rcpp::traits::r_type_string_tag ) {
            if( ! Rf_isString( x) ) throw Rcpp::not_compatible( "expecting a string vector" ) ;
            R_xlen_t n = ::Rf_xlength(x) ;
            for( R_xlen_t i=0; i<n; i++ ){
                res[i] = as_string_elt< value_type >( x, i) ;
            }
        }
       
        template <typename T, typename value_type>
        void export_indexing( SEXP x, T& res ) {
            export_indexing__dispatch<T,value_type>( 
                x, 
                res, 
                typename ::Rcpp::traits::r_type_traits<value_type>::r_category() 
            );
        }
        
    }
}

#endif
