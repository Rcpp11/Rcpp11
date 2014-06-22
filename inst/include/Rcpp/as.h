#ifndef Rcpp__as__h
#define Rcpp__as__h

#include <Rcpp/internal/Exporter.h>

namespace Rcpp{

    namespace internal{
        
        template <typename T> T primitive_as( SEXP x ){
            if( XLENGTH(x) != 1 ) stop( "expecting a single value, got vector if size %d", XLENGTH(x) ) ;
            const int RTYPE = ::Rcpp::traits::r_sexptype_traits<T>::rtype ;
            Shield<SEXP> y = r_cast<RTYPE>(x);
            typedef typename ::Rcpp::traits::storage_type<RTYPE>::type STORAGE;
            T res = caster<STORAGE,T>( *r_vector_start<RTYPE>( y ) ) ;
            return res ; 
        }
        
        template <typename T> T as( SEXP x, ::Rcpp::traits::r_type_primitive_tag ) {
            return primitive_as<T>(x) ;
        }
        
        inline const char* check_single_string( SEXP x){
            if( TYPEOF(x) == CHARSXP ) return CHAR( x ) ;
            if( ! Rf_isString(x) ){
                stop("expecting a string, got object of R type : %s", type2name(x) ) ;
            }
            if (XLENGTH(x) != 1)
                stop( "expecting a single value");
            return CHAR( STRING_ELT( ::Rcpp::r_cast<STRSXP>(x) ,0 ) ) ;
        }
        
        
        template <typename T> T as_string( SEXP x, std::true_type){
            const char* y = check_single_string(x) ;
            return std::wstring( y, y+strlen(y)) ;
        }
        
        template <typename T> T as_string( SEXP x, std::false_type){
            return check_single_string(x) ;
        }
        
        template <typename T> T as(SEXP x, ::Rcpp::traits::r_type_string_tag ) {
            return as_string<T>( x, typename Rcpp::traits::is_wide_string<T>::type() );
        }
        template <> inline Rcpp::String as<Rcpp::String>(SEXP x, ::Rcpp::traits::r_type_string_tag ) ; 
    
        template <typename T> T as(SEXP x, ::Rcpp::traits::r_type_generic_tag ) {
            ::Rcpp::traits::Exporter<T> exporter(x);
            return exporter.get() ;
        }
        
        /** handling enums by converting to int first */
        template <typename T> T as(SEXP x, ::Rcpp::traits::r_type_enum_tag ){
            return T( primitive_as<int>(x) ) ;
        }
        
    }
        
    template <typename T> T as( SEXP m_sexp) {
        return internal::as<T>( m_sexp, typename traits::r_type_traits<T>::r_category() ) ;
    }
    
    template <> inline char as<char>( SEXP m_sexp ){
        return internal::check_single_string(m_sexp)[0] ;    
    }
    
    template<> inline SEXP as(SEXP m_sexp) { return m_sexp ; }

} // Rcpp 

#endif
