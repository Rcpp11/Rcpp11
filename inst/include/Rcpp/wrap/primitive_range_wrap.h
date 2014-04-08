#ifndef Rcpp_wrap_primitive_range_wrap_h
#define Rcpp_wrap_primitive_range_wrap_h
 
namespace Rcpp{
namespace internal{

    /**
     * Range based primitive wrap implementation. used when 
     * - T is a primitive type, indicated by the r_type_traits
     * - T needs a static_cast to be of the type suitable to fit in the R vector
     *
     * This produces an unnamed vector of the appropriate type using the 
     * std::transform algorithm
     */
    template <typename InputIterator, typename T>
    inline SEXP primitive_range_wrap__impl( InputIterator first, InputIterator last, std::true_type ){
        RCPP_DEBUG( "primitive_range_wrap__impl< InputIterator = %s , T = %s>(.,., true_type )\n", DEMANGLE(InputIterator), DEMANGLE(T) ) ;
        size_t size = std::distance( first, last ) ;
        const int RTYPE = ::Rcpp::traits::r_sexptype_traits<T>::rtype ;
        Shield<SEXP> x = Rf_allocVector( RTYPE, size ) ;
        std::transform( first, last, r_vector_start<RTYPE>(x), 
            caster< T, typename ::Rcpp::traits::storage_type<RTYPE>::type >
        ) ; 
        return x ;
    }
    
    /**
     * Range based primitive wrap implementation. used when : 
     * - T is a primitive type
     * - T does not need a cast
     *
     * This produces an unnamed vector of the appropriate type using 
     * the std::copy algorithm
     */
    template <typename InputIterator, typename T>
    inline SEXP primitive_range_wrap__impl( InputIterator first, InputIterator last, std::false_type ){
        RCPP_DEBUG( "primitive_range_wrap__impl< InputIterator = %s , T = %s>(.,., false_type )\n", DEMANGLE(InputIterator), DEMANGLE(T) ) ;
        size_t size = std::distance( first, last ) ;
        const int RTYPE = ::Rcpp::traits::r_sexptype_traits<T>::rtype ;
        Shield<SEXP> x = Rf_allocVector( RTYPE, size );
        std::copy( first, last, r_vector_start<RTYPE>(x) ) ; 
        return x ;
    }

}
}    

#endif
