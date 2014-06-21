#ifndef Rcpp__vector__converters_h
#define Rcpp__vector__converters_h
 
namespace Rcpp{
namespace internal {
    
    
    template <typename T>
    const char* get_object_name__impl( const T& object, std::true_type ){
        return CHAR(PRINTNAME(object.name)) ;    
    }
    template <typename T>
    const char* get_object_name__impl( const T& /* object */, std::false_type){
        return "" ;    
    }
    
    template <typename T>
    const char* get_object_name( const T& object ){
        return get_object_name__impl( object, typename Rcpp::traits::is_named<T>::type() ) ;    
    }
    
    template <int RTYPE>
    class element_converter{
    public:
        typedef typename ::Rcpp::traits::storage_type<RTYPE>::type target ;
    
        template <typename T>
        static target get__impl( const T& input, std::true_type){
            return caster< typename T::object_type,target>(input.object) ; 
        }
    
        template <typename T>
        static target get__impl( const T& input, std::false_type){
            return caster<T,target>(input) ;
        }
    
        template <typename T>
        static target get( const T& input ){
            return get__impl( input, typename Rcpp::traits::is_named<T>::type() ) ;
        }
    
        static target get( const target& input ){
            return input ;
        }
    
        static target get( const Na_Proxy& /* input */ ){
            return traits::get_na<RTYPE>() ;
        }
    
    
    } ;

    template <int RTYPE>
    class string_element_converter {
    public:
        typedef SEXP target ;
    
        template <typename T>
        static target get__impl( const T& input, std::true_type) ;
    
        template <typename T>
        static target get__impl( const T& input, std::false_type) ;
        
        template <typename T>
        static SEXP get( const T& input){
            return get__impl( input, typename Rcpp::traits::is_named<T>::type() ) ;
        }
    
        // assuming a CHARSXP
        static SEXP get(SEXP x){ 
            return x;
        }
    
    } ;

    template <int RTYPE>
    class generic_element_converter {
    public:
        typedef SEXP target ;
    
        template <typename T>
        static target get__impl( const T& input, std::true_type){
            return ::Rcpp::wrap( input.object ) ;
        }
    
        template <typename T>
        static target get__impl( const T& input, std::false_type){
            return ::Rcpp::wrap( input ) ;
        }
    
    
        template <typename T>
        static SEXP get( const T& input){
            return get__impl( input, typename Rcpp::traits::is_named<T>::type() ) ;
        }
    
        static SEXP get( const char* input){
            return ::Rcpp::wrap( input );
        }
    
        static SEXP get(SEXP input){
            return input ;
        }
    
        static target get( const Na_Proxy& /* input */ ){
            return R_LogicalNAValue ;
        }
    } ;
}

namespace traits{
    template <int RTYPE> struct r_vector_element_converter{
        typedef typename ::Rcpp::internal::element_converter<RTYPE> type ;
    } ;
    template<> struct r_vector_element_converter<STRSXP>{
        typedef ::Rcpp::internal::string_element_converter<STRSXP> type ;
    } ;
    template<> struct r_vector_element_converter<VECSXP>{
        typedef ::Rcpp::internal::generic_element_converter<VECSXP> type ;
    } ;
    template<> struct r_vector_element_converter<EXPRSXP>{
        typedef ::Rcpp::internal::generic_element_converter<EXPRSXP> type ;
    } ;
}
}

#endif
